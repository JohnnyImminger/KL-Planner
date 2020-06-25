cmake_minimum_required(VERSION 3.16)
project(KL_Planner)

set(CMAKE_CXX_STANDARD 20)

add_executable(KL_Planner main.cpp Room.cpp Room.h Exam.cpp Exam.h Registration.cpp Registration.h Student.cpp Student.h Professor.cpp Professor.h ReadInput.cpp ReadInput.h Utility.cpp Utility.h Algorithm.cpp Algorithm.h)