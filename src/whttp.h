//
// Created by ya on 3/9/25.
//

#ifndef WHTTP_H
#define WHTTP_H
#include <stddef.h>

typedef struct {
    char* method;
    char* uri;
    char* version;
} http_status_line_t;

typedef struct {
    char* header;
    char* value;
} http_header_t;

typedef struct {
    http_header_t* headers;
    size_t len;
    size_t capacity;
} http_headers_t;

typedef struct {
    char* body;
    size_t body_len;
} http_body_t;

typedef struct {
    http_status_line_t header;
    http_header_t* headers;
    http_body_t body;
} http_request_t;

http_request_t* http_request_new(
    http_status_line_t status_line,
    http_header_t headers[],
    http_body_t body
    );

http_status_line_t* http_status_line_new(const char* req);
void http_status_line_free(http_status_line_t* status_line);

http_headers_t* http_headers_new(const char* req);
void http_headers_free(http_headers_t* header);
char* get_header(const http_headers_t* headers, const char* key);

http_header_t* http_header_new(const char* key, const char* value);
void http_header_free(http_header_t* header);

int http_headers_add(http_headers_t* headers, http_header_t* header);

http_body_t* http_body_new(const char* req);
void http_body_free(http_body_t* body);

void http_request_free(http_request_t* request);

#endif //WHTTP_H
