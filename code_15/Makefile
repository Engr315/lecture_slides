
popcount_mmio_devmem: popcount_mmio_devmem.c
	gcc -O0 -g -o popcount_mmio_devmem popcount_mmio_devmem.c 

.PHONY:gdb
gdb: 
	sudo gdb --args ./popcount_mmio_devmem small.bin

devmem: devmem.c	
	gcc -O0 -g -o devmem devmem.c 

memmap: memmap.c	
	gcc -O0 -g -o memmap memmap.c 

mmio: mmio.c	
	gcc -O0 -g -o mmio mmio.c 

ummio: ummio.c	
	gcc -O0 -g -o ummio ummio.c 

.PHONY:clean
clean:
	rm -rf a.out popcount_mmio_devmem devmem memmap mmio ummio


