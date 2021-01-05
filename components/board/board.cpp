#include "board.h"

using namespace utils;

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
        candidate->move(interval*candidate_pos.x()+blank_size-interval/2, interval*candidate_pos.y()+blank_size-interval/2);
    }
}

void Board::mouseReleaseEvent(QMouseEvent *event) {

}

void Board::leaveEvent(QEvent *event) {
    if (!candidate->isHidden()){
        candidate->hide();
    }
}

Board::Board(QWidget *parent):QFrame(parent) {
    this->setProperty("class", QVariant("board"));
    auto size = (lines_count+1)*blank_size;
    this->setFixedSize(size, size);
    min_pos = blank_size - interval/2;
    max_pos = size - min_pos;
    this->setMouseTracking(true);

    candidate = new QLabel(this);
    candidate->setFixedSize(interval, interval);
    candidate->setStyleSheet("QLabel{background: red}");
    candidate->hide();
}
