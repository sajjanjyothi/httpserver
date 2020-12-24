#pragma once
#include <string>

typedef std::map<std::string, std::string> REQ_DATA;

class HttpRequest
{
    public:
        explicit HttpRequest(){}
        REQ_DATA get_request_data()
        {
            return _request_data;
        }

        void set_request_data(REQ_DATA &data)
        {
            _request_data = data;
        }
    private:
        REQ_DATA _request_data;
};