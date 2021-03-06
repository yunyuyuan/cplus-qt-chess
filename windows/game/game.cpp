#include "game.h"

using namespace utils;

GameWindow::GameWindow() {
    initing = true;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::update_timer);
    this->setupUi();
}

void GameWindow::setupUi() {
    this->setObjectName("game");
    body = new QFrame(this);
    body->setProperty("class", "body");
    board = new Board(body);
    connect(board, &Board::game_over_event, this, &GameWindow::gameOver);
    auto body_layout = new QHBoxLayout();
    body_layout->setSpacing(0);
    body_layout->setContentsMargins(0, 0, 0, 0);
    body_layout->addWidget(board);
    body->setLayout(body_layout);

    menu = new QFrame(this);
    menu->setProperty("class", "menu");
    menu->setFixedWidth(160);

    player_me = new QFrame(menu);
    player_me->setProperty("class", "player");
    my_name = new QLabel(player_me);
    my_name->setProperty("class", "name");
    my_time = new QLabel(player_me);
    my_time->setProperty("class", "time");
    auto player_me_layout = new QVBoxLayout();
    player_me_layout->addWidget(my_name);
    player_me_layout->addWidget(my_time);
    player_me->setLayout(player_me_layout);

    player_other = new QFrame(menu);
    player_other->setProperty("class", "player");
    other_name = new QLabel(player_other);
    other_name->setProperty("class", "name");
    other_time = new QLabel(player_other);
    other_time->setProperty("class", "time");
    auto player_other_layout = new QVBoxLayout();
    player_other_layout->addWidget(other_name);
    player_other_layout->addWidget(other_time);
    player_other->setLayout(player_other_layout);

    menu_mid = new QFrame(menu);
    menu_mid->setProperty("class", "mid");
    chat_area = new QPlainTextEdit(menu_mid);
    input_chat = new QLineEdit(menu_mid);
    btn_send_chat = new Button("发送", menu_mid);
    connect(btn_send_chat, &Button::clicked, this, &GameWindow::send_chat);
    btn_exit = new Button("退出游戏", menu_mid);
    auto menu_mid_layout = new QGridLayout();
    menu_mid_layout->addWidget(chat_area, 0, 0, 4, 4);
    menu_mid_layout->addWidget(input_chat, 4, 0, 1, 3);
    menu_mid_layout->addWidget(btn_send_chat, 4, 3, 1, 1);
    menu_mid_layout->addWidget(btn_exit, 5, 2, 1, 2);
    menu_mid->setLayout(menu_mid_layout);

    auto menu_layout = new QVBoxLayout();
    menu_layout->setContentsMargins(0, 0, 0, 0);
    menu_layout->setSpacing(0);
    menu_layout->addWidget(player_other, 2);
    menu_layout->addWidget(menu_mid, 3);
    menu_layout->addWidget(player_me, 2);
    menu->setLayout(menu_layout);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(body);
    layout->addWidget(menu);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(layout);
    this->setStyleSheet(utils::get_qss("../windows/game/game.css").c_str());
}

void GameWindow::initInfo(QTcpSocket* socket_, const QString& nick_, bool turn_on_) {
    socket = socket_;
    auto nick = nick_.toStdString().c_str();
    my_name->setText(nick);
    connect(socket, &QTcpSocket::readyRead, this, &GameWindow::recvMsg);
    connect(board, &Board::put_chess, this, &GameWindow::put_chess);
    if (turn_on_){
        board->my_color = "black";
        board->other_color = "white";
        this->change_turn(turn_on_);
        // 如果是主机就先发送昵称
        socket->write(nick);
    }else{
        board->my_color = "white";
        board->other_color = "black";
        this->change_turn(turn_on_);
    }
}

void GameWindow::put_chess(int x, int y) {
    if (!turn_on) return;
    char s[100];
    sprintf(s, "%d,%d", x, y);
    socket->write(s);
    board->recv_chess(QPoint(x, y), true);
    this->change_turn(false);
}

void GameWindow::send_chat() {
    auto text = input_chat->text();
    socket->write(("chat:" + text).toStdString().c_str());
    chat_area->setPlainText(chat_area->toPlainText() + "\n" + text.toStdString().c_str());
}

void GameWindow::change_turn(bool b) {
    turn_on = b;
    board->turn_on = turn_on;
    QFrame* active;
    QFrame* deactive;
    QLabel* active_time;
    QLabel* deactive_time;
    if (b){
        active = player_me;
        deactive = player_other;
        active_time = my_time;
        deactive_time = other_time;
    }else{
        active = player_other;
        deactive = player_me;
        active_time = other_time;
        deactive_time = my_time;
    }
    active->setProperty("active", "t");
    refresh_style(active);
    deactive->setProperty("active", "f");
    refresh_style(deactive);
    if (active_time->isHidden()) {
        active_time->show();
        active_time->setText(std::to_string(wait_time).c_str());
    }
    if (!deactive_time->isHidden()) {
        deactive_time->hide();
        deactive_time->setText("");
    }
    timer_count = wait_time;
    timer->start(1000);
}

void GameWindow::update_timer() {
    timer_count --;
    (turn_on?my_time:other_time)->setText(std::to_string(timer_count).c_str());
    if (timer_count == 0){
        timer->stop();
        board->gameover_with_timeout();
    }
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
        if (mid == -1){
            if(std_str.find("chat:") == 0){
                chat_area->setPlainText(chat_area->toPlainText() + "\n" + std_str.substr(5).c_str());
            }
        }else{
            int x = std::stoi(std_str.substr(0, mid));
            int y = std::stoi(std_str.substr(mid+1));
            board->recv_chess(QPoint(x, y), false);
            this->change_turn(true);
        }
    }
}

void GameWindow::gameOver(bool i_win) {
    timer->stop();
}