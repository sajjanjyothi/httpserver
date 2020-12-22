#include "http_server.h"

HttpServer::HttpServer(int port=80)
{
    struct sockaddr_in address; 
    int opt = 1; 

    if ((_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw HttpException("Cannot create socket");
    }

    if (setsockopt(_sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                    &opt, sizeof(opt))) 
    { 
        throw HttpException("Setting socket option failed");
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 

    if (bind(_sock_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        throw HttpException("Binding failed");
    } 
}

int HttpServer::run_for_ever()
{
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    int client_socket;

    if (listen(_sock_fd, MAX_LISTEN_QUEUE) < 0)
    { 
        throw HttpException("listen failed");
    } 

    while(true)
    {
        if ((client_socket = accept(_sock_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen)) < 0) 
        { 
            throw HttpException("accept failed");
        } 
        std::async(std::launch::async,&HttpServer::process_client,*this, client_socket ); /* Process client request asynchronously*/

    }   

    return 0;
}


HttpServer::~HttpServer()
{
    /* TODO need to fix it, async call is calling the destructor - may be an acceptor class */
    // if ( _sock_fd != -1)
    // {
    //     close(_sock_fd);
    //     _sock_fd = -1;
    // }
}


