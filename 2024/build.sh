CC="gcc"
CFLAGS="-g -I/home/brendan/.local/lib/include -laocfunc"

input="main.c"
output="main"

$CC $CFLAGS -o $output $input

./$output
