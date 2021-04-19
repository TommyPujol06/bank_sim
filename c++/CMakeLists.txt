cmake_minimum_required(VERSION 3.7)
project(bank_sim)

set(CMAKE_CXX_STANDARD 20)

add_executable(bank_sim main.cpp clients.cpp clients.h random.h services.cpp services.h)