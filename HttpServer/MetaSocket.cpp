
#include "MetaSocket.hpp"

#include <iostream>

namespace MetaSocket {
	int CSocket::init() {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			std::cout << "WSAStartup() Error!" << std::endl;

			return 0;
		}

		return 1;
	}

	int CSocket::cleanUp() {
		WSACleanup();

		return 1;
	}

	CSocket::CSocket(const std::string ip, const unsigned int port) {

		ZeroMemory(&m_sockAddr, sizeof(m_sockAddr));
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_port = htons(port);

		this->setIp(ip);
	}

	CSocket::CSocket(const SOCKET sock, const SOCKADDR_IN sockAddr) {
		this->m_socket = sock;
		this->m_sockAddr = sockAddr;
	}

	CSocket::~CSocket() { }

	void CSocket::close() { closesocket(m_socket); }

	CSocket::Type CSocket::getSockType() {
		return m_sockType;
	}

	SOCKET CSocket::getSocket() {
		return m_socket;
	}

	SOCKADDR_IN CSocket::getSockAddr() {
		return m_sockAddr;
	}

	unsigned int CSocket::setIp(const std::string ipStr) {
		if (ipStr.empty() || ipStr == "")
			m_sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		else
			m_sockAddr.sin_addr.s_addr = inet_addr(ipStr.c_str());

		return m_sockAddr.sin_addr.s_addr;
	}

	CTCPSocket::CTCPSocket(const std::string ip, const unsigned int port) : CSocket(ip, port) {
		m_sockType = CSocket::Type::TCP;

		m_socket = ::socket(PF_INET, SOCK_STREAM, 0);
		if (m_socket == INVALID_SOCKET)
			std::cout << "socket() error" << std::endl;

	}

	CTCPSocket::CTCPSocket(const SOCKET sock, const SOCKADDR_IN sockAddr) : CSocket(sock, sockAddr) {

	}

	CTCPSocket::~CTCPSocket() {

	}


	int CTCPSocket::send(const char* data, size_t size) {
		return ::send(m_socket, data, size, 0);
	}

    /**
     * @size_t size : size_t는 가장 큰 사이즈를 담을 수 있는 unsigned 정수형 데이터 타입이다. 동영상같은 큰 사이즈의 데이터를 처리할 때 일반적인 int형 타입으로 할 경우 데이터가 오버플로우 날 수 있다.
     * 데이터를 size만큼 받는 소켓 recv() 함수?
     *
     */
	std::vector<char> CTCPSocket::recv(size_t size) {
        // 사이즈 할당
		char* bufChar = (char*)malloc(size);
        // 소켓 통신하여 bufChar에 저장.
		size_t recvSize = ::recv(m_socket, bufChar, (sizeof(char) * size), 0);
        // 서버 환경마다 달라서 그런가..받은 데이터의 글자수를 구하는 라인인듯
		size_t arrSize = recvSize / sizeof(char);
        // 글자수만큼 vector 생성
		std::vector<char> arr(arrSize);
		for (size_t i = 0; i < arrSize; i++) {
			arr[i] = (bufChar[i]);
		}
        // 메모리 해제
		free(bufChar);
		return arr;
	}

	CUDPSocket::CUDPSocket(const std::string ip, const unsigned int port) : CSocket(ip, port) {
		m_sockType = CSocket::Type::UDP;

		m_socket = ::socket(AF_INET, SOCK_DGRAM, 0);
		if (m_socket == INVALID_SOCKET)
			std::cout << "socket() error" << std::endl;

	}

	CUDPSocket::CUDPSocket(const SOCKET sock, const SOCKADDR_IN sockAddr) : CSocket(sock, sockAddr) {

	}

	CUDPSocket::~CUDPSocket() {
	}

	int CUDPSocket::send(const char* data, size_t size) {
		return ::sendto(m_socket, data, size, 0,
			(SOCKADDR *)&m_sockAddr, sizeof(m_sockAddr));
	}

	std::vector<char> CUDPSocket::recv(size_t size) {
		char* bufChar = (char*)malloc(size);

		int addrlen = sizeof(m_peerAddr);
		size_t recvSize = ::recvfrom(m_socket, bufChar, (sizeof(char) * size), 0,
			(SOCKADDR *)&m_peerAddr, &addrlen);


		size_t arrSize = recvSize / sizeof(char);
		std::vector<char> arr(arrSize);
		for (size_t i = 0; i < arrSize; i++) {
			arr[i] = (bufChar[i]);
		}

		free(bufChar);
		return arr;
	}

	CServer::CServer(CSocket& sock) {
		this->m_servCSocket = &sock;
		this->m_servCSocket->setIp(""); // Set to INADDR_ANY

	}

	CSocket* CServer::getServSocket() {
		return this->m_servCSocket;
	}

	CServer::~CServer() {
	}

	CTCPServer::CTCPServer(CTCPSocket& sock) : CServer(sock) {

	}

	int CTCPServer::bind() {

		const SOCKADDR_IN servAddr = (m_servCSocket->getSockAddr());
		if (::bind(m_servCSocket->getSocket(), (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
			std::cout << "bind Error" << std::endl;
			return 0;
		}

		return 1;
	}

	int CTCPServer::listen(size_t size) {

		if (::listen(m_servCSocket->getSocket(), size) == SOCKET_ERROR) {
			std::cout << "listen Error" << std::endl;
			return 0;
		}

		return 1;
	}


	CTCPSocket* CTCPServer::accept() {
		SOCKADDR_IN clntAddr;
		int szClntAddr = sizeof(clntAddr);

		SOCKET clntSock = ::accept(m_servCSocket->getSocket(), (SOCKADDR*)&clntAddr, &szClntAddr);
		if (clntSock == INVALID_SOCKET) {
			std::cout << "accept Error" << std::endl;
			return nullptr;
		}

		CTCPSocket* clntCSock = nullptr;

		clntCSock = new CTCPSocket(clntSock, clntAddr);

		return clntCSock;
	}

	CTCPServer::~CTCPServer() {

	}

	CUDPServer::CUDPServer(CUDPSocket& sock) : CServer(sock) {

	}

	int CUDPServer::bind() {
		const SOCKADDR_IN servAddr = (m_servCSocket->getSockAddr());
		if (::bind(m_servCSocket->getSocket(), (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
			std::cout << "bind Error" << std::endl;
			return 0;
		}

		return 1;
	}

	int CUDPServer::send(const char* data, size_t size) {
		return this->m_servCSocket->send(data, size);
	}

	std::vector<char> CUDPServer::recv(SOCKADDR_IN& sockAddr, size_t size) {
		return this->m_servCSocket->recv(size);
	}

	CUDPServer::~CUDPServer() {

	}

	CClient::CClient(CSocket& sock) {
		this->m_cSocket = &sock;
	}

	int CClient::connect() {
		int result = ::connect(m_cSocket->getSocket(), (SOCKADDR*)&(m_cSocket->getSockAddr()), sizeof(m_cSocket->getSockAddr()));

		if (result == SOCKET_ERROR) {

			return 0;
		}
		else {
			std::cout << "Connect Success" << std::endl;
		}

		return 1;
	}

	CSocket* CClient::getCSocket() {
		return this->m_cSocket;
	}

	CClient::~CClient() {
	}
}
