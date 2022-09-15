#!/bin/bash

# Поиск мусорных файлов и их удаление
for i in ./*; do
    if ! [[ $i =~ .+\.sh || $i =~ .+\.c || $i =~ .+\.h ]]; then
        rm "$i" 2> ./trash.txt
    fi
done

rm ./trash.txt
