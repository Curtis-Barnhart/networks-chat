test_var_str: test_var_str.c var_str.h var_str.o
	gcc -o test_var_str test_var_str.c var_str.o

var_str.o: var_str.h var_str.c
	gcc -c var_str.c

clean:
	rm *.o

