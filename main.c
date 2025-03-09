#include <stdio.h>
#include <cjson/cJSON.h>

#include "./src/whttp.h"

int main(void) {

    char *req = "GET /path/to/resource HTTP/1.1\r\n"
            "Host: www.example.com\r\n"
            "Accept: text/html\r\n"
            "Accept-Language: en-US\r\n"
            "User-Agent: MyCustomClient/1.0\r\n"
            "Connection: keep-alive\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 27\r\n"
            "\r\n"
            "{\"key1\":\"value1\",\"key2\":42}";


    http_status_line_t* status_line = http_status_line_new(req);

    http_headers_t* headers = http_headers_new(req);

    const http_body_t* body = http_body_new(req);

    const cJSON *json = cJSON_Parse(body->body);
    const cJSON *key1 = cJSON_GetObjectItem(json, "key1");
    const cJSON *key2 = cJSON_GetObjectItem(json, "key2");

    printf("Value1: %s\n", key1->valuestring);
    printf("Value: %d\n", key2->valueint);

    for (int i = 0; i < headers->len; i++) {
        printf("%s: %s\n", headers->headers[i].header, headers->headers[i].value);
    }

    http_status_line_free(status_line);
    http_headers_free(headers);





    return 0;
}