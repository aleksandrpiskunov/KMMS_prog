#!/bin/bash

MAIN="main.cpp"
OUT="example"

# Удалить старый бинарник, если есть
rm -f "$OUT"

# Компиляция с нужной кодировкой исходника
g++ -finput-charset=UTF-8 -o "$OUT" "$MAIN"

# Запуск, если компиляция успешна
if [[ -f "$OUT" ]]; then
    ./"$OUT"
fi
