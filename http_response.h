#pragma once
#include <strstream>
#include <iostream>
class HttpResponse
{
    public:
        explicit HttpResponse(){}
        int write_response(std::string response, std::string response_code)
        {
            std::ostrstream response_str;
            response_str << response_code << "\n" << response << "\n";
            return write(_sock_fd,response_str.str(),strlen(response_str.str()));
            return 0;
        }
        void set_client_socket(int sockfd)
        {
            _sock_fd = sockfd;
        }
    private:
        int _sock_fd;
};