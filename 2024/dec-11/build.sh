CC="gcc"
CFLAGS="-g -Wl,-rpath=/home/brendan/.local/lib/include -I/home/brendan/.local/lib/include -L/home/brendan/.local/lib/include -laocfunc"

input="main.c"
output="main"

$CC $CFLAGS -o $output $input

./$output
