#!/bin/bash

# Чтение найденных исходных файлов программы многофайлового проекта в массив
find . -maxdepth 1 -name "*.c" | tr "\n" " " > ./names.log
read -ra files < ./names.log
rm ./names.log

# Создание объектных файлов релизной сборки
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c "${files[@]}"

# Превращение объектных файлов в исполняемый (.exe)
gcc -o "app.exe" "${files[@]//\.c/\.o}" -lm