#include <QApplication>
#include "windows/chief/chief.h"

int main(int argc, char* argv[]){
    QApplication a (argc, argv);
    new Chief();
    int status = QApplication::exec();
    printf("Application exit with code(%d)\n", status);
    return status;
}
