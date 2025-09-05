#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdio.h>


#define HTTP_MAX_REQUEST_LEN 8192*4
#define HTTP_METHOD_MAX_LEN 8
#define HTTP_PATH_MAX_LEN 2048
#define HTTP_PROTOCOL_MAX_LEN 16


typedef enum {
    HTTP_PARSE_OK,
    HTTP_PARSE_INVALID,
} http_parse_e;

typedef enum {
    HTTP_OK,
    HTTP_BAD_REQUEST,
    HTTP_NOT_IMPLEMENTED,
    HTTP_VERSION_NOT_SUPPORTED
} http_status_e;


typedef struct {
    char method[8];    // Maximum 7 characters for HTTP methods (e.g., GET, POST) + null terminator
    char path[2048];   // Based on practical limits for request URIs
    char protocol[16]; // Maximum length for protocol versions (e.g., HTTP/1.1)
    char headers[1024];// Headers of the request
    char body[4096];   // Data of the post body 
} http_request;


http_parse_e read_http_request(int socket_fd, http_request *request);
http_status_e parse_http_request(const char *raw_request, http_request *request);


#endif // HTTP_H