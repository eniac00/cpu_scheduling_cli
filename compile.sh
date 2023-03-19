#!/bin/sh

gcc -o cpu -g -Wall -fsanitize=address main.c

echo "Compilation done!"

