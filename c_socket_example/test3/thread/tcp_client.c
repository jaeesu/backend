#include <sys/socket.h>
#include <stdio.h>
#include <string.h> //memset
#include <arpa/inet.h>
#include <stdlib.h> //exit
#include <unistd.h>
#include <pthread.h>

void error_handling(char* message);
void* send_msg();
void* print_msg();

int main(int argc, char* argv[]){

	int client_socket;
	int server_socket;
	struct sockaddr_in server_addr;
	char message[1024] = {0x00, };

	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(client_socket==-1) error_handling("socket error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	server_addr.sin_port=htons(atoi(argv[2]));
	
	if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
		error_handling("connect error");

	pthread_t thread1 = pthread_create(&thread1, NULL, print_msg(server_socket), NULL);
	pthread_t thread2 = pthread_create(&thread2, NULL, send_msg(server_socket), NULL);
	

	/*while(strcmp(message, "quit") != 0){
		while(read(client_socket, message, sizeof(message)-1)==-1){}
		printf("Message from server : %s\n", message);
		printf("enter the msg : ");
		scanf("%s", message);
		printf("\n");
		write(client_socket, message, sizeof(message));
	}*/
	close(server_socket);
	close(client_socket);
	
	return 0;
}


void error_handling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void* send_msg(int socket){
	char msg[50];
	while(strcmp(msg, "quit") != 0){
		printf("  to socket : ");
		scanf("%s", msg);
		write(socket, msg, sizeof(msg));
	}

}


void* print_msg(int socket){
	char msg[50];
	while(strcmp(msg, "quit") != 0){
		if(read(socket, msg, sizeof(msg)-1) == -1) error_handling("read error");
		printf("from socket : %s\n", msg);
	}
}
