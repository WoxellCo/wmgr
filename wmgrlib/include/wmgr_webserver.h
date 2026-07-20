#ifndef WMGR_WEBSERVER_H
#define WMGR_WEBSERVER_H

#ifndef __cplusplus
#include "wmgr.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#if defined(__unix__)
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/stat.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <winSock2.h>
    #include <wS2tcpip.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <io.h>
#endif
#endif

#ifdef __cplusplus
extern "c" {
#endif

#define WMGR_WEB_OK                  0
#define WMGR_WEB_ERROR_SOCKET       -1
#define WMGR_WEB_ERROR_BIND         -2
#define WMGR_WEB_ERROR_LISTEN       -3
#define WMGR_WEB_ERROR_SOCKETOPT    -4
#define WMGR_WEB_ERROR_ALLOC_FAIL   -5
#define WMGR_WEB_ERROR_INIT_FAIL    -6

struct webserver_request {
    char *data;
    char *method;
    char *path;
    size_t data_length;
    size_t method_length;
    size_t path_length;
};

struct webserver_params {
    void(*on_start_success)(uint16_t port, const char *host_path);
    void(*on_stop)(int code);
    size_t(*on_connect)(char **output, struct webserver_request *);
    size_t(*on_connect_error)(char **output);
    uint8_t *status;
};

const char *guess_content_type_from_path(const char *path, size_t path_max_character_limit);
size_t serve_file(char **output, const char *host_path, const char *path, size_t path_max_character_limit);
uint8_t parse_webserver_http_request(struct webserver_request *dest, char *input);
void start_webserver(uint16_t port, const char *host_path, struct webserver_params params);

#define WMGR_WEB_NOT_FOUND_BODY_RESP "error 404: resource not found"

#ifdef __cplusplus
}
#endif
#endif