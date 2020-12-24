#pragma once

#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <future>
#include <regex>
#include <vector>
#include <tuple>
#include "http_exception.h"
#include "http_request.h"
#include "http_response.h"


#define MAX_LISTEN_QUEUE 50

typedef std::map<std::string,std::tuple<std::string ,void(*)(HttpRequest &request,HttpResponse &response)>> ROUTE_MAP;
typedef std::map<std::string,std::string> REQ_DATA;

class HttpServer
{

 public:
        HttpServer(int );
        inline int set_route( ROUTE_MAP &routes)
        {
            _routes = routes;
        }

        int run_for_ever();
        int process_client(int clientsocket)
        {
            char buffer[1024] = {0};

            read(clientsocket, buffer, sizeof(buffer));
            //std::cout << buffer << std::endl;
            process_callback(buffer,clientsocket );
            close(clientsocket);
            return 0;
        }

        ~HttpServer();
private:
   

    void process_callback(std::string client_data, int sockfd)
    {
        std::regex                      line_regex("[^\\n]+"); /* Separate by line */
        std::smatch                     sm;
        std::vector<std::string>        actions;

        std::regex http_method("(?:GET|PUT|POST|DELETE)");
        
        /* if any http method is there */
        if( std::regex_search(client_data, sm, http_method) )
        {
            while(std::regex_search(client_data, sm, line_regex))
            {
                actions.push_back(sm.str());
                client_data = sm.suffix();
            }
        }

        if( !actions.empty() )
        {
            std::istringstream          stream(actions.at(0));
            std::string                 method, url;
            REQ_DATA                    request_data;
            std::string                 data;

            stream>>method>>url;

            std::cout << url;
            if (int pos; (pos = url.find("?")) != std::string::npos)
            {
                data = url.substr(pos+1);
                url = url.substr(0, pos);
                
                std::regex words_regex("[^&]+");
                auto words_begin = std::sregex_iterator(data.begin(), data.end(), words_regex);
                auto words_end = std::sregex_iterator();

                for (std::sregex_iterator i = words_begin; i != words_end; ++i) 
                {
                    std::smatch match = *i;
                    std::string match_str = match.str();
                    if (match_str.substr(pos).find("=") != std::string::npos)
                    {
                        request_data[match_str.substr(0, match_str.find("="))] = match_str.substr(match_str.find("=") + 1);
                    }
                }
            }
            else
            {
                request_data["data"] = actions[actions.size() - 1];
            }
            
            /* Go through the route, there will be multiple routes */
            std::cout << "URL " << url << std::endl;
            for(const auto &routes : _routes)
            {
                if ( (routes.first == url ) && (std::get<0>(routes.second) == method ) )
                {
                    auto function = std::get<1>(routes.second);
                    HttpRequest request = HttpRequest();
                    HttpResponse response = HttpResponse();
                    response.set_client_socket(sockfd);
                    request.set_request_data(request_data);
                    function(request, response);
                }
            }
            
        }
        
    }

    int         _sock_fd;
    ROUTE_MAP   _routes;

};
