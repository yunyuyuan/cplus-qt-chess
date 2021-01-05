#include "board.h"

using namespace utils;

static void move_chess (Chess* chess, int x, int y){
    chess->move(interval*x+blank_size-interval/2, interval*y+blank_size-interval/2);
}

void Board::paintEvent(QPaintEvent* e) {
    // 画线
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    for (int i=0;i<lines_count;i++){
        // 横
        painter.drawLine(blank_size, i*interval+blank_size, lines_count*interval, i*interval+blank_size);
        // 竖
        painter.drawLine(i*interval+blank_size, blank_size, i*interval+blank_size, lines_count*interval);
    }
    QFrame::paintEvent(e);
}

void Board::mouseMoveEvent(QMouseEvent* e) {
    if (!turn_on) return;
    int x = e->x();
    int y = e->y();
    // 是否在范围内
    if (x >= min_pos && y >= min_pos && x < max_pos && y < max_pos){
        int real_x = x-min_pos;
        int real_y = y-min_pos;
        candidate_pos = QPoint(ceil(real_x/interval), ceil(real_y/interval));
        if (candidate->isHidden()){
            candidate->show();
        }
        move_chess(candidate, candidate_pos.x(), candidate_pos.y());
    }
}

void Board::mouseReleaseEvent(QMouseEvent* e) {
    if (!turn_on || e->button() != Qt::LeftButton) return;
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
    move_chess(new_chess, pos.x(), pos.y());
    new_chess->show();
    pos_list.append(pos);
    chess_list.append(new_chess);
    this->setStyleSheet(get_qss("../components/board/board.css").c_str());
}

Board::Board(QWidget *parent):QFrame(parent) {
    this->setObjectName("board");
    auto size = (lines_count+1)*blank_size;
    this->setFixedSize(size, size);
    turn_on = false;
    min_pos = blank_size - interval/2;
    max_pos = size - min_pos;
    this->setMouseTracking(true);

    candidate = new Chess(this);
    candidate->hide();
    candidate->setProperty("candidate", QVariant("t"));
    this->setStyleSheet(get_qss("../components/board/board.css").c_str());
}
