#ifndef C_BOARD_H
#define C_BOARD_H

#include <cmath>
#include <QtWidgets/QFrame>
#include <QPainter>
#include <QVariant>
#include <QMouseEvent>
#include <QtWidgets/QLabel>
#include "../utils.h"
#include "../chess/chess.h"

class Board: public QFrame{
Q_OBJECT
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
public:
    explicit Board(QWidget* parent = nullptr);
    int min_pos;
    int max_pos;
    bool turn_on;
    QPoint candidate_pos;
    Chess* candidate;
    QVector<QPoint> list;
    void recv_chess(QPoint pos);
signals:
    void put_chess(int, int);

};

#endif //C_BOARD_H
