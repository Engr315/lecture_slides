/**
 * Created for Indiana University's
 * E315 class
 *
 *
 * Author:  Andrew Lukefahr <lukefahr@iu.edu> 
 * 
 */
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main (){
    
    int dev_mem_fd = -1;
    void * vaddr_base;

    //Mapping user-space I/O
    dev_mem_fd = open("/dev/uio0", O_RDWR|O_SYNC);
    if (dev_mem_fd < 0) { perror("open() /dev/uio0"); return 1; }

    // Map 1KB of physical memory starting at 0x40000000
    // to 1KB of virtual memory starting at vaddr_base
	vaddr_base = mmap(0, 1024, PROT_READ|PROT_WRITE,
			MAP_SHARED, dev_mem_fd, 0x0); // not 0x40000000

	if (vaddr_base == MAP_FAILED) { perror("mmap()"); return 1; }
    
    printf("virtual:%p -> physical:%p\n", vaddr_base, (uint32_t*) 0x40000000); 

    uint32_t * reset = (uint32_t*) vaddr_base;
    uint32_t * count = (uint32_t*) (vaddr_base + 0x4);

    *reset = 1;
    *count = 0xf;
    printf("Count: %d\n", *count);

	if (munmap(vaddr_base, 1024) != 0) { perror("munmap()"); }
    if (close(dev_mem_fd) != 0) { perror("close()"); }
    dev_mem_fd = -1;

    return 0;
}



