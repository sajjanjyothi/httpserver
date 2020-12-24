#pragma once
#include<sstream>
#include <iostream>
class HttpResponse
{
    public:
        explicit HttpResponse(){}
        int write_response(std::string response, std::string response_code)
        {
            std::stringstream  response_str{};
            response_str << "HTTP/1.1 "<< response_code <<"\r\n"<< response;

            write(_sock_fd,response_str.str().c_str(),response_str.str().length());
            //std::cout << "Return string " <<  response_str.str() << std::endl;
            return 0;
        }
        void set_client_socket(int sockfd)
        {
            _sock_fd = sockfd;
        }
    private:
        int _sock_fd;
};