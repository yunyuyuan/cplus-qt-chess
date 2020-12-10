#include <QPushButton>


class Button : public QPushButton{
public:
    Button();
    explicit Button(const QString& text, QWidget* parent);

    void setupUi();
};