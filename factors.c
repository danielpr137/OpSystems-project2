
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 1024

int main(int argc, char* argv[]) {

	int factors[MAX_SIZE];
	int num = atoi(argv[1]), f_size = 1;
	int sq_of_num = (int)sqrt(num);

	double temp;

	factors[0] = 1;

	for (int i = 2; i <= num; i++) {
		//temp = num / i;
		if (num%i == 0){
		//if ((int)temp == temp){ //check if the quotient is a whole number
			factors[f_size] = i;
			f_size++;
		}
	}

	//int small_factors = f_size;
	//for (int i = 0; i < small_factors; i++) {
	//	factors[f_size] = num / factors[i];
	//	f_size++;
	//}

	for (int i = 0; i < f_size; i++) {
		printf("%d ", factors[i]);
	}
	printf("\n");

	if (f_size == 2)
		return 1;
	return 0;
}