#include <stdio.h>
#include <fcntl.h>

int main() {
	int fd;
	char line[100];

	fgets(line, 100, stdin);
	printf("%s", line);

	close(0);

	fd = open("./t.txt", O_RDONLY);

	fgets(line, 100, stdin);
	printf("%s", line);
}