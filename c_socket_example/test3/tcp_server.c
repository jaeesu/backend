#include <sys/socket.h>
#include <stdio.h>
#include <string.h> //memset
#include <arpa/inet.h> //htnol, htons, INADDR_ANY, sockaddr_in
#include <stdlib.h> //exit
#include <unistd.h> //sockaddr_in, read, write
#include <pthread.h>

void error_handling(char* message);
void* printfromc();
void* sendtoc(int);

int main(int argc, char* argv[]){
	int server_socket;
	int client_socket;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	pthread_t p_thread[2];
	char p1[] = "thread_1";
	char p2[] = "thread_2";

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(server_socket == -1) error_handling("socket error\n");
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(atoi(argv[1]));


	if(bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr))==-1) error_handling("bind error");

	if(listen(server_socket, 5)==-1) error_handling("listen error");

	client_addr_size = sizeof(client_addr);
	client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
	if(client_socket==-1) error_handling("accept error");
	
	pthread_create(&p_thread[0], NULL, printfromc(), *p1);
	pthread_create(&p_thread[1], NULL, sendtoc(client_socket), *p2);
	
	/*
	char msg[] = "Hello this is server!\n";

	while(strcmp(msg, "quit") != 0){
		printf("enter the msg : ");
		scanf("%s", msg);
		write(client_socket, msg, sizeof(msg));
	}*/

	close(client_socket);
	close(server_socket);


	return 0;
}

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void* printfromc(){
	char msg[] = "null";
	while(strcmp(msg, "quit") != 0){
		if(read(server_socket, msg, sizeof(msg)-1)==-1) error_handling("read error");
		printf("from client : %s\n", msg);
	}
	pthread_exit(-1);
}

void* sendtoc(int client_socket){
	char msg[] = "null";
	while(strcmp(msg, "quit") != 0){
		printf("  to client : ");
		write(client_socket, msg, sizeof(msg));
		printf("\n");
	}
	pthread_exit(-1);

}
