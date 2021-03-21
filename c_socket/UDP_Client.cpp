#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include	<winsock2.h> /*소켓 통신에 필요한 함수 들이 선언되어있는 헤더파일 */
#include	<stdio.h>
#include <conio.h>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")	/* 윈도우 소켓 함수가 정의되어있다. */

#define		PORT		  55000 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*/
#define    BUFFERSIZE    50

int main() {

	WSADATA wsdata;
	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		printf("WS2_32.DLL 을 초기화 하는데 실패했습니다.\n\n");
		return 0;
	}
	printf("WS_32.DLL 을 초기화 하는데 성공 했습니다\n\n");
	/*클라이언트가 메시지를 전송할 서버의 주소를 저장할 구조체*/
	struct sockaddr_in serverAddress;
	/*클라이언트 소켓을 생성하고 소켓 생성에 실패 했으면 -1 을 리턴*/
	int clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (clientSocket == -1) {
		printf("클라이언트 소켓을 생성하는데 실패했습니다.\n");
		return 0;
	}
	/*서버 소켓의 주소 정보를 0으로 설정합니다.*/
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;//서버의 주소 체계
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");//서버 아이피
	serverAddress.sin_port = htons(PORT);//서버의 포트

	char toServer[BUFFERSIZE]; //서버로 전송할 메시지를 저장할 배열
	char fromServer[BUFFERSIZE];//서버에서 보내온 메시지를 읽어 들여서 저장할 배열
	sprintf_s(toServer, "UDP 서버 안녕!!!\n");//toServer 에 "UDP 서버 안녕!!!\n" 메시지를 대입합니다.
   /*toServer 배열에 대입된 메시지를 서버로 전송합니다.*/
	sendto(clientSocket, toServer, BUFFERSIZE, 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	printf("서버로 전달한 메시지:%s\n", toServer);
	/*서버에서 클라이언트로 전송한 메시지를 읽어 들입니다.*/

	recvfrom(clientSocket, fromServer, BUFFERSIZE, 0, NULL, NULL);

	printf("서버로부터 전송된 메시지 : %s\n", fromServer);
	_getch();
	closesocket(clientSocket);
	return 0;
}
