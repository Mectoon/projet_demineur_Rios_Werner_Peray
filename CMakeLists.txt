cmake_minimum_required(VERSION 4.1)
project(projet_demineur_Rios_Werner_Peray C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_demineur_Rios_Werner_Peray main.c
        jeu.c
        jeu.h
        sauvegarde.c
        sauvegarde.h)
