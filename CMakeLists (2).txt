cmake_minimum_required(VERSION 3.9)
project(code)

set(CMAKE_C_STANDARD 99)

add_executable(code
        main.c
        Room.c
        Room.h
        SystemRoom.c
        SystemRoom.h date.c date.h date_time_utils.c date_time_utils.h time.c time.h)
