# use this to find in main "game" dir
add_library(CheckersEngine
    CheckersEngine.cpp
    CheckersPlayer.cpp
) 

# need compiled .cpp of Board objects
target_link_libraries(CheckersEngine
    CheckersBoard
)
