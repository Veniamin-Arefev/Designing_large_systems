cmake_minimum_required(VERSION 3.22)
project(Designing_large_systems)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOGEN_PARALLEL)

add_executable(task_1 task1/main.cpp)

add_executable(task_2_ex1_1 task2/ex1_1.cpp)
add_executable(task_2_ex1_2 task2/ex1_2.cpp)
add_executable(task_2_ex2 task2/ex2.cpp)

add_executable(task_3 task3/main.cpp)

add_executable(task_4 task4/tree.h task4/tree.cpp)

add_executable(task_8 task8/main.cpp)

add_executable(test task1/test.cpp)
