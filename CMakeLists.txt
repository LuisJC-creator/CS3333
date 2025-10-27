cmake_minimum_required(VERSION 3.22)
project(CS3333 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- HW3 ---
add_executable(hw3
    HW3/main.cpp
    HW3/project3.cpp
)
target_include_directories(hw3 PRIVATE HW3)

# --- Lab 7 ---
add_executable(lab7
    Labs/Lab7/main.cpp
    Labs/Lab7/lab7.cpp
    Labs/Lab7/lab7head.cpp
)
target_include_directories(lab7 PRIVATE Labs/Lab7)

# --- Lab 8 ---
add_executable(lab8
    Labs/Lab8/main.cpp
    Labs/Lab8/lab8.cpp
    Labs/Lab8/lab8head.cpp
)
target_include_directories(lab8 PRIVATE Labs/Lab8)

# Add more labs the same way:
# add_executable(lab9 Labs/Lab9/main.cpp Labs/Lab9/lab9.cpp Labs/Lab9/lab9head.cpp)
# target_include_directories(lab9 PRIVATE Labs/Lab9)
