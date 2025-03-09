#include <stdio.h>

#include "./src/whttp.h"

int main(void) {

    char* req = "GET /path/to/resource HTTP/1.1\r\n"
                "Host: www.example.com\r\n"
    "Accept: text/html\r\n"
    "Accept-Language: en-US\r\n"
    "\r\n"
    "Yellow";


    http_status_line_t* status_line = http_status_line_new(req);

    http_headers_t* headers = http_headers_new(req);

    for (int i = 0; i < headers->len; i++) {
        printf("%s: %s\n", headers->headers[i].header, headers->headers[i].value);
    }

    return 0;
}