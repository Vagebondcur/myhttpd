#include "tcp.h"
#include "http.h"

int main() {
    tcp_server server = {0};
    server_status_e status = bind_tcp_port(&server, 8080);
    if (status != SERVER_OK) {
        debug_log("Server initialization failed");
        exit(EXIT_FAILURE);
    }

    int client_fd = accept_client(server.socket_fd);
    if (client_fd == -1) {
        debug_log("Failed to accept client connection");
        close(server.socket_fd);
        exit(EXIT_FAILURE);
    }

    debug_log("[+] Client connected");

    // REQUEST PART

    http_request req = {0};

    if (read_http_request(client_fd, &req) != HTTP_PARSE_OK) {
        debug_log("Failed to read or parse HTTP request");
        close(client_fd);
        return 0;
    }
    
    if (parse_http_headers(req.buffer, &req) != HTTP_PARSE_OK) {
        debug_log("Failed to read or parse HTTP headers");
        close(client_fd);
        return 0;
    }

    printf("Parsed HTTP headers:\n");
    printf("%s %s %s\n", req.method, req.path, req.protocol);
    for (size_t i = 0; i < req.header_count; i++) {
        printf("%s: %s\n", req.headers[i].key, req.headers[i].value);
    }

    free_http_headers(&req);



    // RESPONSE PART

    http_response res = {0};

    init_http_response(&res);
    add_http_header(&res, "Content-Type", "text/html");
    add_http_header(&res, "Connection", "close");

    printf("HTTP Response Headers:\n");
    printf("%d %s\n", res.status_code, res.reason_phrase);
    for (size_t i = 0; i < res.header_count; i++) {

        printf("%s: %s\n", res.headers[i].key, res.headers[i].value);

    }

    send_http_response(client_fd, &res);

    free_http_response(&res);

    close(client_fd);
    close(server.socket_fd);
    return 0;
}