#include "./tcp_server.h"
//#include "./tcp_client.h"
#include <sys/socket.h>

const char* MAIN_PORT = "3345";

void tcpserversocket::start(char* _PORT){
	_socket = socket(PF_INET, SOCK_STREAM, 0);
	int client_socket; 
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	client_addr_size = sizeof(client_addr);

	if(_socket == -1) error_handling("socket error\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(atoi(_PORT));
	
	if(bind(_socket, (struct sockaddr*) &addr, sizeof(addr)) == -1)
		error_handling("bind error");

	if(listen(_socket, 5)==-1) error_handling("listen error");
	client_socket = accept(_socket, (struct sockaddr*)&client_addr, &client_addr_size);
	if(client_socket == -1) error_handling("accept error");
	char name[20];
	read(client_socket, name, sizeof(name)-1);
	printf("client connected : %s\n\n", name);

	close(client_socket);
	close(_socket);
}


void error_handling(string _msg){
	char msg[100];
	strcpy(msg, _msg.c_str());
	fputs(msg, stderr);
	fputc('\n', stderr);
	printf("exit : %u", (unsigned int)pthread_self());
	pthread_exit(NULL);
	//exit(1);
}


int main(){
	tcpserversocket server;
	server.start((char*)MAIN_PORT);
	return 0;

}
