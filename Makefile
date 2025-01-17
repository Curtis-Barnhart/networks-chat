GCC_FLAGS = -g

cchat: ui.c var_str.o var_str.h lib.o lib.h
	gcc $(GCC_FLAGS) -lncurses -o cchat ui.c lib.o var_str.o

lib.o: lib.c lib.h var_str.h
	gcc $(GCC_FLAGS) -c lib.c

test_lib: test_lib.c var_str.o lib.h lib.o
	gcc $(GCC_FLAGS) -o test_lib test_lib.c lib.o var_str.o

var_str.o: var_str.h var_str.c
	gcc $(GCC_FLAGS) -c var_str.c

test_var_str: test_var_str.c var_str.h var_str.o
	gcc $(GCC_FLAGS) -o test_var_str test_var_str.c var_str.o

clean:
	rm -f *.o 2> /dev/null
	rm -f test_var_str 2> /dev/null

