#ifndef _PROMETA_HTTP_HTTPMESSAGEBASE_
#define _PROMETA_HTTP_HTTPMESSAGEBASE_

#include <string>
#include <vector>

#include "HttpMessageHeader.hpp"
#include "HttpMessageBody.hpp"

#include "Cookie.hpp"

#include "File.hpp"

using namespace MetaIO;

namespace MetaHttp {
	class HttpMessageBase {
	protected:
		std::vector<HttpMessageHeader> m_headers;
		HttpMessageBody                m_body;

		Cookie m_cookie;
	public:
		HttpMessageBase() = default;

        /**
         * HTTP 메시지에서 string데이터를 매개변수로 받아 Header와 Body를 설정하는 메소드
         */
		void setMessageData(std::string str) {
			std::vector<std::string> splits = Util::StringUtil::split(str, '\n');

			for (size_t i = 0; i < splits.size(); i++) {
				if (splits[i] == "\r") {
					if ((i + 1) < splits.size()) m_body.set(splits[i + 1]);
					break;
				}
				m_headers.push_back(HttpMessageHeader(splits[i]));
			}
		}

		virtual std::string toString() const = 0;

		HttpMessageHeader* findHeader(std::string header) {
			for (auto& iter : m_headers) {
				if (iter.getHeader() == header)
					return &iter;
			}

			return nullptr;
		}

		void addHeader(HttpMessageHeader header) {
			m_headers.push_back(header);
		}

		void setBody(const std::string str) {
			m_body.set(str);

			HttpMessageHeader* headContentLen = findHeader("Content-Length");
			if (headContentLen == nullptr)
				addHeader(HttpMessageHeader("Content-Length", std::to_string(str.length())));
			else
				headContentLen->setValue(std::to_string(str.length()));
		}
		void                   setBody(File file) { setBody(file.read()); }
		const HttpMessageBody* getBody() const { return &this->m_body; }
	};
}

#endif
