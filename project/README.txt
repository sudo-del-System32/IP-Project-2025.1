rm *.o 
rm *.exe 
gcc -Wall -Wextra -Wpedantic -std=c99 -g -O0 -c *.c 
gcc -o teste.exe *.o
./teste.exe