//@File: Meant to help print special characters to terminal
#ifndef SPECIAL_PRINTS_H
#define SPECIAL_PRINTS_H

#include <string>
#include <sstream> // std::stringstream

namespace Checkers {

namespace Printing {

    constexpr auto underline {"\033[4m"};
    constexpr auto closeUnderline {"\033[0m"};

    inline std::string underlineChar(const char to_underline) {
        std::stringstream underlined_char;
        underlined_char << underline << to_underline << closeUnderline;
        return underlined_char.str();
    }

} // end of Printing namespace

} // end of Checkers namespace


#endif
