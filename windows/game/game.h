#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>

class GameWindow : public QWidget{
Q_OBJECT
public:
    QFrame body;
    QFrame menu;

    explicit GameWindow();
    void setupUi();
signals:
    void open_window();
};