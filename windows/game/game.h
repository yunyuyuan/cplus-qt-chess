#ifndef GAME_HEAD
#define GAME_HEAD

#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QVariant>
#include <QTcpSocket>
#include <QTimer>
#include <QtNetwork/QTcpServer>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include "../../components/utils.h"
#include "../../components/board/board.h"
#include "../../components/button/button.h"

class GameWindow : public QWidget{
Q_OBJECT
public:
    QFrame* body;
    Board* board;

    QFrame* menu;

    QFrame* menu_mid;

    QPlainTextEdit* chat_area;
    QLineEdit* input_chat;
    Button* btn_send_chat;
    
    Button* btn_exit;

    QFrame* player_me;
    QLabel* my_name;
    QLabel* my_time;
    QFrame* player_other;
    QLabel* other_name;
    QLabel* other_time;

    QTcpSocket* socket;
    bool turn_on;
    bool initing;
    QTimer* timer;
    int timer_count;

    GameWindow();
    void initInfo(QTcpSocket*, const QString&, bool);

private:
    void setupUi();
    void put_chess(int, int);
    void send_chat();
    void change_turn(bool);
    void update_timer();
signals:
    void open_window();
private slots:
    void recvMsg();
    void gameOver(bool);
};


#endif