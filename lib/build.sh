CC="gcc"
CFLAGS="-g"

input="aocfunc.c"
output="aocfunc"

$CC $CFLAGS -o $output $input

./"$output"
