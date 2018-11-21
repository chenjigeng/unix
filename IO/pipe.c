#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 1024
#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS "testing...\n"
#define oops(m,x) {printf(m); exit(x);}


int main(int argc, char *argv[]){
	
	int argList[2];
	char send_buffer[BUFFER_SIZE] = "";
	char recv_buffer[BUFFER_SIZE] = "";
	int len;
	int read_len;
	
	int read_pipe = creat("read", 0755);
	int write_pipe = creat("write", 0755);
	
	argList[0] = read_pipe;
	argList[1] = write_pipe;
	
	
	printf("%d  %d", argList[0], argList[1]);
	if( pipe(argList) == -1)
		oops("pipe", -1);
	
	switch(fork()){
		case -1:
			oops("fork: ", -1);
			break;
			
		//子进程write
		case 0:
			len = strlen(CHILD_MESS);
			while (1) {
				if (write(argList[1], CHILD_MESS, len) != len)
					oops("write", 3);
				sleep(5);
			}
		//父进程read，读完后输出结果
		default:
			len = strlen(PAR_MESS);
			while (1) {
				if (write(argList[1], PAR_MESS, len) != len)
					oops("write", 4);
				sleep(1);
				read_len = read(argList[0], recv_buffer, BUFFER_SIZE);
				if (read_len <= 0)
					break;
				write(1, recv_buffer, read_len);
			}
	}

	return 0;
}