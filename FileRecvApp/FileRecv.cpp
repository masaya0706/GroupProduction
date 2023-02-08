//受信側

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment( lib, "ws2_32.lib" )

int main() {

	//ポート番号
	int port_number = 8080;

	WSADATA wsa_data;

	//WinSockの初期化処理(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsockの初期化失敗" << std::endl;
	}

	//サーバ側ソケット作成
	int src_socket;

	//sockaddr_in構造体
	//ポート番号
	//AF_INET
	struct sockaddr_in src_addr;
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.sin_port = htons(port_number);
	src_addr.sin_family = AF_INET;
	src_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	src_socket = socket(AF_INET, SOCK_STREAM, 0);

	//サーバ側のソケットをIPアドレスとポートに紐付け
	bind(src_socket, (struct sockaddr*)&src_addr, sizeof(src_addr));

	//クライアント側のソケット設定
	int dst_socket;
	struct sockaddr_in dst_addr;
	int dst_addr_size = sizeof(dst_addr);

	//接続の待受を開始
	listen(src_socket, 1);

	std::cout << "接続待ち" << std::endl;

	//送受信に使用するバッファ
	char recv_buf1[256], recv_buf2[256];
	char send_buf[256];

	//接続待ちループ
	while (1) {
		//クライアントからの接続を受信する
		dst_socket = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);
		
		std::cout << "接続完了" << std::endl;

		//接続後の処理
		while (1) {
			
			int status;

			int recv1_result = recv(dst_socket, recv_buf1, sizeof(char) * 256, 0);
			if (recv1_result == 0 || recv1_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "受信したtxtファイルの中身 : " << recv_buf1 << std::endl;

			//結果を格納したパケットの送信
			send(dst_socket, send_buf, sizeof(char) * 256, 0);
		}
	}

	//WinSockの終了処理
	WSACleanup();

	return 0;
}