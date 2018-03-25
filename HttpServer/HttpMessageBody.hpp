#ifndef _PROMETA_HTTP_HTTPMESSAGE_BODY_
#define _PROMETA_HTTP_HTTPMESSAGE_BODY_

#include <string>
#include <vector>

#include "URL.hpp"

namespace MetaHttp {
	class HttpMessageBody {
	private:
		std::string m_bodyStr;
	public:

		HttpMessageBody() {

		}
		HttpMessageBody(std::string str) {
			this->m_bodyStr = str;
		}

		void set(std::string str) {
			this->m_bodyStr = str;
		}
		const std::string get() const {
			return this->m_bodyStr;
		}

        /**
         * 뭐하는 기능이지? Body에 있는 여러 Elements를 뽑아내는 기능?
         * Body의 데이터는 어떻게 구성되는지 확인하기!!!
         */
		const std::string getElemInBody(std::string str) const {
			URL url;
			url.setFullQuery(m_bodyStr);

			return url.getQueryElem(str);
		}
	};
}

#endif
