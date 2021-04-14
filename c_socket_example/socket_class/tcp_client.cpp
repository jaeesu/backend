#include "./tcp_client.h"
const char* MAIN_PORT = "3345";

void tcpclientsocket::start(char* _PORT){
	char name[20];
	printf("enter the name you use : ");
	scanf("%s", name);

	_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(_socket == -1) error_handling("socket error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(atoi(_PORT));

	if(connect(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1) error_handling("connect error");

	write(_socket, name, sizeof(name)-1);

	close(_socket);
}


void error_handling(string _msg){
	char msg[100];
	strcpy(msg, _msg.c_str());
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(){
	printf("starting client socket.........\n\n");
	tcpclientsocket client_socket;
	client_socket.start((char*)MAIN_PORT);

}
