all: main.o IntVector.o
	gcc -Werror -pedantic-errors -Wall -Wextra -Wpedantic -Wcast-align \
	-Wcast-qual -Wconversion  -Wduplicated-branches \
	-Wduplicated-cond  -Wfloat-equal -Wlogical-op \
	-Wold-style-cast  \
	-Wredundant-decls -Wsign-conversion main.o IntVector.o -o ./a.out

main.o: main.c
	gcc -c -Werror -pedantic-errors -Wall -Wextra -Wpedantic -Wcast-align \
	-Wcast-qual -Wconversion  -Wduplicated-branches \
	-Wduplicated-cond  -Wfloat-equal -Wlogical-op \
	-Wold-style-cast  \
	-Wredundant-decls -Wsign-conversion main.c

IntVector.o:IntVector.c
	gcc -c -Werror -pedantic-errors -Wall -Wextra -Wpedantic -Wcast-align \
	-Wcast-qual -Wconversion  -Wduplicated-branches \
	-Wduplicated-cond  -Wfloat-equal -Wlogical-op \
	-Wold-style-cast  \
	-Wredundant-decls -Wsign-conversion IntVector.c

clean:
	rm -rf *.o ./a.out
