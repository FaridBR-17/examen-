#!/bin/bash
echo "=========================================="
echo "COMPILADOR DEL SISTEMA DE INVENTARIO"
echo "=========================================="

# Verificar si Qt5 está instalado
if ! command -v qmake &> /dev/null; then
    echo "ERROR: Qt5 no está instalado."
    echo "Instale con: sudo apt install qt5-default"
    exit 1
fi

# Verificar si g++ está instalado
if ! command -v g++ &> /dev/null; then
    echo "ERROR: g++ no está instalado."
    echo "Instale con: sudo apt install g++"
    exit 1
fi

# Verificar SQLite3
if ! command -v sqlite3 &> /dev/null; then
    echo "ERROR: SQLite3 no está instalado."
    echo "Instale con: sudo apt install sqlite3 libsqlite3-dev"
    exit 1
fi

# Crear archivo .pro para qmake
cat > inventario.pro << 'EOF'
QT += core gui sql widgets
CONFIG += c++17
TARGET = inventario
TEMPLATE = app
SOURCES += main.cpp
EOF

# Mover el código a main.cpp si no existe
if [ ! -f "main.cpp" ]; then
    echo "ERROR: No se encuentra main.cpp"
    echo "Guarda el código como main.cpp en esta carpeta"
    exit 1
fi

# Compilar
echo "Compilando con qmake..."
qmake inventario.pro
echo "Ejecutando make..."
make -j$(nproc)

# Verificar compilación
if [ -f "inventario" ]; then
    echo "=========================================="
    echo "¡COMPILACIÓN EXITOSA!"
    echo "=========================================="
    echo "Ejecutable: ./inventario"
    echo "Tamaño: $(du -h inventario | cut -f1)"
    
    # Optimizar tamaño
    echo "Optimizando tamaño del ejecutable..."
    strip --strip-all inventario
    echo "Tamaño final: $(du -h inventario | cut -f1)"
    
    # Mostrar dependencias
    echo "=========================================="
    echo "Para ejecutar necesitas:"
    echo "1. libqt5core5"
    echo "2. libqt5widgets5"
    echo "3. libqt5sql5"
    echo "4. libsqlite3-0"
    echo ""
    echo "Instalar en Ubuntu/Debian:"
    echo "sudo apt install libqt5core5 libqt5widgets5 libqt5sql5 libsqlite3-0"
    echo "=========================================="
else
    echo "ERROR: La compilación falló."
    exit 1
fi
