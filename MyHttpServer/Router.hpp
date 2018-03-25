//
//  Router.hpp
//  CppProject
//
//  Created by choi on 2018. 3. 25..
//  Copyright © 2018년 choi. All rights reserved.
//

#ifndef Router_hpp
#define Router_hpp

#include <stdio.h>

#include "API.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class Router {
private:
    /**
     * GET, POST, PATCH 별로 routeMap을 분리할까?
     */
    
    /**
     * map<key, value>
     * key   => API(string method, string urlPath)
     * value => function<HttpResponse>
     */
    std::map<API, std::function<HttpResponse* (const HttpRequest&)>> m_routeFuncMap;
    
public:
    //void addRouteFunc(API api, std::function<HttpResponse*(const HttpRequest&)> func);
    
    Router() = default;
    ~Router() = default;
    
    void addRouteFunction(std::string method, std::string urlPath, std::function<HttpResponse*(const HttpRequest&)> func);
    
    void get(std::string urlPath, std::function<HttpResponse*(const HttpRequest&)> func) {
        addRouteFunction("GET", urlPath, func);
    }
    void post(std::string urlPath, std::function<HttpResponse*(const HttpRequest&)> func) {
        addRouteFunction("POST", urlPath, func);
    }
    
    HttpResponse* route(const HttpRequest* request);
};


#endif /* Router_hpp */
