//���M��

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>

using std::ofstream;//�A�E�g�v�b�g�t�@�C���X�g���[��
using std::ifstream;

#pragma comment( lib, "ws2_32.lib" )

int main() {

	char server_ip_addr[32];
	int port_number;

	WSADATA wsa_data;
	//WinSock�̏���������(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsock�̏��������s(WSAStartup)" << std::endl;
	}

	//����
	std::cout << "�ڑ���IP�A�h���X����́F";
	std::cin >> server_ip_addr;
	std::cout << "�|�[�g�ԍ�����́F";
	std::cin >> port_number;

	//sockaddr_in�\����
	//�|�[�g�ԍ�
	//AF_INET
	struct sockaddr_in dst_addr;
	memset(&dst_addr, 0, sizeof(dst_addr));
	dst_addr.sin_port = htons(port_number);		
	dst_addr.sin_family = AF_INET;				

	inet_pton(dst_addr.sin_family, server_ip_addr, &dst_addr.sin_addr.s_addr);

	int dst_socket = socket(AF_INET, SOCK_STREAM, 0);

	//�ڑ�����
	if (connect(dst_socket, (struct sockaddr*)&dst_addr, sizeof(dst_addr))) {
		std::cerr << "�ڑ����s" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl;
		exit(0);
	}

	std::cout << "�ڑ�����" << server_ip_addr << "/�ڑ���|�[�g�ԍ�" << port_number << std::endl << std::endl;;

	ifstream input_file;

	std::string fname = "test.txt";

	char send_buf1[256], send_buf2[256];
	char recv_buf[256];
	
	input_file.open(fname, std::ios::in);
	if (input_file.fail())//�G���[�����͑厖
	{
		std::cout << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
		exit(0);
	}
	std::string indata;
	std::getline(input_file, indata);

	//Packet�̑��M
	send(dst_socket, indata.c_str(), 256, 0);

	std::cout << "���M����" << std::endl;

	//�������
	closesocket(dst_socket);

	//WinSock�̏I������
	WSACleanup();

	return 0;
}