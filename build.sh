#!/bin/bash

# Argument 1 is the c file
# Argument 2 is the init file

mkdir -p tmp
mkdir -p obj

cc65 -Oi src/$1.c --add-source -o tmp/$1.s -Iheaders/
ca65 tmp/$1.s -o obj/$1.o
ca65 src/$2.s -o obj/$2.o
ld65 -C cfg/$1.cfg -o $1.nes obj/$2.o obj/$1.o nes.lib
