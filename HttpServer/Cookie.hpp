#ifndef _PROMETA_HTTP_COOKIE_
#define _PROMETA_HTTP_COOKIE_

#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "Util.hpp"


namespace MetaHttp {
	class Cookie {
	private:
		std::map<std::string, std::string> m_cookies;

	public:
		Cookie() = default;
		Cookie(std::string str) {
			this->setStr(str);
		}

		std::string toString() const {
			std::stringstream ss;

			size_t i = 0;
			for (auto iter = m_cookies.begin(); iter != m_cookies.end(); iter++, i++) {
				ss << iter->first << "=" << iter->second;
				if (i != m_cookies.size() - 1) ss << "; ";
			}

			return ss.str();
		}

		void        setStr(std::string str) {
			std::vector<std::string> querySplits = Util::StringUtil::split(str, ';');

			for (auto iter : querySplits) {
				if (iter[0] == ' ') iter = iter.substr(1);
				auto elemSplits = Util::StringUtil::split(iter, '=');
				m_cookies.insert(std::pair<std::string, std::string>(elemSplits[0], elemSplits[1]));
			}
		}
		std::string getElem(std::string key) const {
			auto iter = m_cookies.find(key);
			if (iter != m_cookies.end())
				return iter->second;

			return "";
		}
		void        setElem(std::string key, std::string value) {
			auto iter = m_cookies.find(key);
			if (iter != m_cookies.end())
				iter->second = value;
			else
				m_cookies.insert(std::pair<std::string, std::string>(key, value));

		}

		std::vector<std::string> get() const {
			std::vector<std::string> temp(m_cookies.size());

			size_t i = 0;
			for (auto iter = m_cookies.begin(); iter != m_cookies.end(); iter++, i++) {
				temp[i] = iter->first + "=" + iter->second;
			}

			return temp;
		}
	};
}

#endif