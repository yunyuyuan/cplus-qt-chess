#include "board.h"

using namespace utils;

static void move_chess (Chess* chess, QPoint pos){
    chess->move(interval*pos.x()+blank_size-interval/2, interval*pos.y()+blank_size-interval/2);
}

static QVector<QPoint> check_win (const QVector<QPoint>& lis){
    // 右, 下, 右上, 右下
    auto shifts = QVector<QPoint>{QPoint(1, 0), QPoint(0, 1), QPoint(1, -1), QPoint(1, 1)};
    QVector<QPoint> need;
    for (QPoint pos:lis){
        need.clear();
        int start_x = pos.x();
        int start_y = pos.y();
        for (QPoint shift:shifts){
            bool found = true;
            for (int i=1;i<win_size;i++){
                auto point = QPoint(start_x+i*shift.x(), start_y+i*shift.y());
                if (lis.contains(point)){
                    need.append(point);
                    continue;
                }else{
                    found = false;
                    break;
                }
            }
            if (found) {
                need.append(pos);
                return need;
            }
        }
    }
    return QVector<QPoint>{};
}

void Board::paintEvent(QPaintEvent* e) {
    // 画线
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    for (int i=0;i<lines_count;i++){
        // 横
        painter.drawLine(blank_size, i*interval+blank_size, (lines_count-1)*interval+blank_size, i*interval+blank_size);
        // 竖
        painter.drawLine(i*interval+blank_size, blank_size, i*interval+blank_size, (lines_count-1)*interval+blank_size);
    }
    QFrame::paintEvent(e);
}

void Board::mouseMoveEvent(QMouseEvent* e) {
    if (!turn_on || game_over) return;
    int x = e->x();
    int y = e->y();
    // 是否在范围内
    if (x >= min_pos && y >= min_pos && x < max_pos && y < max_pos){
        int pos_x = ceil((x - min_pos) / interval);
        int pos_y = ceil((y - min_pos) / interval);
        candidate_pos = QPoint(pos_x, pos_y);
        if (my_pos_list.contains(candidate_pos) || other_pos_list.contains(candidate_pos)){
            if (!candidate->isHidden()){
                candidate->hide();
            }
            return;
        };
        if (candidate->isHidden()){
            candidate->show();
        }
        move_chess(candidate, candidate_pos);
    }
}

void Board::mouseReleaseEvent(QMouseEvent* e) {
    if (!turn_on || game_over || e->button() != Qt::LeftButton) return;
    emit put_chess(candidate_pos.x(), candidate_pos.y());
}

void Board::leaveEvent(QEvent *event) {
    if (!candidate->isHidden()){
        candidate->hide();
    }
}

void Board::recv_chess(QPoint pos, bool is_me){
    auto new_chess = new Chess(this);
    new_chess->setProperty("color", is_me?my_color:other_color);
    auto point = QPoint(pos.x(), pos.y());
    move_chess(new_chess, point);
    new_chess->show();
    if (is_me){
        my_pos_list.append(point);
        my_chess_list.append(new_chess);
    }else{
        other_pos_list.append(point);
        other_chess_list.append(new_chess);
    }
    this->setStyleSheet(get_qss("../components/board/board.css").c_str());
    QVector<QPoint> my_win = check_win(my_pos_list);
    bool end = false;
    if (!my_win.empty()){
        end = true;
        for (QPoint p:my_win){
            int idx = my_pos_list.indexOf(p);
            auto chess = my_chess_list.at(idx);
            chess->setProperty("active", QVariant("t"));
            refresh_style(chess);
        }
    }else {
        QVector<QPoint> other_win = check_win(other_pos_list);
        if (!other_win.empty()) {
            end = true;
            for (QPoint p:other_win){
                int idx = other_pos_list.indexOf(p);
                auto chess = other_chess_list.at(idx);
                chess->setProperty("active", QVariant("t"));
                refresh_style(chess);
            }
        }
    }
    if (end){
        game_over = true;
        if (!candidate->isHidden()){
            candidate->hide();
        }
        this->setCursor(Qt::ForbiddenCursor);
    }
}

Board::Board(QWidget *parent):QFrame(parent) {
    this->setObjectName("board");
    auto size = (lines_count-1)*interval+blank_size*2;
    this->setFixedSize(size, size);
    this->setMouseTracking(true);
    turn_on = false;
    game_over = false;
    min_pos = blank_size - interval/2;
    max_pos = size - min_pos;

    candidate = new Chess(this);
    candidate->hide();
    candidate->setProperty("candidate", QVariant("t"));

    this->setStyleSheet(get_qss("../components/board/board.css").c_str());
}
