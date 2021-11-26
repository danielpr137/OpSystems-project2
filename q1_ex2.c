#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int rc = fork();
	if (rc == 0) { //is the cild proccess
		char* args[3] = { "factors","100",NULL };
		execvp(args[0], args);
	}
	else {
		while (wait(NULL) != -1) {};

	}

}