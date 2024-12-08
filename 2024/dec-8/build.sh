CC="gcc"
CFLAGS="-g"

input="main.c"
output="main"

$CC $CFLAGS -o $output $input

./$output
