cmake_minimum_required(VERSION 3.23)
project(amoba_NHF C)

set(CMAKE_C_STANDARD 99)

add_executable(amoba_NHF program.c board.c base.h menu.c board.h menu.h moves.c moves.h base.c)
