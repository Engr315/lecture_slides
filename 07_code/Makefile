
all:
	arm-none-eabi-gcc -o test.o0.o test.c -g \
						-O0 --specs=nosys.specs
	arm-none-eabi-objdump -DS test.o0.o > test.o0.dis
	arm-none-eabi-gcc -o test.o1.o test.c -g \
						-O1 --specs=nosys.specs
	arm-none-eabi-objdump -DS test.o1.o > test.o1.dis
	arm-none-eabi-gcc -o test.o3.o test.c -g \
						-O3 --specs=nosys.specs
	arm-none-eabi-objdump -DS test.o3.o > test.o3.dis

clean:
	rm -rf test.o*.dis test.o*.o
