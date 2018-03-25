#ifndef _PROMETA_HTTP_HTTPRESPONSE_
#define _PROMETA_HTTP_HTTPRESPONSE_

#include "HttpMessageBase.hpp"

#include <string>
#include <sstream>
#include <vector>

namespace MetaHttp {
	class HttpResponse : public HttpMessageBase {
	private:
		std::string m_protocol;

		int         m_statusCode;
		std::string m_responseMessage;
	public:
		HttpResponse() = default;

		HttpResponse(std::string protocol, int status, std::string responseMsg) {
			setStatusLine(protocol, status, responseMsg);
		}

		int setStatusLine(std::string protocol, int status, std::string responseMsg) {
			this->m_protocol        = protocol;
			this->m_statusCode      = status;
			this->m_responseMessage = responseMsg;
			
			return 1;
		}

		std::string toString() const override {
			std::stringstream ss;

			ss << m_protocol << " " << std::to_string(m_statusCode) << " " << m_responseMessage << "\r\n";

			for (auto header : m_headers) {
				ss << header.toString() << "\r\n";
			}

			std::vector<std::string> cookies = this->m_cookie.get();
			for (auto cookie : cookies) {
				ss << "Set-Cookie: " << cookie << "\r\n";
			}

			ss << "\r\n";
			ss << m_body.get();

			return ss.str();
		};

		int         getStatusCode()  const { return this->m_statusCode; }
		std::string getResponseMsg() const { return this->m_responseMessage; }

		void        setCookie(std::string key, std::string value) { 
			m_cookie.setElem(key ,value);
		};
	};
}

#endif
