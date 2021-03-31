#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>


pthread_t build_thread(pthread_t*, void*, void*);
void* build_connection();
void error_handling(char*);

int main(int argc, char* argv[]){
	int status;
	pthread_t p_thread[2];
	
	build_thread(&p_thread[0], build_connection, (void*)argv[1]);
	build_thread(&p_thread[1], build_connection, (void*)(argv[2]));
	//main_func();

	pthread_join(p_thread[0], (void**)&status);
	pthread_join(p_thread[1], (void**)&status);

	return 0;
}

pthread_t build_thread(pthread_t* _addr, void* _func, void* _argv){
	pthread_t tid;
	tid = pthread_create(_addr, NULL, _func, _argv);
	if(tid <0){
		perror("thread create error : ");
		exit(0);
	}
	//exiting creating thread

	return tid;
}

void* build_connection(void* _argv){
	printf("pid : %u, tid : %x \n", (unsigned int)getpid(), (unsigned int)pthread_self());
	//여기까진 잘 왔다...스레드 생성 잘 됨... 소켓만 제발ㅠㅠㅠ
	//각 스레드마다 서버 소켓, 클라이언트 소켓 맞겠지..?
	int server_socket;
	int client_socket;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(server_socket == -1) error_handling("socket error\n");
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(atoi((char*)_argv));

	if(bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr))==-1) {
		error_handling("bind error");
	}

	if(listen(server_socket, 5)==-1) error_handling("listen error");

	client_addr_size = sizeof(client_addr);
	client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
	if(client_socket==-1) error_handling("accept error");

	char msg[1024] = "this is server in test4";

	write(client_socket, msg, sizeof(msg));

	close(client_socket);
	close(server_socket);


	return 0;	
	


}

void error_handling(char* _msg){
	fputs(_msg, stderr);
	fputc('\n', stderr);
	//exit(1);
	printf("exit : %u", (unsigned int)pthread_self());
	pthread_exit(NULL);
	//exit(1);
}
