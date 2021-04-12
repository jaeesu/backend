#include <sys/socket.h>
#include <stdlib.h> //exit
#include <string.h> //memset
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <ctype.h>

const char* _PORT = "3345";
int str_len(char*);

void error_handling(char* message);
void* read_serv(void*);

int main(int argc, char* argv[]){
	printf("waiting-----------\n");

	int client_socket;
	unsigned long int server_socket;
	struct sockaddr_in server_addr;
	char message[1024] = {0x00, };

	time_t ct;
	struct tm tm;
	ct = time(NULL);
	tm = *localtime(&ct);

	pthread_t p_thread;
	int status;
	pthread_t tid;
	tid = pthread_create(&p_thread, NULL, read_serv, (void*)server_socket);


	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(client_socket==-1) error_handling("socket error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	////
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(atoi(_PORT));

	if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
		error_handling("connect error");

	write(client_socket, argv[1], sizeof(argv[1]-1));

	if(read(client_socket, message, sizeof(message)-1)==-1)
		error_handling("read error");
	printf("[Server] : %s\n", message);

	while(strcmp(message,"quit") != 0){
		if(read(server_socket, message, sizeof(message)-1)!=-1 && str_len(message)>24){
		printf("[ %d : %d : %d ] [client : ohter]%s  \n", tm.tm_hour, tm.tm_min, tm.tm_sec,  message);
		}
		printf("MESSAGE : ");
		scanf("%s",message);
		printf("\n");
		write(client_socket, message, sizeof(message)-1);
	}

	close(client_socket);
	pthread_join(p_thread, (void**)&status);

	return 0;
}


void error_handling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


void* read_serv(void* _server_socket){
	printf("pid : %u, tid : %x \n", (unsigned int)getpid(), (unsigned int)pthread_self());

	time_t ct;
	struct tm tm;
	ct = time(NULL);
	tm = *localtime(&ct);
	char msg[40];

	int server_socket = *(int*)_server_socket;
	while(1){

		while(read(server_socket, msg, sizeof(msg))==-1 || str_len(msg)<=24){};
		printf("[ %d : %d : %d ] [client : other]%s  \n", tm.tm_hour, tm.tm_min, tm.tm_sec, msg);
	}
}


int str_len(char* _str){
	int cnt;
	for(int i=0;i<strlen(_str);i++){
		if(!isspace(_str[i])) cnt++;
	}
	return cnt;
}
