#include <QtWidgets/QLabel>
#include <Qt>
#include "connect.h"

void ConnectWindow::setupUi() {
    this->tab_create = new Button("创建", this);
    this->tab_join = new Button("加入", this);
    this->stop = new Button("取消", this);
    this->start = new Button("提交", this);
    connect(this->tab_create, &QPushButton::clicked, this, &ConnectWindow::switchToCreate);
    connect(this->tab_join, &QPushButton::clicked, this, &ConnectWindow::switchToJoin);
    connect(this->start, &QPushButton::clicked, this, &ConnectWindow::doConnect);

    this->label_ip = new QLabel("地址:", this);
    this->input_nick = new QLineEdit(this);
    this->input_ip = new QLineEdit(this);
    this->status = new QLabel("", this);
    this->status->setAlignment(Qt::AlignCenter);

    auto* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("昵称:", this), 0, 0, 1, 1);
    layout->addWidget(this->input_nick, 0, 1, 1, 5);
    layout->addWidget(this->label_ip, 1, 0, 1, 1);
    layout->addWidget(this->input_ip, 1, 1, 1, 5);
    layout->addWidget(this->tab_create, 2, 0, 1, 1);
    layout->addWidget(this->tab_join, 2, 1, 1, 1);
    layout->addWidget(this->stop, 2, 4, 1, 1);
    layout->addWidget(this->start, 2, 5, 1, 1);
    layout->addWidget(this->status, 3, 0, 1, 6);
    this->setLayout(layout);
}

ConnectWindow::ConnectWindow() {
    this->setupUi();
    this->show();
}


void ConnectWindow::switchToCreate() {
    this->label_ip->setText("端口:");
    this->is_create = true;
}

void ConnectWindow::switchToJoin() {
    this->label_ip->setText("地址:");
    this->is_create = false;
}

void ConnectWindow::doConnect() {
    if (this->connecting)return;
    this->connecting = true;
    this->status->setText("正在连接...");
    if (this->is_create){
        this->sock = this->SocketServer();
    }else{
        this->sock = this->SocketClient();
    }
    if (this->sock == 0){
        this->status->setText((QString)(this->is_create?"创建":"加入") + "失败");
    }
    this->connecting = false;
}

int ConnectWindow::SocketServer() {
    return 0;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    int new_socket;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == 0){
        return 0;
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt))){
        return 0;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8886);
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0){
        return 0;
    }
    if (listen(sock, 1)<0){
        return 0;
    }
    status->setText("等待玩家连接...");
    if ((new_socket = accept(sock, (struct sockaddr *)&address ,(socklen_t *) &addrlen))< 0){
        return 0;
    }

    return sock;
}

int ConnectWindow::SocketClient() {
    return 0;
}
