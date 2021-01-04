#include "lines.h"

void Lines::paintEvent(QPaintEvent* e) {
    // 画线
    auto painter = new QPainter();
    QFrame::paintEvent(e);
}
