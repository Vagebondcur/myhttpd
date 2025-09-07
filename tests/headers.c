#include "http.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char *raw_request =
        "GET /index.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: curl/7.68.0\r\n"
        "Accept: */*\r\n"
        "\r\n";

    http_request req = {0};
    parse_http_headers(raw_request, &req);

    printf("Parsed HTTP Headers:\n");
    for (size_t i = 0; i < req.header_count; i++) {
        printf("%s: %s\n", req.headers[i].key, req.headers[i].value);
    }

    free_http_headers(&req);

    http_response res = {0};

    add_http_header(&res, "Content-Type", "text/html");
    add_http_header(&res, "Connection", "close");

    printf("HTTP Response Headers:\n");
    printf("%s %s\n", res.status_code, res.reason_phrase);
    for (size_t i = 0; i < res.header_count; i++) {

        printf("%s: %s\n", res.headers[i].key, res.headers[i].value);

    }

    free_http_response(&res);


    return 0;
}
