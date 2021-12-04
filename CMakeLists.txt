cmake_minimum_required(VERSION 3.20)
project(Task4_Game)

set(CMAKE_CXX_STANDARD 14)

add_executable(Task4_Game
        main.cpp Player.cpp Player.h GameManager.cpp GameManager.h Cells/Cell.h Cells/CellFactory.cpp Cells/CellFactory.h Cells/PossibleCells.cpp Cells/PossibleCells.h)
