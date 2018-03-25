//
//  HttpMessageHeader.h
//  CppProject
//
//  Created by choi on 2018. 3. 24..
//  Copyright © 2018년 choi. All rights reserved.
//

#ifndef HttpMessageHeader_hpp
#define HttpMessageHeader_hpp

#include <iostream>
#include <string>

namespace Http {
    class HttpMessageHeader {
    private:
        std::string m_header;
        std::string m_value;
        
    public:
        HttpMessageHeader(std::string str);
        HttpMessageHeader(std::string header, std::string value);
        
        void setHeader(std::string header);
        void setValue(std::string value);
        
        std::string getHeader();
        std::string getValue();
        
        std::string toString();
    };
}

#endif /* HttpMessageHeader_h */
