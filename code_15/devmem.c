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
#include <unistd.h>

int dev_mem_fd = -1;

int main (){

    dev_mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (dev_mem_fd < 0) {
        perror("open() /dev/mem");
        return 0;
    }
    if (close(dev_mem_fd) != 0) {
        perror("close()");
    }
    dev_mem_fd = -1;

    return 0;
}



