cmake_minimum_required(VERSION 3.26)
project(LSOBB_LIBT_ABB C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(LSOBB_LIBT_ABB
        ABB.h
        Envios.h
        LIBT.h
        LSOBB.h
        main.c)
