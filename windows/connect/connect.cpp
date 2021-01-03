#include "connect.h"


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
    input_nick->setText("哈哈");
    input_ip = new QLineEdit(this);
    connect(input_ip, &QLineEdit::textChanged, this, &ConnectWindow::parseIp);
    input_ip->setText("127.0.0.1:8989");

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

ConnectWindow::ConnectWindow(){
    setupUi();
}

ConnectWindow::~ConnectWindow() {
    try{
        tcp_server->close();
        tcp_socket->close();
    } catch (int) {}
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
    if (is_create) {
        status->setText("创建服务...");
        tcp_server = new QTcpServer(this);
        tcp_server->listen(QHostAddress(input_ip_text), input_port_text);
        connect(tcp_server, &QTcpServer::newConnection, this, &ConnectWindow::new_client);
        status->setText("等待其他玩家加入...");
    }else{
        status->setText("准备加入...");
        tcp_socket = new QTcpSocket(this);
        tcp_socket->connectToHost(QHostAddress(input_ip_text), input_port_text);
        if(tcp_socket->waitForConnected()){
            status->setText("加入成功!");
            emit open_window(tcp_socket, input_nick->text(), false);
        }else{
            status->setText(QString("出错了:") + tcp_socket->errorString());
        }
    }
}

void ConnectWindow::new_client() {
    tcp_socket = tcp_server->nextPendingConnection();
    status->setText("玩家已加入!");
    emit open_window(tcp_socket, input_nick->text(), true);
}

void ConnectWindow::cancelConnect() {
    connecting = false;
}