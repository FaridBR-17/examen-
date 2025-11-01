cmake_minimum_required(VERSION 3.10)
project(GestionEstudiantes)

set(CMAKE_CXX_STANDARD 17)

# Incluir directorios
include_directories(include)

# Archivos fuente
set(SOURCES src/estudiante.cpp src/main.cpp)

# Ejecutable principal
add_executable(gestion_estudiantes ${SOURCES})
