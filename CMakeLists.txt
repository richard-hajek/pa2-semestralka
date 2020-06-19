cmake_minimum_required(VERSION 3.16)
project(semester-project)
set(CMAKE_CXX_STANDARD 14)

add_executable(project
        src/main.cpp
        src/utils/TSVReader.h
        src/utils/TSVWriter.h
        src/Game.h src/Game.cpp
        src/fragments/Fragment.h
        src/fragments/Display.h src/fragments/Display.cpp
        src/fragments/GameStats.h src/fragments/GameStats.cpp
        src/fragments/Terrain.h src/fragments/Terrain.cpp
        src/fragments/Towers.h src/fragments/Towers.cpp
        src/fragments/Player.h src/fragments/Player.cpp
        src/fragments/Enemies.h src/fragments/Enemies.cpp
        src/fragments/Rounds.h src/fragments/Rounds.cpp
        src/fragments/Help.cpp
        src/units/Drawable.h src/units/Drawable.cpp
        src/units/Tile.h src/units/Tile.cpp
        src/units/Tower.h src/units/Tower.cpp
        src/units/Enemy.h src/units/Enemy.cpp
        src/utils/pathfinding.h src/utils/Log.h src/lib/ccolor.h)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(project ${CURSES_LIBRARIES})