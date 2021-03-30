/**
 * Created for Indiana University's
 * E315 class
 *
 *
 * Author:  Andrew Lukefahr <lukefahr@iu.edu> 
 * 
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main (){
    
    int dev_mem_fd = -1;
    void * phys_addr = (void*)0x40000000;
    void * vaddr_base;

    dev_mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (dev_mem_fd < 0) { perror("open() /dev/mem"); return 1; }

    // Map 1KB of physical memory starting at 0x40000000
    // to 1KB of virtual memory starting at vaddr_base
	vaddr_base = mmap(0, 1024, PROT_READ|PROT_WRITE,
			MAP_SHARED, dev_mem_fd, (int) phys_addr);
    
    printf("virtual:%p -> physical:%p\n", vaddr_base, phys_addr); 

	if (vaddr_base == MAP_FAILED) { perror("mmap()"); return 1; }

	if (munmap(vaddr_base, 1024) != 0) { perror("munmap()"); }
    if (close(dev_mem_fd) != 0) { perror("close()"); }
    dev_mem_fd = -1;

    return 0;
}



