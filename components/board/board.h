#ifndef C_BOARD_H
#define C_BOARD_H

#include <cmath>
#include <QtWidgets/QFrame>
#include <QPainter>
#include <QVariant>
#include <QMouseEvent>
#include <QtWidgets/QLabel>
#include "../utils.h"

class Board: public QFrame{
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
public:
    explicit Board(QWidget* parent = nullptr);
    int min_pos;
    int max_pos;
    QPoint candidate_pos;
    QLabel* candidate;
};

#endif //C_BOARD_H
