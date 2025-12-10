# gcc src/main.cpp -Wall -o test

EXE="pipes"

cmake .

make

./$EXE
