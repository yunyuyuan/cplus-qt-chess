#include <QtWidgets/QWidget>
#include <QObject>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLabel>
#include <QtCore/Qt>
#include <QtCore/QThread>
#include "../../components/button/button.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

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
    int sock, client_sock = 0;
    QString input_ip_text;
    int input_port_text;

    void setupUi();
    explicit ConnectWindow();

private:
    void switchToCreate();
    void switchToJoin();
    void parseIp();

    void doConnect();
    void status_change(const char*) const;
    void server_finish(int, int,  char*);
    void client_finish(int,  char*);
    void cancelConnect();
signals:
    void open_window(int, char*, char*);
};

// ********** worker **********
class ServerWorker : public QThread{
Q_OBJECT
public:
    int input_port_text;
    QString input_nick;
    ServerWorker(int, const QString&);
    void run() override;
signals:
    void statusChange(const char*);
    void resultReady(int, int, char*);
};

class ClientWorker : public QThread{
Q_OBJECT
public:
    int input_port_text;
    QString input_nick;
    QString input_ip_text;
    ClientWorker(int, const QString&, const QString&);
    void run() override;
signals:
    void statusChange(const char*);
    void resultReady(int, char*);
};

