#ifndef GAME_HEAD
#define GAME_HEAD

#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QVariant>
#include <QTcpSocket>
#include "../../components/utils.h"

class GameWindow : public QWidget{
Q_OBJECT
public:
    QFrame* body;
    QFrame* menu;
    QFrame* menu_mid;

    QLabel* my_name;
    QLabel* other_name;

    QTcpSocket* socket;
    bool turn_on;
    bool initing;

    GameWindow();
    void initInfo(QTcpSocket*, const QString&, bool);

private:
    void setupUi();
    void sendMsg(const char*);
signals:
    void open_window();
private slots:
    void recvMsg();
};


#endif