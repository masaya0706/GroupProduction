//��M��

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment( lib, "ws2_32.lib" )

int main() {

	//�|�[�g�ԍ�
	int port_number = 8080;

	WSADATA wsa_data;

	//WinSock�̏���������(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsock�̏��������s" << std::endl;
	}

	//�T�[�o���\�P�b�g�쐬
	int src_socket;

	//sockaddr_in�\����
	//�|�[�g�ԍ�
	//AF_INET
	struct sockaddr_in src_addr;
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.sin_port = htons(port_number);
	src_addr.sin_family = AF_INET;
	src_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	src_socket = socket(AF_INET, SOCK_STREAM, 0);

	//�T�[�o���̃\�P�b�g��IP�A�h���X�ƃ|�[�g�ɕR�t��
	bind(src_socket, (struct sockaddr*)&src_addr, sizeof(src_addr));

	//�N���C�A���g���̃\�P�b�g�ݒ�
	int dst_socket;
	struct sockaddr_in dst_addr;
	int dst_addr_size = sizeof(dst_addr);

	//�ڑ��̑Ҏ���J�n
	listen(src_socket, 1);

	std::cout << "�ڑ��҂�" << std::endl;

	//����M�Ɏg�p����o�b�t�@
	char recv_buf1[256], recv_buf2[256];
	char send_buf[256];

	//�ڑ��҂����[�v
	while (1) {
		//�N���C�A���g����̐ڑ�����M����
		dst_socket = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);
		
		std::cout << "�ڑ�����" << std::endl;

		//�ڑ���̏���
		while (1) {
			
			int status;

			int recv1_result = recv(dst_socket, recv_buf1, sizeof(char) * 256, 0);
			if (recv1_result == 0 || recv1_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "��M����txt�t�@�C���̒��g : " << recv_buf1 << std::endl;

			//���ʂ��i�[�����p�P�b�g�̑��M
			send(dst_socket, send_buf, sizeof(char) * 256, 0);
		}
	}

	//WinSock�̏I������
	WSACleanup();

	return 0;
}