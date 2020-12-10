#include <QApplication>
#include "windows/connect/connect.h"

int main(int argc, char* argv[]){
    QApplication a (argc, argv);
    ConnectWindow connectWindow;
    return QApplication::exec();
}
