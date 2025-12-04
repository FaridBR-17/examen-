#!/bin/bash
echo "Compilando Sistema de Inventario..."

# Limpiar
rm -rf build 2>/dev/null
mkdir build
cd build

# Configurar
cmake -DCMAKE_BUILD_TYPE=Release ..

# Compilar
make -j$(nproc)

# Optimizar tamaño
strip --strip-all inventario-app

echo "Compilación completada!"
echo "Ejecutable: build/inventario-app"
