#include "game.h"

GameWindow::GameWindow() {
    this->setupUi();
}

void GameWindow::setupUi() {
    this->setObjectName("game");
    body = new QFrame(this);
    body->setProperty("class", "body");

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

void GameWindow::initInfo(int a, char *b, char *c, bool d) {
    sock = a;
    my_name->setText(b);
    other_name->setText(c);
    turn_on = d;
}
