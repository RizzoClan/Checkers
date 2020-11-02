# main cmake for checkers project
cmake_minimum_required(VERSION 2.8)

add_executable(Checkers
    Checkers.cpp
    checkers_logic.cpp
)

# include created libs from other dirs (i.e. board) -- comes after add executable
target_link_libraries(Checkers
    CheckersBoard
)