#!/bin/bash
make clean
make
clear
clear
clear
valgrind --leak-check=yes --track-origins=yes ./etapa* exemplo.in