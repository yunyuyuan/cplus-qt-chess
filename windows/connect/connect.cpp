#include "connect.h"

const char *qstring_to_char(const QString &s) {
    const std::string &text = s.toStdString();
    return text.c_str();
}


void ConnectWindow::setupUi() {
    tab_create = new Button("创建", this);
    tab_join = new Button("加入", this);
    stop = new Button("取消", this);
    start = new Button("提交", this);
    connect(tab_create, &QPushButton::clicked, this, &ConnectWindow::switchToCreate);
    connect(tab_join, &QPushButton::clicked, this, &ConnectWindow::switchToJoin);
    connect(stop, &QPushButton::clicked, this, &ConnectWindow::cancelConnect);
    connect(start, &QPushButton::clicked, this, &ConnectWindow::doConnect);

    input_nick = new QLineEdit(this);
    input_ip = new QLineEdit(this);
    connect(input_ip, &QLineEdit::textChanged, this, &ConnectWindow::parseIp);
    
    status = new QLabel("", this);
    status->setAlignment(Qt::AlignCenter);

    auto* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("昵称:", this), 0, 0, 1, 1);
    layout->addWidget(input_nick, 0, 1, 1, 11);
    layout->addWidget(new QLabel("地址:", this), 1, 0, 1, 1);
    layout->addWidget(input_ip, 1, 1, 1, 11);
    layout->addWidget(tab_create, 2, 0, 1, 2);
    layout->addWidget(tab_join, 2, 2, 1, 2);
    layout->addWidget(stop, 2, 8, 1, 2);
    layout->addWidget(start, 2, 10, 1, 2);
    layout->addWidget(status, 3, 0, 1, 12);
    setLayout(layout);
}

ConnectWindow::ConnectWindow() {
    setupUi();
    show();
}

void ConnectWindow::switchToCreate() {
    is_create = true;
}
void ConnectWindow::switchToJoin() {
    is_create = false;
}
void ConnectWindow::parseIp() {
    const QString &s = input_ip->text().trimmed();
    if (s.indexOf(":") == -1){
        return;
    }
    QStringList lis = s.split(":");
    input_ip_text = lis[0];
    input_port_text = lis[1].toInt();
}

void ConnectWindow::doConnect() {
    if (connecting)return;
    connecting = true;
    status->setText("准备连接...");
    if (is_create) {
        auto worker = new ServerWorker(this->input_port_text, qstring_to_char(this->input_nick->text()));
        connect(worker, &ServerWorker::resultReady, this, &ConnectWindow::server_finish);
        connect(worker, &ServerWorker::statusChange, this, &ConnectWindow::status_change);
        worker->start();
    }else{
        auto worker = new ClientWorker(this->input_port_text, qstring_to_char(this->input_ip_text), qstring_to_char(this->input_nick->text()));
        connect(worker, &ClientWorker::resultReady, this, &ConnectWindow::client_finish);
        connect(worker, &ClientWorker::statusChange, this, &ConnectWindow::status_change);
        worker->start();
    }
}
void ConnectWindow::status_change(const char* str) {
    status->setText(str);
}

void ConnectWindow::server_finish(int sock_, int client_sock_) {
    this->sock = sock_;
    this->client_sock = client_sock_;
    if (client_sock == 0){
        status->setText("创建失败");
    }else{
        status->setText("创建成功");
    }
    if (sock == 0){
    }
    connecting = false;
}
void ConnectWindow::client_finish(int sock_) {
    this->sock = sock_;
    if (sock == 0){
        status->setText("加入失败");
    }else{
        status->setText("加入成功");
    }
    connecting = false;
}

void ConnectWindow::cancelConnect() {

}

// ------- worker ----------

ServerWorker::ServerWorker(uint16_t input_port_text, const char* input_nick) {
    this->input_port_text = input_port_text;
    this->input_nick = input_nick;
}
void ServerWorker::run() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    char buffer[1024] = {0};

    emit statusChange("创建服务器...");
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == 0){
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(input_port_text);
    emit statusChange("正在绑定端口...");
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0){
    }
    emit statusChange("准备监听连接...");
    if (listen(sock, 1) < 0){
    }
    emit statusChange("等待玩家连接...");
    int client_sock;
    if ((client_sock = accept(sock, (struct sockaddr *)&address , (socklen_t *) &addrlen)) < 0){
    }
    // 发送主机昵称
    emit statusChange("发送自身昵称...");
    send(sock , input_nick , strlen(input_nick) , 0);
    // 接受客机昵称
    emit statusChange("接受对方昵称...");
    recv(sock , buffer, 1024, 0);
    printf("%s\n", buffer);
    emit resultReady(sock, client_sock);
}

ClientWorker::ClientWorker(uint16_t input_port_text, const char * input_ip_text, const char * input_nick) {
    this->input_port_text = input_port_text;
    this->input_ip_text = input_ip_text;
    this->input_nick = input_nick;
}

void ClientWorker::run() {
    struct sockaddr_in serv_addr;
    int sock;
    char buffer[1024] = {0};
    emit statusChange("正在创建连接...");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(uint16_t(input_port_text));
    if(inet_pton(AF_INET, input_ip_text, &serv_addr.sin_addr)<=0){
    }
    emit statusChange("正在连接主机...");
    if (::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    }
    // 接受主机昵称
    emit statusChange("接受对方昵称...");
    recv(sock , buffer, 1024, 0);
    printf("%s\n", buffer);
    // 发送客机昵称
    emit statusChange("发送自身昵称...");
    auto nick = qstring_to_char(input_nick);
    send(sock , nick , strlen(nick) , 0);
}
