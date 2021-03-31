#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//스레드 생성 후, 서버 소켓, 클라이언트 소켓 생성?
//서버는 클라이언트로부터 받은 메시지를 다른 모든 클라이언트에 브로드캐스트
//클라이언트는 서버로 계속 메시지를 보냄
//서버의 메인 스레드 : 브로드캐스트, 나머지 스레드 : 클라이언트로부터 메시지를 받음
//클라이언트의 스레드는 2개 : 하나는 서버로 메시지 전달, 하나는 서버로부터 브로드캐스트 메시지 전달 받음

void error_handling(char*);
pthread_t  build_thread(pthread_t* _addr, void* _func, void* _agc, char* _argv[]);
void* build_connection(char* _argv[]);

int main(int argc, char* argv[]){
	pthread_t p_thread[2];
	int status;

	char p1[] = "thread_1";
	char p2[] = "thread_2";
	char pm[] = "thread_m";

	sleep(1);

	p_thread[0] = build_thread(pthread_t* &p_thread[0], build_connection, (void*)p1, &argv[1]);
	p_thread[1] = build_thread(pthread_t* &p_thread[1], build_connection, (void*)p2, &argv[1]);

	//_mfunc();
	printf("chat-----\n");

	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	return 0;
}

pthread_t build_thread(pthread_t* _addr, void* _func, void* _agc, char* _argv[]){
	pthread_t thread;
	thread = pthread_create(_addr, NULL, _func, _argv);

	if(thread < 0){
		perror("thread create error : ");
		exit(0);
	}


	return thread;
}

void* build_connection(char* _argv[]){

	printf("pid : %u tid: %u\n", (unsigned int)getpid(), (unsigned int)pthread_self());
	
	int server_socket;
	int client_socket;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(server_socket == -1) error_handling("socket error\n");
	
	memset(&server_addr, 0, sizeof(server_addr)); //server_addr init
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(_argv[1]));

	if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1) error_handling("bind error");

	if(listen(server_socket, 5) == -1) error_handling("listen error");
	
	client_addr_size = sizeof(client_addr);
	client_socket = accept(server_socket, (struct sockaddr*)&client_addr,&client_addr_size);
	if(client_socket == -1) error_handling("accept error");

	char msg[] = "Hello this is server!\n";
	write(client_socket, msg, sizeof(msg));

	printf("close sockets");

	close(client_socket);
	close(server_socket);
}

void error_handling(char* _msg){
	fputs(_msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
