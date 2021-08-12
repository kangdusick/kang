#define _CRT_SECURE_NO_WARNINGS
#include <ctime> //���� �ð� Ȯ�� �뵵
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

string make_daytime_string() {
	time_t now = time(0); //1970�� 1 �� 1 �� 0 �� (UTC) ���� ���� ���� �帥 �� ��
	return ctime(&now); //time_t ���� �ؼ��ؼ� ���ڿ��� ��ȯ���ش�. ���� �ð��� ���ڿ��� ������
}

int main() {
	try {
		boost::asio::io_service io_service;
		//TCP ���������� 13�� ��Ʈ�� daytime �������ݷ� ���������� ��ӵǾ��ִ�.
		//� Ŭ���̾�Ʈ�� 13�� ��Ʈ�� ���� ��û
		//TCP ���������� 13�� ��Ʈ�� ������ �޴� ���� ������ ����
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13)); 
		while (1)
		{
			//�ϳ��� Ŭ���̾�Ʈ ���� ��ü�� ������ ������ ��ٸ��ϴ�.
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			//������ �Ϸ�Ǹ� �ش� Ŭ���̾�Ʈ���� ���� �޼����� �����մϴ�.
			string message = make_daytime_string();
			//�ش� Ŭ���̾�Ʈ���� �޼����� ��� �����մϴ�.
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}