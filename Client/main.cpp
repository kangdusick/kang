#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try
	{//�⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� �����ϴ�.
		boost::asio::io_service io_service;
		//������ �̸��� TCP ���������� �ٲٱ� ���� Resolver�� ����մϴ�.
		tcp::resolver resolver(io_service);
		//�����δ� ���� ����, ���񽺴� Daytime ���������� �����ݴϴ�.
		tcp::resolver::query query("localhost", "daytime"); //127.0.0.1 , //13����Ʈ
		//DNS�� ���� IP�ּ� �� ��Ʈ��ȣ�� ���ɴϴ�.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		//���� ��ü�� �ʱ�ȭ�Ͽ� ������ �����մϴ�.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		while (1)
		{
			//���� �� ���� ó�� ������ �����մϴ�.
			boost::array<char, 128> buf;
			boost::system::error_code error;
			//���۸� �̿��� �����κ��� �����͸� �޾ƿɴϴ�.
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			//���ۿ� ��� �����͸� ȭ�鿡 ����մϴ�.
			cout.write(buf.data(), len);
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	return 0;
}