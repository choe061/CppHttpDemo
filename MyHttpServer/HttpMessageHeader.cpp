//
//  HttpMessageHeader.cpp
//  CppProject
//
//  Created by choi on 2018. 3. 24..
//  Copyright © 2018년 choi. All rights reserved.
//

#include "HttpMessageHeader.hpp"

#include <iostream>
#include <string>

using namespace std;

namespace Http {
    HttpMessageHeader::HttpMessageHeader(string str) {
        
    }
    
    HttpMessageHeader::HttpMessageHeader(string header, string value) {
        this->m_header = header;
        this->m_value = value;
    }
    
    void HttpMessageHeader::setHeader(string header) {
        this->m_header = header;
    }
    
    void HttpMessageHeader::setValue(string value) {
        this->m_value = value;
    }
    
    string HttpMessageHeader::getHeader() {
        return this->m_header;
    }
    
    string HttpMessageHeader::getValue() {
        return this->m_value;
    }
    
    string HttpMessageHeader::toString() {
        return this->m_header + ": " + this->m_value;
    }
}
