#!/bin/bash
set -euo pipefail

# Убедитесь, что активирована среда Emscripten
# source /path/to/emsdk_env.sh

# Пусть исходник лежит в той же папке: compute.cpp
EMCPP="./compute.cpp"
OUTPUT_JS="app.js"

# Сборка: экспортируем функцию compute и подключаем ccall/ccall
emcc "$EMCPP" -O2 \
  -s WASM=1 \
  -s EXPORTED_FUNCTIONS="['_compute']" \
  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall','cwrap']" \
  -o "$OUTPUT_JS"

echo "Сборка завершена. Файлы: app.js, app.wasm (появятся рядом)."
