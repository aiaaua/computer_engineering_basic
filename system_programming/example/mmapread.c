#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
	char *filepath = "mmap_test.txt";
	struct stat fileInfo;
	int fd;
	fd = open(filepath, O_RDONLY, (mode_t)0600);
	if (fd < 0) {
		printf("can't open file\n");
		exit(EXIT_FAILURE);
	}

	fstat(fd, &fileInfo);
	printf("File size is %ji\n", (intmax_t)fileInfo.st_size);
	char *map = mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED) {
		close(fd);
		perror("Error mapping the file");
		exit(EXIT_FAILURE);
	}
	// no need of scheduling, just access memory
	for (off_t i = 0; i < fileInfo.st_size; i++) {
		printf("Found character %c at %ji\n", map[i], (intmax_t)i);
	}
	if (munmap(map, fileInfo.st_size) == -1) {
		close(fd);
		perror("Error un-mmaping the file");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return 0;
}
