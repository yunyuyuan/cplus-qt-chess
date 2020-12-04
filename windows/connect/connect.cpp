#include "connect.h"

void ConnectWindow::setupUi() {
    this->label = new QLabel(this);
    this->label->setText("哈哈");
//    QLayout* layout = new QGridLayout(this);
//    layout->addWidget(this->label);
//    this->setLayout(layout);
}

ConnectWindow::ConnectWindow() {
    this->setupUi();
}
