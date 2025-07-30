cmake_minimum_required(VERSION 3.31)
project(finalmente C)

set(CMAKE_C_STANDARD 99)

add_executable(finalmente  main.c Func_gerais.h Func_gerais.c uf1.h uf1.c people.h people.c Election.h Election.c Candidate.h Candidate.c attendance.h attendance.c vote.h vote.c ui1.h ui1.c)
