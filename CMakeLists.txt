cmake_minimum_required(VERSION 3.17)
project(pvz)

set(CMAKE_CXX_STANDARD 14)

add_executable(source main.cpp painter.cpp painter.h board.cpp board.h common.h object.cpp object.h game.cpp game.h market.cpp market.h Plants.cpp Plants.h zombie.cpp zombie.h)