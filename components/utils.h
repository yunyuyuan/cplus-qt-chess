#include <fstream>
#include <string>

#pragma once
namespace utils {
    static std::string get_qss(const char *filename) {
        std::ifstream fp(filename);
        std::string content( (std::istreambuf_iterator<char>(fp) ),
                             (std::istreambuf_iterator<char>()) );
        return content;
    }
}