#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>

class ConnectWindow: public QWidget{
public:
    QLabel* label;

    void setupUi();
    explicit ConnectWindow();
};