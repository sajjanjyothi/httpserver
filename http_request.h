#pragma once
#include <string>
class HttpRequest
{
    public:
        explicit HttpRequest(){}
        std::string get_request_data()
        {
            return _request_data;
        }

        void set_request_data(std::string &data)
        {
            _request_data = data;
        }
    private:
        std::string _request_data;
};