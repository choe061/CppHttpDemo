#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>

#include <Windows.h>

namespace Util {
	class StringUtil {
	public:
		static std::vector<std::string> split(std::string str, char seperator) {
			std::vector<std::string> output;

			std::string::size_type prev_pos = 0, pos = 0;
			while ((pos = str.find(seperator, pos)) != std::string::npos)
			{
				std::string substring(str.substr(prev_pos, pos - prev_pos));
				output.push_back(substring);
				prev_pos = ++pos;
			}
			output.push_back(str.substr(prev_pos, pos - prev_pos));

			return output;
		}
		static std::string trim(std::string& str)
		{
			str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
			return str;
		}
		template <typename T>
		static T string2type(std::string str, T defaultValue) {
			std::stringstream ss(str);
			T temp;

			if ((ss >> temp).fail() || str.empty()) {
				temp = defaultValue;
			}

			return temp;
		}


		static std::wstring s2ws(std::string str) {
			std::wstring wstr(str.begin(), str.end());
			return wstr;
		}

		static std::string ws2s(const std::wstring& wstr)
		{
			using convert_typeX = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_typeX, wchar_t> converterX;

			return converterX.to_bytes(wstr);
		}
		static std::string UTF8toANSI(std::string s)
		{
			BSTR    bstrWide;
			char*   pszAnsi;
			int     nLength;
			const char *pszCode = s.c_str();

			nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
			bstrWide = SysAllocStringLen(NULL, nLength);

			MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

			nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
			pszAnsi = new char[nLength];

			WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
			SysFreeString(bstrWide);

			std::string r(pszAnsi);
			delete[] pszAnsi;
			return r;
		}
	};
}

#endif