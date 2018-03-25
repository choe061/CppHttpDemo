#ifndef _PROMETA_HTTP_HTTPREQUEST_
#define _PROMETA_HTTP_HTTPREQUEST_

#include "HttpMessageBase.hpp"

#include <string>
#include <sstream>
#include <vector>

#include "Util.hpp"

#include "URL.hpp"

namespace MetaHttp {
	class HttpRequest : public HttpMessageBase {
	private:
		std::string m_protocol;
		std::string m_method;
		URL         m_url;
	public:
        /**
         *
         */
		HttpRequest(std::string str) {
            // Request 메시지의 첫번째 줄은 요청 라인으로 index 0부터 한줄공백 이전까지
			std::string requestLine = str.substr(0, str.find_first_of('\n'));
            // 요청 라인 다음줄부터는 헤더 + '\n' + 바디
			std::string messageStr = str.substr(requestLine.length() + 1);
            // Request-Line은 공백(space)으로 정보 구분
            // 정보는 : Method URI HTTP버젼
			std::vector<std::string> requestLineSplit = Util::StringUtil::split(requestLine, ' ');
			// Request-Line을 저장
			m_method   = requestLineSplit[0];
			m_url      = URL("HTTP", "localhost", requestLineSplit[1]);
			m_protocol = requestLineSplit[2];
            // Headers와 Body를 설정
			this->setMessageData(messageStr);

			auto cookieHeader = this->findHeader("Cookie");
			if (cookieHeader != nullptr)
				this->m_cookie = Cookie(cookieHeader->getValue());
		}
        /**
         *
         */
		HttpRequest(std::string protocol, std::string method, URL url) {
			this->m_protocol = protocol;
			this->m_method   = method;
			this->m_url      = url;
		}

		std::string toString() const override {
			std::stringstream ss;

			ss << m_method << " " << m_url.getPath() << " " << m_protocol << "\r\n";

			for (auto header : m_headers) {
				ss << header.toString() << "\r\n";
			}

			ss << "\r\n";
			ss << m_body.get();

			return ss.str();
		}

		const std::string      getMethod() const { return this->m_method; }
		const URL              getURL()    const { return this->m_url; }

		void setMethod(std::string method) { this->m_method = method; }
		void setURL(URL url)               { this->m_url = url; }

		const Cookie* getCookie() const { return &this->m_cookie; }
	};
}

#endif
