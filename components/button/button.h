#ifndef BUTTON_HEAD
#define BUTTON_HEAD

#include <QPushButton>
#include "../utils.h"

class Button : public QPushButton{
public:
    Button();
    explicit Button(const QString& text, QWidget* parent);

    void setupUi();

    const QString &get_qss(const char string[11]);
};


#endif