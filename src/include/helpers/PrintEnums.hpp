//@File: Contains operator<< overrides for printing enums
#ifndef PRINT_ENUMS_HPP
#define PRINT_ENUMS_HPP

// Standard Includes
#include <iostream>
#include <type_traits>

// 3rd Party Includes

// Our Includes
#include "pieces.h"

// use inline to not break "one definition rule"
template <typename T, typename = typename std::enable_if<std::is_enum<T>::value>::type>
inline std::ostream &operator<<(std::ostream &os, const T& enum_item) {
    return os << static_cast<typename std::underlying_type<T>::type>(enum_item);
}

#endif
