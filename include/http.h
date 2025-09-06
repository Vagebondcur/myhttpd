#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdio.h>


#define HTTP_MAX_REQUEST_LEN 8192*4
#define HTTP_METHOD_MAX_LEN 8
#define HTTP_PATH_MAX_LEN 2048
#define HTTP_PROTOCOL_MAX_LEN 16

#define HTTP_MAX_HEADER_KEY_LEN 256
#define HTTP_MAX_HEADER_VALUE_LEN 256


typedef enum {
    HTTP_PARSE_OK,
    HTTP_PARSE_INVALID,
} http_parse_e;


typedef struct {
    char key[HTTP_MAX_HEADER_KEY_LEN];    // Header key (e.g., "Host") || "Content-Type"
    char value[HTTP_MAX_HEADER_VALUE_LEN];  // Header value (e.g., "localhost:8080") || "text/html"
} http_header_t; // represents a single http header


typedef struct {
    int status_code;           // Numeric status code (e.g., 200, 404)
    char reason_phrase[64];    // Text explanation of the status (e.g., "OK", "Not Found")
    http_header_t *headers;    // Array of HTTP headers (key-value pairs)
    size_t header_count;       // Number of headers
    char *body;                // Response body content
    size_t body_length;        // Length of the response body
} http_response;


typedef struct {
    char method[HTTP_METHOD_MAX_LEN];    // Maximum 7 characters for HTTP methods (e.g., GET, POST) + null terminator
    char path[HTTP_PATH_MAX_LEN];   // Based on practical limits for request URIs
    char protocol[HTTP_PROTOCOL_MAX_LEN]; // Maximum length for protocol versions (e.g., HTTP/1.1)
    http_header_t *headers;
    size_t header_count; 
    char buffer[HTTP_MAX_REQUEST_LEN];
} http_request;


http_parse_e read_http_request(int socket_fd, http_request *request);
http_parse_e parse_http_headers(const char *raw_request, http_request *request);
void free_http_headers(http_request *request);
void init_http_response(http_response *response);
void add_http_header(http_response *response, const char *key, const char *value);
void free_http_response(http_response *response);

#endif // HTTP_H