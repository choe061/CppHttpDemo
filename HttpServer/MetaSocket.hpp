#ifndef _PROMETA_SOCKET_
#define _PROMETA_SOCKET_

#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>

#include <string>
#include <vector>

namespace MetaSocket {

	class CSocket {
	public:
		enum class Type { TCP = 0, UDP = 1 };

		static int init();
		static int cleanUp();

	protected:
		Type m_sockType;
		SOCKET m_socket;
		SOCKADDR_IN m_sockAddr;

	public:
		CSocket(const std::string ip, const unsigned int port);
		CSocket(const SOCKET sock, const SOCKADDR_IN sockAddr);
		virtual ~CSocket();

		void close();

		virtual int send(const char* data, size_t size) = 0;

		virtual std::vector<char> recv(size_t size) = 0;

		Type        getSockType();
		SOCKET      getSocket();
		SOCKADDR_IN getSockAddr();

		unsigned int setIp(const std::string ipStr);

	};

	class CTCPSocket : public CSocket {
	public:
		CTCPSocket(const std::string ip, const unsigned int port);
		CTCPSocket(const SOCKET sock, const SOCKADDR_IN sockAddr);

		~CTCPSocket();

		int send(const char* data, size_t size) override;

		std::vector<char> recv(size_t size) override;
	};

	class CUDPSocket : public CSocket {
	private:
		SOCKADDR_IN m_peerAddr;
	public:
		CUDPSocket(const std::string ip, const unsigned int port);
		CUDPSocket::CUDPSocket(const SOCKET sock, const SOCKADDR_IN sockAddr);

		CUDPSocket::~CUDPSocket();

		int send(const char* data, size_t size) override;

		std::vector<char> recv(size_t size) override;
	};

	class CServer {
	protected:
		CSocket* m_servCSocket;
	public:
		CServer(CSocket& sock);

		virtual int bind() = 0;

		CSocket* getServSocket();

		~CServer();
	};

	class CTCPServer : CServer {
	public:
		CTCPServer(CTCPSocket& sock);

		int bind() override;

		int listen(size_t size);

		CTCPSocket* accept();

		~CTCPServer();
	};

	class CUDPServer : CServer {
	public:
		CUDPServer(CUDPSocket& sock);

		int bind() override;

		int send(const char* data, size_t size);
		std::vector<char> recv(SOCKADDR_IN& sockAddr, size_t size);

		~CUDPServer();
	};

	class CClient {
	private:
		CSocket* m_cSocket;
	public:
		CClient(CSocket& socket);

		int connect();

		CSocket* getCSocket();

		CClient::~CClient();
	};
}

#endif