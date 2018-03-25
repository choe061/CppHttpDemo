//
//  API.hpp
//  CppProject
//
//  Created by choi on 2018. 3. 25..
//  Copyright © 2018년 choi. All rights reserved.
//

#ifndef API_hpp
#define API_hpp

#include <stdio.h>

#endif /* API_hpp */

class API {
private:
    std::string m_method;
    std::string m_urlPath;
public:
    API(std::string method, std::string urlPath);
}
