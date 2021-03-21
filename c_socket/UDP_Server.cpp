#include	<winsock2.h> /*소켓 통신에 필요한 함수 들이 선언되어있는 헤더파일 */
#include	<stdio.h>
#include <conio.h>

#define		PORT		  55000 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*/
#define    BUFFERSIZE    50

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")	/* 윈도우 소켓 함수가 정의되어있다. */

int main() {

	WSADATA wsdata;
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		printf("WS2_32.DLL 을 초기화 하는데 실패했습니다.\n\n");
		return 0;
	}
	printf("WS_32.DLL 을 초기화 하는데 성공 했습니다\n\n");

	struct sockaddr_in serverAddress; //서버의 주소 정보를 저장할 구조체
	//UDP 프로토콜의 서버소켓 생성
	int serverSocket = socket(PF_INET, SOCK_DGRAM, 0);
	//서버의 주소를 저장할 serverAddress 를 0으로 초기화 시킴
	memset(&serverAddress, 0, sizeof(serverAddress));
	//serverAddress 의 주소 체계 설정
	serverAddress.sin_family = AF_INET;
	//serverAddress 에 서버 IP 대입
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	//serverAddress 에 포트 대입
	serverAddress.sin_port = htons(PORT);
	//serverSocket 에 서버의 주소 정보 설정
	bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
	printf("클라이언트에서 데이터를 보내오기를 기다리고 있습니다.\n");
	//클라이언트가 전송한 메시지를 저장할 배열
	char fromClient[BUFFERSIZE];
	//클라이언트로 전송할 메시지를 저장할 배열
	char toClient[BUFFERSIZE];
	//클라이언트의 주소 정보를 저장할 구조체
	struct sockaddr_in clientAddress;
	//클라이언트의 주소 정보를 저장할 구조체의 크기를 저장할 변수
	int clientAddress_size;

	while (1) {
		//클라이언트의 주소 정보를 저장할 clientAddress 구조체의 크기를 대입
		clientAddress_size = sizeof(clientAddress);
		//클라이언트가 전송한 메시지를 읽어 들여서 fromClient 배열에 대입하고 
		//메시지를 보낸 클라이언트의 주소 정보를 clientAddress 에 대입함


	   /* recvfrom 함수는 클라이언트로부터 데이터를 수신하는 함수입니다.
		  데이터를 읽어들이는 데 성공하면 읽어들인 데이터의 바이트 수를 리턴하고, 실패하면 -1을 리턴한다.
	  형식:
	   recvfrom(int sock, const void *msg, int len, unsigned flags, const struct sockaddr * addr, int addrlen)
		   int    데이터를 전송받을 소켓의 파일 핸들
		   void   읽어들인 데이터를 저장할 배열 설정
		   int    읽어들인 데이터를 저장할 배열의 크기
		   unsigned UDP 소켓의 옵셥을 설정하는데 보통 0으로 설정
		   sockaddr 데이터를 보낸 곳 (addr 구조체)의 포인터 설정
		   int    addr 포인터가 가리키는 구조체의 크기 설정
		 */

		recvfrom(serverSocket, fromClient, BUFFERSIZE, 0, (struct sockaddr*)&clientAddress, &clientAddress_size);
		printf("앗!! 클라이언트가 메시지를 전송했습니다.\n");
		printf("클라이언트로 부터 전달된 메시지:%s\n", fromClient);
		//toClient 배열에 "UDP 클라이언트 반가워!!!\n" 메시지를 대입
		sprintf_s(toClient, "UDP 클라이언트 반가워!!\n");
		//클라이언트로 toClient 배열의 메시지를 전송함

			   /* sendto 함수는 클라이언트로 데이터를 전송하는 함수입니다.
				데이터를 전송하는 데 성공하면 전송한 데이터의 바이트 수를 리턴하고, 실패하면 -1을 리턴한다.
	  형식:
	  int sendto( int sock, const void *msg, int len, unsigned flags, const struct sockaddr * addr, int addrlen)
		   int   데이터를 전송할 소켓의 파일 핸들
		   void   전송할 데이터를 저장할 배열 설정
		   int    전송할 데이터를 저장할 배열의 크기
		   unsigned UDP 소켓의 옵션을 설정하는데 보통 0으로 설정
		   sockaddr 전송을 하고자 하는 목적지(addr 구조체)의 포인터  설정
		   int    addr 포인터가 가리키는 구조체의 크기 설정
		 */
		sendto(serverSocket, toClient, BUFFERSIZE, 0, (struct sockaddr*)&clientAddress, sizeof(clientAddress));
		printf("클라이언트로 전달한 메시지:%s\n", toClient);
	}
	_getch();
	closesocket(serverSocket);
	return 0;
}



