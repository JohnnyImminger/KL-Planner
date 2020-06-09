cmake_minimum_required(VERSION 3.16)
project(KL_Planner)

set(CMAKE_CXX_STANDARD 14)

add_executable(KL_Planner main.cpp Raum.cpp Raum.h Klausur.cpp Klausur.h Anmeldung.cpp Anmeldung.h Student.cpp Student.h Professor.cpp Professor.h ReadInput.cpp ReadInput.h Utility.cpp Utility.h Algorithmus.cpp Algorithmus.h)