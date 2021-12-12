cmake_minimum_required(VERSION 3.20)
project(Task4_Game)

set(CMAKE_CXX_STANDARD 23)

add_executable(Task4_Game
        main.cpp
        Players/Player.cpp
        Players/Player.h
        GameManager.cpp
        GameManager.h
        Cells/Cell.h
        Cells/CellFactory.cpp
        Cells/CellFactory.h
        Cells/PossibleCells.cpp
        Cells/PossibleCells.h
        Field/Field.cpp
        Field/Field.h
        Actions/Action.h
        Actions/ActionFactory.cpp
        Actions/ActionFactory.h
        Actions/PossibleActions.cpp
        Actions/PossibleActions.h Players/Bot.cpp Players/Bot.h Exceptions/Exception.cpp Exceptions/Exception.h Players/HumanPlayer.cpp Players/HumanPlayer.h Printer.cpp Printer.h Field/GeneralField.cpp Field/GeneralField.h Field/OpenField.cpp Field/OpenField.h)
