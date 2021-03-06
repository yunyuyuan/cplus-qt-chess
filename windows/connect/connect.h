#ifndef CONNECT_HEAD
#define CONNECT_HEAD

#include <QtWidgets/QWidget>
#include <QObject>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLabel>
#include <QtCore/Qt>
#include <QtCore/QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include "../../components/button/button.h"

class ConnectWindow: public QWidget {
Q_OBJECT
public:
    Button* tab_create;
    Button* tab_join;
    Button* stop;
    Button* start;

    QLineEdit* input_nick;
    QLineEdit* input_ip;
    QLabel* status;

    bool connecting = false;
    bool is_create = true;
    QTcpServer* tcp_server;
    QTcpSocket* tcp_socket;
    QString input_ip_text;
    int input_port_text;

    void setupUi();
    ConnectWindow();
    ~ConnectWindow();

private:
    void parseIp();

signals:
    void open_window(QTcpSocket*, QString, bool);
private slots:
    void switchToCreate();
    void switchToJoin();

    void doConnect();
    void new_client();
    void cancelConnect();

};

#endif