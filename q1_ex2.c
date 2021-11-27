#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

int open_file(char* file_name);
char* format_file_name(char* f_name, char* suffix);
int exec_factors(char* num);
void print_end_msg(const int num_primes);

int main(int argc, char* argv[])
{
	int primes = 0;
	int pid, status;

	for (int i = 1; i < argc; i++) {
		int rc = fork();	
		if (rc == 0) { //is the cild proccess
			exec_factors(argv[i]);
		}
	}
	while ((pid = wait(&status)) != -1) {
		int ex_code = WEXITSTATUS(status);
		fprintf(stderr, "DEBUG: pid = %d, status = %d, EX(pid) = %d, EX(status) = %d\n", 
			pid, status, WEXITSTATUS(pid),ex_code);
		if (ex_code == 1)
			primes++;
	};
		//char* args[3] = { "factors","100",NULL };
		//execvp(args[0], args);
	print_end_msg(primes);

}

void print_end_msg(const int num_primes) {
	printf("There were %d prime numbers\n", num_primes);
}


int open_file(char* file_name) {
	int fd = open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	if (fd < 0) {	//failed to open the file
		fprintf(stderr,"ERROR: couldn't open file '%s' (fd: %d). Exiting program\n",
			file_name, fd);
		exit(2);
	}
	fprintf(stderr, "LOG: file '%s' opened succefully (fd: %d)\n", file_name, fd);
	return fd;
}

int exec_factors(char* num) {
	
	char* f_name = format_file_name(num, ".txt");
	printf("In 'exec_factors': num = %s, f_name = %s", num, f_name);

	//get file-descriptor of the output file
	int fd = open_file(f_name);
	free(f_name);

	//link between the output from stdout to the output file
	dup2(fd, 1);

	//we dont need the output file dexriptor anymore
	close(fd);

	//call the 'factors' program and redirect it's output to the output file,
	//via the linking we did earlier
	char* args[3] = { "./factors",num,NULL };
	int err = execvp(args[0], args);	//if factors exit with an error code, return it.

	fprintf(stderr, "ERROR: failed to run exec() with args: '%s' '%s', err = %d",args[0], args[1], err);
	close(1); //free the use for stdout.
	return err;
}


char* format_file_name(char* f_name, char* suffix) {
	int size = sizeof(f_name) + sizeof(suffix) + 1;
	char* full_name = malloc(size);
	assert(full_name);

	strcpy(full_name, f_name);	//copy the literal file name
	strcat(full_name, suffix);	//add the suffix extension to the file name

	return full_name;
}