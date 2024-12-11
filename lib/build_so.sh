CC="gcc"
CFLAGS="-g -fpic -shared"

input="aocfunc.c"
output="libaocfunc.so"
header="aocfunc.h"

$CC $CFLAGS -o $output $input

mkdir -p ~/.local/lib/include
cp $header $output ~/.local/lib/include
