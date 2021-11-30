
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

int main(int argc, char* argv[]) {

	unsigned long factors[MAX_SIZE];
	char* ptr;
	unsigned long num = strtoul(argv[1], &ptr, 10);
	int f_size = 0;

	for (unsigned long i = 1; i <= num; i++) {
		if (num%i == 0){		 //check if the quotient is a whole number
			factors[f_size] = i;
			f_size++;
		}
	}

	for (int i = 0; i < f_size; i++) {
		printf("%lu ", factors[i]);
	}
	printf("\n");

	if (f_size == 2)
		return 1;
	return 0;
}