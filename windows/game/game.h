#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QVariant>
#include "../../components/utils.h"

class GameWindow : public QWidget{
Q_OBJECT
public:
    QFrame* body;
    QFrame* menu;
    QFrame* menu_mid;

    QLabel* my_name;
    QLabel* other_name;

    int sock;
    bool turn_on;

    explicit GameWindow();
    void setupUi();
    void initInfo(int, char*, char*, bool);
signals:
    void open_window();
};