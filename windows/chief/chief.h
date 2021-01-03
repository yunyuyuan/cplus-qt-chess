#ifndef CHIEF_HEAD
#define CHIEF_HEAD

#include "../connect/connect.h"
#include "../game/game.h"

class Chief: public QObject{
public:
    explicit Chief();

    ConnectWindow* connectWindow;
    GameWindow* gameWindow;

public slots:
    void do_open_connect_window();
    void do_open_game_window(QTcpSocket*, const QString&, bool);
};
#endif