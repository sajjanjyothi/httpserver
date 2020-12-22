
#include <string>
#include <exception>

class HttpException : public std::exception
{
    public:
        HttpException(const std::string &exception_string)
        {
            _exception_string = exception_string;
        }

        const char* what() const throw()
        {
            return _exception_string.c_str();
        }

        ~HttpException() throw(){}
    private:
        std::string _exception_string;
};