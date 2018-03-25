#ifndef _PROMETA_HTTP_ROUTER_
#define _PROMETA_HTTP_ROUTER_

#include "Singleton.hpp"

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#include "File.hpp"

#include <iostream>
#include <map>
#include <functional>

using namespace MetaHttp;
using namespace MetaIO;

class Router : public Singleton<Router> {
private:
    /**
     * HttpResponse*(const HttpRequest&)는 뭐지??? => "복사 생성자"
     * 문법) 복사 생성자란?
     * 
     * HttpResponse와 HttpRequest 모두 HttpMessageBase를 상속받고있고,
     * HttpMessageBase() = default;가 선언되어 있기 때문에 가능한 문법
     */
	std::map<std::string, std::function<HttpResponse*(const HttpRequest&)>> m_routeFuncMap;

public:
	Router()  = default;
	~Router() = default;

    /**
     * map<string, function>을 정의
     * @key      : method + " " + urlPath
     * key를 string대신 API 클래스 추가(class API : string method, string urlPath를 멤버변수로 가짐)
     * @value    : function
     */
	void addRouteFunc(std::string method, std::string urlPath, std::function<HttpResponse*(const HttpRequest&)> func) {
		m_routeFuncMap.insert(
			std::pair<std::string, std::function<HttpResponse*(const HttpRequest&)>>(
					method + " " + urlPath, func
                )
		);

	}

    /**
     * Request에 따라 route
     */
	HttpResponse* route(const HttpRequest& request) {
		HttpResponse* response;
		const std::string URLpath = request.getURL().getPath();

        /**
         * 저장해둔 m_routeFuncMap에서 Method와 Path가 일치하는 객체를 찾는다.
         * 문법) auto란?
         * C++11부터 사용.
         * 기존의 자료형 자리에 위치하여 자료형을 타입 추론으로 대체할 수 있다.
         * auto가 아니라 그냥 map으로 선언하면 안되나???
         */
		auto iter = m_routeFuncMap.find(request.getMethod() + " " + URLpath);

        /**
         * else부분은 왜 필요한지 알겠는데,
         * if부분은 왜 필요한지 모르겠다... => 아!!! iterator의 끝(end)까지 존재하지 않을때
         */
		if (iter == m_routeFuncMap.end()) {
			if (File(File::FilePath + URLpath).isExist()) {
				response = new HttpResponse("HTTP/1.1", 200, "OK");
				response->setBody(File(File::FilePath + URLpath));
            } else {
				response = new HttpResponse("HTTP/1.1", 404, "Not Found");
            }
        } else {
            /**
             * map<int, string>::iterator itMap;
             * itMap->first     : key 값을 가져옴 - int변수를 가져옴
             * itMap->second    : value 값을 가져옴 - string변수를 가져옴
             * 여기서는 second는 lambda function이고, 인자로 request를 넣어줌
             *
             * function을 호출하여 return response 값을 받는다.
             */
			response = iter->second(request);
        }

		response->addHeader(HttpMessageHeader("Connection", "close"));

		return response;
	}
};

#endif
