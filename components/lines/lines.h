#ifndef C_LINES_H
#define C_LINES_H

#include <QtWidgets/QFrame>
#include <QPainter>
#include "../../windows/game/game.h"

class Lines: public QFrame{
    void paintEvent(QPaintEvent *) override;
};

#endif //C_LINES_H
