#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <memory>

#include "MetaSocket.hpp"
#include "MetaHttp.h"

#include "File.hpp"
#include "Router.hpp"

using namespace MetaSocket;
using namespace MetaHttp;

/**
 * API Design : URL 경로 및 HTTP 메서드, 기능
 *    [URL]      [Method]      [Description]
 * 1. /dupcheck    GET      => 중복 파일이 있는지 확인
 * 2. /download    GET      => File 다운로드
 *
 * 아 PATCH는 업로드와 구분할 필요가 없나?
 * 클라이언트에서 중복을 확인한다면 분리처리하는 것도 좋을 것 같다.
 * 아니면 중복이든(PATCH) 아니든(POST) 하나의 url경로를 통해 받아서 분리처리하는 것도 좋을 것 같다.
 * 3. /upload      POST     => File 업로드
 * 4. /upload      PATCH    => 중복되는 파일이 존재하면 이름만 변경(부분 업데이트)
 */
int main() {

	CSocket::init();

	CTCPSocket sock("", 80);
	CTCPServer serv(sock);

	serv.bind(); serv.listen(5);
    
    /**
     * lambda function
     * [](매개변수) -> 리턴타입 { ... }
     */
    Router::getInstance()->addRouteFunc("POST", "/upload", [](const HttpRequest& request) -> HttpResponse* {
        /**
         * request Body에서 Filr binary 데이터를 읽어서 File로 생성
         * 성공(200) or 실패(500)에 대한 리턴
         */
        return nullptr;
    });

	Router::getInstance()->addRouteFunc("GET", "/", [](const HttpRequest& request) -> HttpResponse*{
		HttpRequest requestT = request;
		
		URL url("HTTP", "localhost", "/index.html");
		requestT.setURL(url);

		return Router::getInstance()->route(requestT);
	});

	Router::getInstance()->addRouteFunc("GET", "/get.html", [](const HttpRequest& request) -> HttpResponse* {
		HttpResponse* response = new HttpResponse("HTTP/1.1", 200, "OK");

		response->setBody(File(File::FilePath + "/get.html"));

		URL requestURL = request.getURL();
		if (!requestURL.getFullQuery().empty()) {
			std::cout << "TestText  : " << requestURL.getQueryElem("TestText") << std::endl;
			std::cout << "TestText2 : " << requestURL.getQueryElem("TestText2") << std::endl;
		}

		return response;
	});

	Router::getInstance()->addRouteFunc("POST", "/post", [](const HttpRequest& request) -> HttpResponse* {
		HttpResponse* response = new HttpResponse("HTTP/1.1", 200, "OK");	

		response->setBody(File(File::FilePath + "/post.html"));

		std::cout << "TestText  : " << request.getBody()->getElemInBody("TestText")  << std::endl;
		std::cout << "TestText2 : " << request.getBody()->getElemInBody("TestText2") << std::endl;

		return response;
	});

	Router::getInstance()->addRouteFunc("PUT",  "/put",  [](const HttpRequest& request) -> HttpResponse* {
		HttpResponse* response = new HttpResponse("HTTP/1.1", 200, "OK");

		response->setBody(request.getBody()->getElemInBody("PutTest"));

		return response;
	});

	Router::getInstance()->addRouteFunc("GET",  "/cookie", [](const HttpRequest& request) -> HttpResponse* {
		HttpResponse* response = new HttpResponse("HTTP/1.1", 200, "OK");


		std::cout << "<Request>" << std::endl << request.toString() 
				<< std::endl << "</Request>" << std::endl << std::endl;

		std::string cookie = request.getCookie()->getElem("count");
		int cnt = 0;
		if(!cookie.empty())
			cnt = Util::StringUtil::string2type<int>(cookie, 0);

		std::cout << "Count : " << cnt << std::endl;

		response->setCookie("count", std::to_string(cnt + 1));

		response->setBody(File(File::FilePath + "/cookie.html"));

		std::cout << "<Response>" << std::endl << response->toString()
			<< std::endl << "</Response>" << std::endl << std::endl;

		return response;
	});

	while (1) {
        /**
         * std::shared_ptr<T>이란?
         * template< class T > class shared_ptr; C++11
         * 기본 포인터를 대체하는 스마트 포인터
         */
		std::shared_ptr<CTCPSocket> clnt(serv.accept());
        // 1500사이즈만큼 읽어들여 recvMsg에 저장
		std::vector<char> recvMsg = clnt->recv(1500);
		std::string recvStr(recvMsg.begin(), recvMsg.end());
        // receive 문자열(데이터)가 비어있으면 continue;
		if (recvStr.length() == 0) continue;
        /**
         * 요청을 HttpRequest 객체로 생성
         * std::shared_ptr<HttpResponse> response(); 의 경우
         * 원래는 HttpResponse* response(); 이다.
         */
		HttpRequest request(recvStr);
		std::shared_ptr<HttpResponse> response(Router::getInstance()->route(request));
        
		std::string resStr = response->toString();
        /**
         * string.c_str() : string -> char* 형으로 변환
         * response를 JSON으로 보낼수는 없을까???
         */
		clnt->send(resStr.c_str(), resStr.length());
		clnt->close();


		//std::cout << "<Request>" << std::endl 
		//		  << request.toString() 
		//		  << "</Request>" << std::endl
		//		  << std::endl
		//		  << "<Response>" << std::endl 
		//		  << Util::StringUtil::UTF8toANSI(response->toString()) 
		//		  << "</Response>" << std::endl;
		std::cout << request.getMethod() << " " << request.getURL().getPath() << " - "
			<< response->getStatusCode() << " " << response->getResponseMsg() << std::endl;


	}

	CSocket::cleanUp();
	return 0;

}
