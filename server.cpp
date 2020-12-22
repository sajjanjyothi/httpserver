#include "http_server.h"
#include <exception>
#include <tuple>
#include "http_request.h"
#include "http_response.h"


void call_back(const std::string &value )
{
    std::cout << "I got this from server\n" << value << std::endl;
}
int main()
{
    ROUTE_MAP routes;

    routes["/index.html"] = std::make_tuple("GET",[](HttpRequest &client_data, HttpResponse &client_response){
        std::string request_data = client_data.get_request_data();
        std::cout << "Get data " << request_data << std::endl;
        client_response.write_response("Successfully get the values", "200 OK");
    });

    routes["/api/people"] = std::make_tuple("POST",[](HttpRequest &client_data, HttpResponse &client_response){
        std::cout << "Post data " << client_data.get_request_data() << std::endl;
        client_response.write_response("Successfully updated", "200 OK");
    });

    try
    {
        HttpServer server = HttpServer(8085);
        server.set_route(routes);
        server.run_for_ever();
    }
    catch(std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        exit(-1);
    }

    return 0;
}