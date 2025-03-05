cmake_minimum_required(VERSION 3.29)
project(Security2_RSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(Security2_RSA main.cpp)
add_executable(testFile testFile.cpp RSA.h)
add_executable(signature signature.cpp RSA.h)