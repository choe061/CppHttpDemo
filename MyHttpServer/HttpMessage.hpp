//
//  HttpMessage.hpp
//  CppProject
//
//  Created by choi on 2018. 3. 24..
//  Copyright © 2018년 choi. All rights reserved.
//

#ifndef HttpMessage_hpp
#define HttpMessage_hpp

#include <string>
#include <vector>

#include "HttpMessageHeader.hpp"
#include "HttpMessageBody.hpp"

using namespace std;

namespace Http {
    class HttpMessage {
    protected:
        vector<HttpMessageHeader> m_headers;
        HttpMessageBody           m_body;
        
    public:
        HttpMessage() = default;
        
        void setHeaders(string str);
        void addHeader(HttpMessageHeader header);
        
        void setBody(string str);
//        void setBody(File file)
        
        const HttpMessageHeader* findHeader(string header);
        const HttpMessageBody* getBody();
    };
}


#endif /* HttpMessage_h */
