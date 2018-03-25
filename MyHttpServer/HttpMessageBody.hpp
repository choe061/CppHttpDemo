//
//  HttpMessageBody.hpp
//  CppProject
//
//  Created by choi on 2018. 3. 24..
//  Copyright © 2018년 choi. All rights reserved.
//

#ifndef HttpMessageBody_hpp
#define HttpMessageBody_hpp

#include <string>
#include <vector>

using namespace std;

namespace Http {
    class HttpMessageBody {
    private:
        string m_body;
    public:
        HttpMessageBody();
        HttpMessageBody(string str);
        
        void setBody(string str);
        string getBody();
        
    };
}

#endif /* HttpMessageBody_hpp */
