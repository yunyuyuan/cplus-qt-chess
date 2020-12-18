#include <QtCore/QFile>
#include "button.h"
#include <QVariant>

Button::Button(const QString& text, QWidget* parent){
    this->setText(text);
    this->setParent(parent);
    this->setProperty("class", QVariant("common-button"));
    this->setupUi();
}

void Button::setupUi() {
    this->setStyleSheet(utils::get_qss("../components/button/button.css").c_str());
}
