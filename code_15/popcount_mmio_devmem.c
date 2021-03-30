/**
 * Created for Indiana University's
 * E315 class
 *
 * Author:  Austin Roach <ahroach@iu.edu> 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

// MMIO interface for popcount block
#define POPCOUNT_BASE 0x40000000
#define POPCOUNT_RESET_OFF 0
#define POPCOUNT_COUNT_OFF 4

// Buffer size for input data
#define BUFSIZE 32768

// Globals for shared /dev/mem file descriptor
int dev_mem_fd = -1;
int dev_mem_fd_use_cnt = 0;

static void * get_mapped_phys_mem_ptr(const off_t paddr, const size_t len)
{
	// For convenience, we will always return a pointer mapped to the
	// physical address tha the caller wants, even if that physical
	// address is not aligned to a page boundary

	long page_size;
	off_t paddr_page_base, page_offset;
	void *vaddr_base;

	if (dev_mem_fd < 0) {
		// Open /dev/mem for reading and writing
		dev_mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
		if (dev_mem_fd < 0) {
			perror("open() /dev/mem");
			return 0;
		}
	}
	// Keep track of the number of mappings sharing the file descriptor
	dev_mem_fd_use_cnt++;


	// Determine the nearest page boundary for the requested paddr
	page_size = sysconf(_SC_PAGESIZE);
	page_offset = paddr % page_size;
	paddr_page_base = paddr - page_offset;

	// Map starting at the page boundary
	vaddr_base = mmap(0, page_offset + len, PROT_READ|PROT_WRITE,
			MAP_SHARED, dev_mem_fd, paddr_page_base);

	if (vaddr_base == MAP_FAILED) {
		perror("mmap()");
		return 0;
	}

	// Return a pointer from the mapped virtual address space
	return vaddr_base + page_offset;
}

static void release_mapped_phys_mem_ptr(void * vaddr, const size_t len)
{
	long page_size;
	void * vaddr_page_base;
	off_t page_offset;
	
	// Determine the nearest page boundary to the provided vaddr.
	// This should be the base virtual address of the mapping.
	page_size = sysconf(_SC_PAGESIZE);
	page_offset = (off_t)vaddr & page_size;
	vaddr_page_base = vaddr - page_offset;

	// Unmap starting at the page boundary
	if (munmap(vaddr_page_base, page_offset + len) != 0) {
		perror("munmap()");
	}

	if (--dev_mem_fd_use_cnt == 0) {
		// Close /dev/mem file descriptor if no users remain
		if (close(dev_mem_fd) != 0) {
			perror("close()");
		}
		dev_mem_fd = -1;
	}
}

int main(int argc, char **argv)
{
	void *popcount_base;
	volatile uint32_t *reset_reg, *count_reg;
	int input_fd;
	uint8_t *data_buf, *data_ptr;
	ssize_t buf_cnt;

	// Open the input file
	if (argc != 2) {
		fprintf(stderr, "Usage: %s input_filename\n", argv[0]);
		exit(1);
	}

	input_fd = open(argv[1], O_RDONLY);
	if (input_fd < 0) {
		fprintf(stderr, "open() %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	// Allocate a read buffer
	data_buf = malloc(BUFSIZE);
	if (data_buf == 0) {
		perror("malloc()");
		exit(1);
	}
	
	// Get the virtual address pointers mapped to the MMIO interface
	popcount_base = get_mapped_phys_mem_ptr(POPCOUNT_BASE, 8);
	if (popcount_base == 0) {
		fprintf(stderr, "Error in get_mapped_phys_mem_ptr()\n");
		exit(1);
	}
	reset_reg = (uint32_t *)(popcount_base + POPCOUNT_RESET_OFF);
	count_reg = (uint32_t *)(popcount_base + POPCOUNT_COUNT_OFF);


	// Reset by writing 1 to the reset register
	*reset_reg = 1;

	// Pass the file contents to the counter
	while (1) {
		buf_cnt = read(input_fd, data_buf, BUFSIZE);
		if (buf_cnt < 0) {
			perror("read()");
			exit(1);
		}
		else if (buf_cnt == 0) {
			// EOF
			break;
		} else {
			// Feed the data into the counter in 4-byte chunks
			data_ptr = data_buf;
			while (buf_cnt >= 4) {
				*count_reg = *(uint32_t *)data_ptr;
				data_ptr += 4;
				buf_cnt -= 4;
			}
			// Feed any remaining bytes 1 byte at a time
			while (buf_cnt > 0) {
				*count_reg = *data_ptr;
				data_ptr++;
				buf_cnt--;
			}
		}
	}

	// Read the bit count result
	printf("Counted %u ones\n", *count_reg);

	// Release the mapping
	release_mapped_phys_mem_ptr(popcount_base, 8);
	
	free(data_buf);
	close(input_fd);
	return 0;
}

