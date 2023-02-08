//送信側

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>

using std::ofstream;//アウトプットファイルストリーム
using std::ifstream;

#pragma comment( lib, "ws2_32.lib" )

int main() {

	char server_ip_addr[32];
	int port_number;

	WSADATA wsa_data;
	//WinSockの初期化処理(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsockの初期化失敗(WSAStartup)" << std::endl;
	}

	//入力
	std::cout << "接続先IPアドレスを入力：";
	std::cin >> server_ip_addr;
	std::cout << "ポート番号を入力：";
	std::cin >> port_number;

	//sockaddr_in構造体
	//ポート番号
	//AF_INET
	struct sockaddr_in dst_addr;
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.sin_port = htons(port_number);		
	dst_addr.sin_family = AF_INET;				

	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);

	int dst_socket = socket(AF_INET, SOCK_STREAM, 0);

	//接続処理
	if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
		std::cerr << "接続失敗" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl;
		exit(0);
	}

	std::cout << "接続完了" << server_ip_addr << "/接続先ポート番号" << port_number << std::endl << std::endl;;

	ifstream input_file;

	std::string fname = "test.txt";

	char send_buf1[256], send_buf2[256];
	char recv_buf[256];
	
	input_file.open(fname, std::ios::in);
	if (input_file.fail())//エラー処理は大事
	{
		std::cout << "ファイルオープンに失敗" << std::endl;
		exit(0);
	}
	std::string indata;
	std::getline(input_file, indata);

	//Packetの送信
	send(dst_socket, indata.c_str(), 256, 0);

	std::cout << "送信完了" << std::endl;

	//解放処理
	closesocket(dst_socket);

	//WinSockの終了処理
	WSACleanup();

	return 0;
}