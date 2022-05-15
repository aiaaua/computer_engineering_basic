#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	struct stat fileInfo;
	char *filepath = "mmap_test.txt";
	char *update = "hello muse!";
	int fd = open(filepath, O_RDWR, (mode_t)0600);
	if (fd == -1) {
		printf("Error opening file for writing");
		exit(EXIT_FAILURE);
	}

	fstat(fd, &fileInfo);
	printf("%ld\n", fileInfo.st_size);
	char *map = mmap(0, fileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED) {
		close(fd);
		perror("Error mapping the file");
		exit(EXIT_FAILURE);
	}
	
	printf("%ld", strlen(update));
	for (size_t i = 0; i < strlen(update); i++) {
		printf("Write character %c at %zu\n", map[i], i);
		map[i] = update[i];
	}
	if (msync(map, fileInfo.st_size, MS_SYNC) == -1) {
		perror("Could not sync the file to disk");
	}
	if (munmap(map, fileInfo.st_size) == -1) {
		close(fd);
		perror("Error un-mmaping the file");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return 0;
}
