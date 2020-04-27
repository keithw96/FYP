cmake_minimum_required(VERSION 3.1)

project(FYP)

# set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(FYP Main.cpp Game.h Game.cpp Gamestates.h Player.h Player.cpp Tile.h Tile.cpp Animation.h Animation.cpp Coin.h Coin.cpp Goal.h Goal.cpp Pipe.h Pipe.cpp Enemy.h Enemy.cpp Play.h Play.cpp MainMenuScene.h MainMenuScene.cpp)

target_link_libraries(FYP sfml-graphics sfml-audio)





