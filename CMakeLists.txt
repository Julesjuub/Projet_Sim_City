cmake_minimum_required(VERSION 3.23)
project(Projet_S1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet_S1 main.c Initialisation.c Biblio.h)

target_link_libraries(Projet_S1 -lmingw32 -lalleg44)
