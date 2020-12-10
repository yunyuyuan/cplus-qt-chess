#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include "../../components/button/button.h"
#include <netinet/in.h>

class ConnectWindow: public QWidget{
public:
    Button* tab_create;
    Button* tab_join;
    Button* stop;
    Button* start;

    QLabel* label_ip;
    QLineEdit* input_nick;
    QLineEdit* input_ip;
    QLabel* status;

    bool connecting = false;
    bool is_create = true;
    int sock = 0;

    void setupUi();
    explicit ConnectWindow();

private:
    void switchToCreate();
    void switchToJoin();
    void doConnect();
    int SocketServer();
    int SocketClient();
};