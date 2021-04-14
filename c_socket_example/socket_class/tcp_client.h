#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <iostream>

using namespace std;

void error_handling(string);

class tcpclientsocket{
	private :
		unsigned long int _socket;
		struct sockaddr_in server_addr;

	public :
		void start(char*);

};


