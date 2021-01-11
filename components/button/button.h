#ifndef BUTTON_HEAD
#define BUTTON_HEAD

#include <QPushButton>
#include "../utils.h"

class Button : public QPushButton{
public:
    explicit Button(const QString& text, QWidget* parent);

    void setupUi();
};


#endif