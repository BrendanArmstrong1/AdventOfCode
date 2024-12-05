CC="gcc"
CFLAGS="-g -std=c99"

input="main.c"
output="main"

$CC $CFLAGS -o $output $input

./$output
