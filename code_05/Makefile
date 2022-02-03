
all:
	arm-none-eabi-gcc -o test.o test.c -g \
						-O1 --specs=nosys.specs
	arm-none-eabi-objdump -DS test.o > test.dis
