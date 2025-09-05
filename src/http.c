#include "http.h"
#include <string.h>
#include <unistd.h>

http_parse_e read_http_request(int socket_fd, http_request *request) {
    char buffer[HTTP_MAX_REQUEST_LEN] = {0}; // or buffer[8192]
    ssize_t bytes_read = read(socket_fd, buffer, sizeof(buffer) - 1); // never read more than buffer len

    if (bytes_read <= 0) {
        return HTTP_PARSE_INVALID; // reading failed or closed
    }

    buffer[bytes_read] = '\0';

    if (sscanf(buffer, "%7s %2047s %15s", request->method, request->path, request->protocol) != 3) {
        return HTTP_PARSE_INVALID; // -1 Failed to parse the request line
    }
    return HTTP_PARSE_OK; // 0
}