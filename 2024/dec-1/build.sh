CC="gcc"
CFLAGS=""

input="main.c"
output="main"

$CC $CFLAGS -o $output $input

./$output
