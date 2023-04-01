cmake_minimum_required(VERSION 3.23)
project(stu_book_cd)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(stu_book_cd
        borrow.h
        main.cpp
        newfile.cpp
        queue.h
        sqlist_B.h
        sqlist_S.h
        typedefine.h)
