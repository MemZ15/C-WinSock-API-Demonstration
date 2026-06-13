#pragma once
#include "NetworkIncludes.h"

/* Quick and Dirty Basic Request Structure -> Will flush out later */
struct HttpRequest
{
    std::string method;
    std::string path;
    std::string body;
};

class ResponseBuilder
{
public:
    HttpRequest ParseHTTPRequest(char* data, int size);

    std::string Build
    (
        int statusCode,
        std::string statusText,
        std::string body,
        std::string contentType = "text/plain"
    )
    {
        std::string response{};

        response += "HTTP/1.1 " + std::to_string(statusCode) + " " + statusText + "\r\n";
        response += "Content-Type: " + contentType + "\r\n";
        response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
        response += "Connection: close\r\n";
        response += "\r\n";
        response += body;

        return response;
    }

    std::string OK(std::string body)                                     { return Build(200, "OK", body);        }

    std::string NotFound(std::string body = "Not Found")                 { return Build(404, "Not Found", body); }

    std::string Error(std::string body =    "Internal Server Error")     { return Build(500, "Error", body);     }

};