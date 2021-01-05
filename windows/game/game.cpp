#include <QtNetwork/QTcpServer>
#include "game.h"

GameWindow::GameWindow() {
    initing = true;
    this->setupUi();
}

void GameWindow::setupUi() {
    this->setObjectName("game");
    body = new QFrame(this);
    body->setProperty("class", "body");
    board = new Board(body);

    menu = new QFrame(this);
    menu->setProperty("class", "menu");
    menu->setFixedWidth(100);
    my_name = new QLabel();
    other_name = new QLabel();
    menu_mid = new QFrame();
    auto menu_layout = new QVBoxLayout();
    menu_layout->addWidget(other_name);
    menu_layout->addWidget(menu_mid);
    menu_layout->addWidget(my_name);
    menu->setLayout(menu_layout);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(body);
    layout->addWidget(menu);
    this->setLayout(layout);
    this->setGeometry(0, 0, 800, 500);
    this->setStyleSheet(utils::get_qss("../windows/game/game.css").c_str());
}

void GameWindow::initInfo(QTcpSocket* socket_, const QString& nick_, bool turn_on_) {
    socket = socket_;
    auto nick = nick_.toStdString().c_str();
    my_name->setText(nick);
    turn_on = turn_on_;
    board->turn_on = turn_on;
    connect(socket, &QTcpSocket::readyRead, this, &GameWindow::recvMsg);
    connect(board, &Board::put_chess, this, &GameWindow::putChess);
    if (turn_on){
        // 如果是主机就先发送昵称
        socket->write(nick);
    }
}

void GameWindow::putChess(int x, int y) {
    if (!turn_on) return;
    char s[100];
    sprintf(s, "%d,%d", x, y);
    socket->write(s);
    board->recv_chess(QPoint(x, y));
    turn_on = false;
    board->turn_on = turn_on;
}

void GameWindow::recvMsg() {
    QByteArray data = socket->readAll();
    auto std_str = data.toStdString();
    auto msg = std_str.c_str();
    if (initing){
        other_name->setText(msg);
        if (!turn_on) {
            socket->write(my_name->text().toStdString().c_str());
        }
        initing = false;
    }else{
        int mid = std_str.find(',');
        int x = std::stoi(std_str.substr(0, mid));
        int y = std::stoi(std_str.substr(mid+1));
        board->recv_chess(QPoint(x, y));
        turn_on = true;
        board->turn_on = turn_on;
    }
}
