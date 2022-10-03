
all:  test_1.c test_2.c
	gcc -O0 test_1.c -o test_1.out
	objdump --disassemble test_1.out > test_1.dis
	gcc -O0 test_2.c -o test_2.out
	objdump --disassemble test_2.out > test_2.dis


.PHONY: clean
clean:
	rm -rf *.out *.dis
