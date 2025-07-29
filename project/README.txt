rm *.o 
rm *.exe 
gcc -Wall -Wextra -Wpedantic -g -O0 -c *.c 
gcc -o teste.exe *.o
.\teste.exe