#include "http_server.h"
#include <exception>
#include <tuple>
#include "http_request.h"
#include "http_response.h"

#define SERVER_PORT 8085

int main()
{
    ROUTE_MAP routes;

    routes["/index.html"] = std::make_tuple("GET",[](HttpRequest &client_data, HttpResponse &client_response){
        REQ_DATA request_data = client_data.get_request_data();
        std::cout << "Get data " << request_data["name"] << std::endl;
        client_response.write_response("<h1>Successfully get the values</h1>", "200 OK");
    });

    routes["/api/people"] = std::make_tuple("POST",[](HttpRequest &client_data, HttpResponse &client_response){
        REQ_DATA request_data = client_data.get_request_data();
        std::cout << "Post data " << request_data["data"] << std::endl;
        client_response.write_response("Successfully updated", "200 OK");
    });

    try
    {
        HttpServer server = HttpServer(SERVER_PORT);
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