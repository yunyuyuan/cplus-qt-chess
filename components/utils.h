#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>

namespace utils {
    static std::string get_qss(const char *filename) {
        std::ifstream fp(filename);
        std::string content( (std::istreambuf_iterator<char>(fp) ),
                             (std::istreambuf_iterator<char>()) );
        return content;
    }
    static int blank_size = 40;
    static int lines_count = 15;
    static int interval = 40;
}

#endif