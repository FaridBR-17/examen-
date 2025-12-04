cmake_minimum_required(VERSION 3.16)
project(InventarioApp VERSION 1.0.0)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración automática Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Encontrar Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql)

# Encontrar SQLite3
find_package(SQLite3 REQUIRED)

# Optimizar tamaño
add_compile_options(-Os -flto -fno-exceptions -fno-rtti)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-s)
endif()

# Archivo fuente principal
add_executable(inventario_app main.cpp)

# Vincular librerías
target_link_libraries(inventario_app
    Qt5::Core
    Qt5::Widgets
    Qt5::Sql
    ${SQLite3_LIBRARIES}
)

# Instalación
install(TARGETS inventario_app DESTINATION bin)