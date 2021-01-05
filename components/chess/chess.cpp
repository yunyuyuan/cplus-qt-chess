#include "chess.h"

using namespace utils;

Chess::Chess(QWidget* parent):QFrame(parent) {
    this->setProperty("class", QVariant("chess"));
    char s[100];
    sprintf(s, "QFrame{border-radius: %dpx}", interval/2);
    this->setFixedSize(interval, interval);
    this->setStyleSheet(s);
}
