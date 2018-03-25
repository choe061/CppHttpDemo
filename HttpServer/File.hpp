#ifndef _PROMETA_FILE_FILE_
#define _PROMETA_FILE_FILE_

#include <string>
#include <sstream>
#include <fstream>

#include <codecvt>

#include <functional>

namespace MetaIO {
	class File {
	public:
		static std::string FilePath;
	private:
		std::string m_filePath;
		std::string m_fileType;

	private:

		std::function<std::string()> getReadFunc() {

			std::function<std::string()> func;

			if      (m_fileType == "png" || m_fileType == "jpg")
				func = std::bind(&File::readBinary, this);

			else if (m_fileType == "html" || m_fileType == "txt")
				func = std::bind(&File::readText,   this);

			else
				func = std::bind(&File::readText,   this);

			return func;
		}

		std::string readText() {
			std::ifstream file(m_filePath);

			if (!file.is_open()) {
				return nullptr;
			}

			std::stringstream ss;

			std::string str;
			while (!file.eof()) {
				std::getline(file, str);
				ss << str << "\n";
			}

			return ss.str();
		}
		std::string readBinary() {
			std::ifstream input(m_filePath, std::ios::binary);

			std::vector<char> buffer(
				(std::istreambuf_iterator<char>(input)),
				(std::istreambuf_iterator<char>()));

			return std::string(buffer.begin(), buffer.end());
		}
	public:

		File(std::string str) {
			m_filePath = str;
			m_fileType = m_filePath.substr(m_filePath.find_last_of(".") + 1);
		}

		bool isExist() {
			std::ifstream file(m_filePath);

			return file.is_open();
		}

		std::string getType() {
			return this->m_fileType;
		}

		std::string read() {
			auto readFunc = this->getReadFunc();

			return readFunc();
		}
	};

	std::string File::FilePath = "C:/Users/okms00909/Desktop/Data/HttpServer/html/";
} 

#endif