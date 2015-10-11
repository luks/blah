require 'mkmf'
$CFLAGS = "--std=c99 -O -ggdb3 -O0"

create_makefile('blah/blah')