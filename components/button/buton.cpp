#include <QtCore/QFile>
#include "button.h"
#include <QVariant>
#include <zconf.h>

Button::Button(const QString& text, QWidget* parent){
    this->setText(text);
    this->setParent(parent);
    this->setProperty("class", QVariant("common-button"));
    this->setupUi();
}

void Button::setupUi() {
    QFile styleFile(":/button.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    this->setStyleSheet(style);
}
