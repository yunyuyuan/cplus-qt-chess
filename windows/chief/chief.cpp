#include "chief.h"
#include <string>

Chief::Chief() {
    connectWindow = new ConnectWindow();
    gameWindow = new GameWindow();
    connect(connectWindow, &ConnectWindow::open_window, this, &Chief::do_open_game_window);
    connect(gameWindow, &GameWindow::open_window, this, &Chief::do_open_connect_window);
    connectWindow->show();
}

void Chief::do_open_connect_window() {
    connectWindow->show();
}

void Chief::do_open_game_window(int sock, char *my_name, char *other_name, bool turn_on) {
    gameWindow->initInfo(sock, my_name, other_name, turn_on);
    gameWindow->show();
    // 打开游戏窗口时自动关闭连接窗口
    connectWindow->hide();
}