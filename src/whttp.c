//
// Created by ya on 3/9/25.
//

#include "whttp.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

http_status_line_t* http_status_line_new(const char* req) {
    const size_t pos = strcspn(req, "\r\n");

    char* our_copy = malloc(pos + 1);
    our_copy[pos] = '\0';

    memcpy(our_copy, req, pos);

    char* save_ptr = NULL;
    const char* tokenized = strtok_r(our_copy, " ", &save_ptr);

    http_status_line_t* status_line = malloc(sizeof(http_status_line_t));

    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                status_line->method = strdup(tokenized);
            break;
            case 1:
                status_line->uri = strdup(tokenized);
            break;
            case 2:
                status_line->version = strdup(tokenized);
            break;
            default:
        }

        tokenized = strtok_r(NULL, " ", &save_ptr);
    }
    free(our_copy);

    return status_line;
}

void http_status_line_free(http_status_line_t* status_line) {
    status_line->method = NULL;
    status_line->uri = NULL;
    status_line->version = NULL;
    free(status_line);
}


http_headers_t* http_headers_new(const char* req) {
    http_headers_t* headers = calloc(0, sizeof(http_headers_t));

    const size_t body_start = strstr(req, "\r\n\r\n") - req;
    char* our_copy = malloc(body_start + 1);

    memcpy(our_copy, req, body_start);

    const size_t it = strcspn(req, "\r\n");
    char *our_copy_ptr = our_copy + it;

    char* outer_ptr = NULL;
    char* inner_ptr = NULL;
    const char* nl = strtok_r(our_copy_ptr, "\r\n", &outer_ptr);

    while (nl != NULL) {
        http_header_t* header = malloc(sizeof(http_header_t));

        char* nlc = strdup(nl);

        header->header = strtok_r(nlc, ":", &inner_ptr);

        header->value = strtok_r(NULL, ":", &inner_ptr);

        http_headers_add(headers, header);

        nl = strtok_r(NULL, "\r\n", &outer_ptr);
    }
    free(our_copy);
    return headers;
}

void http_headers_free(http_headers_t* header) {
    for (int i = 0; i < header->len; i++) {
        free(&header->headers[i]);
        header->capacity = 0;
        header->len = 0;
    }
    free(header);
}

int http_headers_add(http_headers_t* headers, http_header_t* header) {
    if (headers == NULL) {
        return -1;
    }
    if (headers->capacity == 0) {
        headers->capacity = 1;
        headers->headers = malloc(sizeof(http_header_t) * headers->capacity);
    }

    if (headers->len == headers->capacity) {
        headers->capacity *= 2;
        http_header_t* temp = realloc(headers->headers, sizeof(http_header_t) * headers->capacity);
        if (temp == NULL) {
            return -1;
        }
        headers->headers = temp;
    }

    headers->headers[headers->len++] = *header;

    return 0;
}

http_body_t * http_body_new(const char *req) {
    char* our_copy = strdup(req);

    const size_t body_start = strstr(our_copy, "\r\n\r\n") - our_copy;

    char* body_ptr = our_copy + body_start + 4;

    http_body_t* body = malloc(sizeof(http_body_t));

    body->body = body_ptr;
    body->body_len = strlen(body_ptr);

    return body;
}

char* get_header(const http_headers_t* headers, const char* key) {
    for (int i = 0; i < headers->len; i++) {
        if (strcasecmp(headers->headers[i].header, key) == 0) {
            return strdup(headers->headers[i].value);
        }
    }
    return NULL;
}
