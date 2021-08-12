#define _CRT_SECURE_NO_WARNINGS
#include <ctime> //현재 시간 확인 용도
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

string make_daytime_string() {
	time_t now = time(0); //1970년 1 월 1 일 0 시 (UTC) 부터 현재 까지 흐른 초 수
	return ctime(&now); //time_t 값을 해석해서 문자열로 변환해준다. 현재 시간을 문자열로 보여줌
}

int main() {
	try {
		boost::asio::io_service io_service;
		//TCP 프로토콜의 13번 포트는 daytime 프로토콜로 세계적으로 약속되어있다.
		//어떤 클라이언트가 13번 포트로 접속 요청
		//TCP 프로토콜의 13번 포트로 연결을 받는 수동 소켓을 생성
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13)); 
		while (1)
		{
			//하나의 클라이언트 소켓 객체를 생성해 연결을 기다립니다.
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			//연결이 완료되면 해당 클라이언트에게 보낼 메세지를 생성합니다.
			string message = make_daytime_string();
			//해당 클라이언트에게 메세지를 담아 전송합니다.
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}