CC="gcc"
CFLAGS="-g -I/home/brendan/.local/lib/include -L/home/brendan/.local/lib/include -laocfunc"

input="main.c"
output="main"

$CC $CFLAGS -o $output $input

LD_LIBRARY_PATH=/home/brendan/.local/lib/include ./$output
