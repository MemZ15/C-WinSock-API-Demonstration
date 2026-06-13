#include "NetworkIncludes.h" 
#include "NetworkHandler.h"
#include "ResponseBuilder.h"

HttpRequest ResponseBuilder::ParseHTTPRequest(
    char* data, 
    int size
)
{
    HttpRequest req;

    std::string_view request(data, size);

    /* Find request line */
    size_t lineEnd = request.find("\r\n");
    if (lineEnd == std::string_view::npos)
        return {};

    std::string_view line = request.substr(0, lineEnd);

    /* Method */
    size_t sp1 = line.find(' ');
    if (sp1 == std::string_view::npos)
        return {};

    /* Path */
    size_t sp2 = line.find(' ', sp1 + 1);
    if (sp2 == std::string_view::npos)
        return {};

    req.method = std::string(line.substr(0, sp1));
    req.path = std::string(line.substr(sp1 + 1, sp2 - sp1 - 1));

    return req;
}