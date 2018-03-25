#ifndef _PROMETA_HTTP_HTTPMESSAGE_HEADER_
#define _PROMETA_HTTP_HTTPMESSAGE_HEADER_

#include <string>
#include <iostream>

#include "Util.hpp"

using namespace Util;

namespace MetaHttp {
	class HttpMessageHeader {
	private:
		std::string m_header;
		std::string m_value;

	public:
		HttpMessageHeader(std::string header, std::string value) {
			this->m_header = header;
			this->m_value  = value;
		}

		HttpMessageHeader(std::string str) {
			std::vector<std::string> split = StringUtil::split(str, ':');

			m_header = split[0];

			split[1].erase(0, 1);
			m_value  = split[1];
		}

		std::string toString() {
			return m_header + ": " + m_value;
		}

		std::string getHeader() {
			return this->m_header;
		}

		std::string getValue() {
			return this->m_value;
		}
		void setValue(std::string value) {
			this->m_value = value;
		}
	};
}

#endif