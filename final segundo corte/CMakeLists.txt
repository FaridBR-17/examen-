cmake_minimum_required(VERSION 3.10)
project(ProyectoEstudiante)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ProyectoEstudiante
    src/main.cpp
    src/Estudiante.cpp
)
