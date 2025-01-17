GCC_FLAGS = -g

cchat: ui.c var_str.o var_str.h lib.o lib.h line_buff.o line_buff.h
	gcc $(GCC_FLAGS) -lncurses -o cchat ui.c lib.o var_str.o line_buff.o

lib.o: lib.c lib.h var_str.h
	gcc $(GCC_FLAGS) -c lib.c

test_lib: test_lib.c var_str.o lib.h lib.o
	gcc $(GCC_FLAGS) -o test_lib test_lib.c lib.o var_str.o

var_str.o: var_str.h var_str.c
	gcc $(GCC_FLAGS) -c var_str.c

test_var_str: test_var_str.c var_str.h var_str.o
	gcc $(GCC_FLAGS) -o test_var_str test_var_str.c var_str.o

line_buff.o: line_buff.c line_buff.h
	gcc $(GCC_FLAGS) -c line_buff.c

test_line_buff: line_buff.o test_line_buff.c
	gcc $(GCC_FLAGS) -o test_line_buff test_line_buff.c line_buff.o

clean:
	rm -f *.o 2> /dev/null
	rm -f cchat 2> /dev/null
	rm -f test_lib 2> /dev/null
	rm -f test_var_str 2> /dev/null
	rm -f test_line_buff 2> /dev/null

