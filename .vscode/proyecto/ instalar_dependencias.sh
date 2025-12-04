#!/bin/bash
echo "Instalando dependencias para el proyecto..."

# Actualizar sistema
sudo apt update

# Instalar herramientas de compilación
sudo apt install -y build-essential g++ cmake

# Instalar Qt5 (bibliotecas completas)
sudo apt install -y qt5-default qtbase5-dev qt5-qmake

# Instalar SQLite3
sudo apt install -y sqlite3 libsqlite3-dev

# Instalar herramientas adicionales
sudo apt install -y make git

echo "=========================================="
echo "Dependencias instaladas correctamente."
echo "Versiones instaladas:"
echo "g++: $(g++ --version | head -n1)"
echo "qmake: $(qmake --version | head -n1)"
echo "sqlite3: $(sqlite3 --version)"
echo "=========================================="
