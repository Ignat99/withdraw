#!/bin/sh
astyle --style=kr cat.c
gcc cat.c
pmccabe cat.c
./a.out
