#ifndef _PROMETA_HTTP_URL_
#define _PROMETA_HTTP_URL_

#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "Util.hpp"



namespace MetaHttp {
	class URL {
	private:
		std::string m_protocol;

		std::string m_userinfo;

		std::string m_hostname;
		std::string m_port;

		std::string m_path;

		std::map<std::string, std::string> m_querys;

	public:
		URL() = default;
        /**
         * HTTP, localhost, path
         * port 번호는 필요 없나???
         * GET과 POST에 따라 URL 생성자를 다르게 둠
         * GET  => remain = urlPath + Querystring
         * POST => remain = urlPath
         */
		URL(std::string protocol, std::string hostname, std::string remain) {
			this->m_protocol = protocol;
			this->m_hostname = hostname;

            /**
             * QueryString이 있는 경우 Path와 Querystring을 분리
             * string.find()는 찾는 단어나 문자열이 없으면
             * string::npos를 리턴한다.
             */
			if (remain.find('?') != std::string::npos) {
				std::vector<std::string> splits = Util::StringUtil::split(remain, '?');

				this->m_path = splits[0];
				this->setFullQuery(splits[1]);
            } else {
				this->m_path = remain;
            }
		}

		std::string toString() const {
			std::stringstream ss;

			ss                          << m_protocol << "://";
			if (!m_userinfo.empty()) ss << m_userinfo << "@";

			ss                          << m_hostname;
			if (!m_port.empty())     ss << ":" << m_port;
			ss                          << m_path;

			if (!m_querys.empty())   ss << "?";

			size_t i = 0;
			for (auto iter = m_querys.begin(); iter != m_querys.end(); iter++, i++) {
				ss << iter->first << "=" << iter->second;
				if (i != m_querys.size() - 1) ss << "&";
			}

			return ss.str();
		}

		const std::string getProtocol() const {
            return this->m_protocol;
        }
		const std::string getHostname() const {
            return this->m_hostname;
        }
		const std::string getPort()     const {
            return this->m_port;
        }
		const std::string getPath()     const {
            return this->m_path;
        }

		void setProtocol(std::string protocol) {
            this->m_protocol = protocol;
        }
		void setHostname(std::string hostname) {
            this->m_hostname = hostname;
        }
		void setPort(std::string port) {
            this->m_port = port;
        }
		void setPath(std::string path) {
            this->m_path = path;
        }

		std::string getFullQuery() const {
			std::stringstream ss;

			size_t i = 0;
			for (auto iter = m_querys.begin(); iter != m_querys.end(); iter++, i++) {
				ss << iter->first << "=" << iter->second;
				if (i != m_querys.size() - 1) ss << "&";
			}

			return ss.str();
		}
        
        /**
         * Querystring => map<key, value>
         */
		void setFullQuery(std::string str) {
			std::vector<std::string> querySplits = Util::StringUtil::split(str, '&');

			for (auto iter : querySplits) {
				auto elemSplits = Util::StringUtil::split(iter, '=');
				m_querys.insert(std::pair<std::string, std::string>(elemSplits[0], elemSplits[1]));
			}
		}
        
        /**
         * key에 해당하는 Querystring이 있으면 리턴
         */
		std::string getQueryElem(std::string key) const { 
			auto iter = m_querys.find(key);
			if (iter != m_querys.end())
				return iter->second;

			return "";
		}
        
		void setQueryElem(std::string key, std::string value) {
			auto iter = m_querys.find(key);
			if (iter != m_querys.end())
				iter->second = value;
			else
				m_querys.insert(std::pair<std::string, std::string>(key, value));

		}
	};
}

#endif
