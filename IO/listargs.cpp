#include <stdio.h>

int main(int ac, char * av[]) {
	int i;
	for (i = 0; i < ac; i++) {
		printf("args[%d] %s\n", i, av[i]);
	}
}