#pragma once
#include<sstream>
#include <iostream>
class HttpResponse
{
    public:
        explicit HttpResponse(){}
        int write_response(std::string response, std::string response_code)
        {
            std::stringstream  response_str;
            response_str << response_code << "\n" << response << "\n";
            return write(_sock_fd,response_str.str().c_str(),response_str.str().length());
            return 0;
        }
        void set_client_socket(int sockfd)
        {
            _sock_fd = sockfd;
        }
    private:
        int _sock_fd;
};