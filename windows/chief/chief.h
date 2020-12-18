#include "../connect/connect.h"
#include "../game/game.h"

class Chief: public QObject{
public:
    ConnectWindow* connectWindow;
    GameWindow* gameWindow;

    explicit Chief();

public slots:
    void do_open_connect_window();
    void do_open_game_window(int, char*, char*, bool);
};