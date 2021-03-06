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
    bool game_over;
    const char* my_color;
    const char* other_color;
    QPoint candidate_pos;
    Chess* candidate;
    QVector<QPoint> my_pos_list;
    QVector<QPoint> other_pos_list;
    QVector<Chess*> my_chess_list;
    QVector<Chess*> other_chess_list;

    void recv_chess(QPoint, bool);
    void gameover_with_timeout();
signals:
    void put_chess(int, int);
    void game_over_event(bool);
};

#endif //C_BOARD_H
