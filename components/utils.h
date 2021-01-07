#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include <QStyle>

namespace utils {
    static std::string get_qss(const char *filename) {
        std::ifstream fp(filename);
        std::string content( (std::istreambuf_iterator<char>(fp) ),
                             (std::istreambuf_iterator<char>()) );
        return content;
    }
    static void refresh_style(QWidget* widget){
        widget->style()->unpolish(widget);
        widget->style()->polish(widget);
        widget->update();
    }
    static int blank_size = 40;
    static int lines_count = 8;
    static int interval = 30;
    static int win_size = 5;
    static int wait_time = 15;
}

#endif