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
    uint16_t input_port_text;

    void setupUi();
    explicit ConnectWindow();

private:
    void switchToCreate();
    void switchToJoin();
    void parseIp();

    void doConnect();
    void status_change(const char*);
    void server_finish(int, int);
    void client_finish(int);
    void cancelConnect();
};

// ********** worker **********
class ServerWorker : public QThread{
Q_OBJECT
public:
    uint16_t input_port_text;
    const char* input_nick;
    ServerWorker(uint16_t, const char*);
    void run() override;
signals:
    void statusChange(const char* str);
    void resultReady(const int sock, const int client);
};

class ClientWorker : public QThread{
Q_OBJECT
public:
    uint16_t input_port_text;
    const char* input_ip_text;
    const char* input_nick;
    ClientWorker(uint16_t, const char*, const char*);
    void run() override;
signals:
    void statusChange(const char* str);
    void resultReady(const int sock);
};

