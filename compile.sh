#!/usr/bin/bash

gcc -o cpu -g -Wall -fsanitize=address main.c

echo "Compilation done!"

