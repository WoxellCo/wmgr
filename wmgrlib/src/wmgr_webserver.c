#include "wmgr_webserver.h"

const char *guess_content_type_from_path(const char *path, size_t path_max_character_limit) {
    size_t extension_idx = 0;
    for (size_t i = 0; i < path_max_character_limit; i++) {
        if (path[i] == '.') {
            extension_idx = i + 1;
        }
    }
    const char *extension = path + extension_idx;
    size_t n = path_max_character_limit - extension_idx;

    if (n >= 8)
        return "text/html";

    char ext[8];
    for (size_t i = 0; i < n; i++)
        ext[i] = tolower(extension[i]);

    if (!strncmp(ext, "css", n))
        return "text/css";
    else if (!strncmp(ext, "js", n))
        return "text/javascript";
    else if (!strncmp(ext, "json", n))
        return "application/json";
    else if (!strncmp(ext, "mjs", n))
        return "text/javascript";
    else if (!strncmp(ext, "md", n))
        return "text/markdown";
    else if (!strncmp(ext, "txt", n))
        return "text/plain";
    else if (!strncmp(ext, "xml", n))
        return "application/xml";
    else if (!strncmp(ext, "ico", n))
        return "image/vnd.microsoft.icon";
    else if (!strncmp(ext, "jpeg", n) || !strncmp(ext, "jpg", n))
        return "image/jpeg";
    else if (!strncmp(ext, "mp4", n) || !strncmp(ext, "m4a", n))
        return "video/mp4";
    else if (!strncmp(ext, "mp3", n))
        return "audio/mp3";
    else if (!strncmp(ext, "mpeg", n))
        return "video/mpeg";
    else if (!strncmp(ext, "html", n) || !strncmp(ext, "htm", n))
        return "text/html";
    else if (!strncmp(ext, "csv", n))
        return "text/csv";
    else if (!strncmp(ext, "css", n))
        return "text/css";
    else if (!strncmp(ext, "png", n))
        return "image/png";
    else if (!strncmp(ext, "gif", n))
        return "image/gif";
    else if (!strncmp(ext, "webp", n))
        return "image/webp";
    else if (!strncmp(ext, "svg", n))
        return "image/svg+xml";
    else if (!strncmp(ext, "bmp", n))
        return "image/bmp";
    else if (!strncmp(ext, "tif", n) || !strncmp(ext, "tiff", n))
        return "image/tiff";
    else if (!strncmp(ext, "apng", n))
        return "image/apng";
    else if (!strncmp(ext, "avif", n))
        return "image/avif";
    else if (!strncmp(ext, "wav", n))
        return "audio/wav";
    else if (!strncmp(ext, "weba", n))
        return "audio/webm";
    else if (!strncmp(ext, "aac", n))
        return "audio/aac";
    else if (!strncmp(ext, "opus", n))
        return "audio/opus";
    else if (!strncmp(ext, "oga", n))
        return "audio/ogg";
    else if (!strncmp(ext, "ogg", n))
        return "audio/ogg";
    else if (!strncmp(ext, "ogv", n))
        return "video/ogg";
    else if (!strncmp(ext, "ogx", n))
        return "application/ogg";
    else if (!strncmp(ext, "webm", n))
        return "video/webm";
    else if (!strncmp(ext, "avi", n))
        return "video/x-msvideo";
    else if (!strncmp(ext, "3gp", n))
        return "video/3gpp";
    else if (!strncmp(ext, "3g2", n))
        return "video/3gpp2";
    else if (!strncmp(ext, "midi", n) || !strncmp(ext, "mid", n))
        return "audio/midi";
    else if (!strncmp(ext, "pdf", n))
        return "application/pdf";
    else if (!strncmp(ext, "doc", n))
        return "application/msword";
    else if (!strncmp(ext, "docx", n))
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    else if (!strncmp(ext, "xls", n))
        return "application/vnd.ms-excel";
    else if (!strncmp(ext, "xlsx", n))
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    else if (!strncmp(ext, "ppt", n))
        return "application/vnd.ms-powerpoint";
    else if (!strncmp(ext, "pptx", n))
        return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    else if (!strncmp(ext, "odt", n))
        return "application/vnd.oasis.opendocument.text";
    else if (!strncmp(ext, "ods", n))
        return "application/vnd.oasis.opendocument.spreadsheet";
    else if (!strncmp(ext, "odp", n))
        return "application/vnd.oasis.opendocument.presentation";
    else if (!strncmp(ext, "rtf", n))
        return "application/rtf";
    else if (!strncmp(ext, "otf", n))
        return "font/otf";
    else if (!strncmp(ext, "ttf", n))
        return "font/ttf";
    else if (!strncmp(ext, "woff", n))
        return "font/woff";
    else if (!strncmp(ext, "woff2", n))
        return "font/woff2";
    else if (!strncmp(ext, "eot", n))
        return "application/vnd.ms-fontobject";
    else if (!strncmp(ext, "zip", n))
        return "application/zip";
    else if (!strncmp(ext, "rar", n))
        return "application/vnd.rar";
    else if (!strncmp(ext, "7z", n))
        return "application/x-7z-compressed";
    else if (!strncmp(ext, "gz", n))
        return "application/gzip";
    else if (!strncmp(ext, "tar", n))
        return "application/x-tar";
    else if (!strncmp(ext, "bz", n))
        return "application/x-bzip";
    else if (!strncmp(ext, "bz2", n))
        return "application/x-bzip2";
    else if (!strncmp(ext, "epub", n))
        return "application/epub+zip";
    else if (!strncmp(ext, "jar", n))
        return "application/java-archive";
    else if (!strncmp(ext, "jsonld", n))
        return "application/ld+json";
    else if (!strncmp(ext, "ics", n))
        return "text/calendar";
    else if (!strncmp(ext, "sh", n))
        return "application/x-sh";
    else if (!strncmp(ext, "php", n))
        return "application/x-httpd-php";
    else if (!strncmp(ext, "bin", n))
        return "application/octet-stream";

    return "text/html";
}

uint8_t parse_webserver_http_request(struct webserver_request *dest, char *input) {
    size_t len = strlen(input);
    *dest = (struct webserver_request){
        .data = input,
        .method = NULL,
        .path = NULL,
        .data_length = len,
        .method_length = 0,
        .path_length = 0
    };
    size_t idx = 0;
    size_t last_idx = 0;

    dest->method = input;
    for (; idx < len; idx++) {
        char c = input[idx];
        if (c >= 'A' && c <= 'Z') {
            continue;
        } else if (c == ' ' && idx > 0) {
            dest->method_length = idx;
            last_idx = idx;
            break;
        } else {
            return 0;
        }
    } if (idx == len) return 0;
    
    dest->path = input + ++idx;
    for (; idx < len; idx++) {
        char c = input[idx];
        if (c == ' ') {
            if (idx - 1 == last_idx) {
                return 0;
            }
            dest->path_length = idx - last_idx - 1;
            last_idx = idx;
            break;
        }
    } if (idx == len) return 0;

    return dest->method != NULL && dest->path != NULL;
}

#if defined(__unix__) || defined(__APPLE__)
size_t serve_file(char **output, const char *host_path, const char *path, size_t path_max_character_limit) {
    size_t max_path_len = strlen(host_path) + path_max_character_limit;
    char *full_path = (char *)malloc(max_path_len + 1);
    if (full_path == NULL) {
        *output = NULL;
        return 0;
    }
    size_t tot_path_len = snprintf(full_path, max_path_len + 1, "%s%.*s", host_path, (int)path_max_character_limit, path);
    FILE *f = NULL;
    uint8_t retry = 0;
    struct stat st;

    if (stat(full_path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            full_path = (char *)realloc(full_path, tot_path_len + 12); // tot_path_len + "/index.html" + '\0'
            if (full_path == NULL) {
                *output = NULL;
                return 0;
            }
            strcpy(full_path + tot_path_len, full_path[tot_path_len - 1] == '/' ? "index.html" : "/index.html");
            if (stat(full_path, &st) != 0) {
                *output = NULL;
                return 0;
            }
            if (S_ISDIR(st.st_mode)) {
                *output = NULL;
                return 0;
            } else if (S_ISREG(st.st_mode)) {
                
            } else {
                *output = NULL;
                return 0;
            }
            f = fopen(full_path, "rb");
            //printf("fp: \"%s\"\n", full_path);
        } else if (S_ISREG(st.st_mode)) {
            f = fopen(full_path, "rb");
        }
    }

    //printf("fp: \"%s\"\n", full_path);

    if (f == NULL) {
        *output = NULL;
        return 0;
    }

    size_t sz = fseek(f, 0L, SEEK_END);
    sz = ftell(f);
    rewind(f);

    if (sz == -1) {
        *output = NULL;
        return 0;
    }

    //printf("sz: %zu\n", sz);

    //char *buff = (char *)malloc((sz + 1) * sizeof(char));
    char *content = (char *)malloc((sz + 1) * sizeof(char));
    if (/*buff == NULL || */content == NULL) {
        //free(buff);
        //free(content);
        *output = NULL;
        //puts("b");
        return 0;
    }

    size_t length = 0;
    content[0] = '\0';
    length = fread(content, 1, sz, f);

    fclose(f);
    free(full_path);
    //free(buff);
    *output = content;
    //puts(*output);
    return length;
}

void start_webserver(uint16_t port, const char *host_path, struct webserver_params params) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    socklen_t address_length = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_SOCKET);
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(server_fd);
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_SOCKETOPT);
        return;
    }

    if (bind(server_fd, (struct sockaddr *)&address, address_length) < 0) {
        close(server_fd);
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_BIND);
        return;
    }

    if (listen(server_fd, 20) < 0) {
        close(server_fd);
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_LISTEN);
        return;
    }

    *params.status = 1;

    params.on_start_success(port, host_path);

    while (*params.status) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, &address_length)) < 0) {
            if (params.on_connect_error != NULL)
                params.on_connect_error(NULL);
            continue;
        }

        char raw_req[2048] = "";

        char *response = NULL;
        size_t n_bytes = 0;

        ssize_t read_size = read(client_socket, raw_req, 2048 - 1);
        if (read_size <= 0) {
            close(client_socket);
            if (params.on_connect_error != NULL)
                n_bytes = params.on_connect_error(&response);
            continue;
        }
        raw_req[read_size] = '\0';

        struct webserver_request req;
        uint8_t req_err = 0;

        if (!parse_webserver_http_request(&req, raw_req)) {
            if (params.on_connect_error != NULL)
                n_bytes = params.on_connect_error(&response);
            req_err = 1;
        }

        //printf("%s\n", raw_req);
        //printf("|%.*s| |%.*s|\n", (int)req.method_length, req.method, (int)req.path_length, req.path);
        //printf("req_err: %u\n", req_err);
        //printf("(%zu; %zu)\n", req.method_length, req.path_length);
        
        if (!req_err) {
            if (response == NULL && params.on_connect != NULL)
                n_bytes = params.on_connect(&response, &req);

            if (response == NULL) {
                // default case (serve file)
                char *content;
                size_t len = serve_file(&content, host_path, req.path, req.path_length);
                
                if (content != NULL) {
                    response = (char *)malloc((len + 1 + 128) * sizeof(char));
                    if (response == NULL) {
                        close(client_socket);
                        close(server_fd);
                        params.on_stop(WMGR_WEB_ERROR_ALLOC_FAIL);
                        return;
                    }

                    size_t header_len = snprintf(response, len + 1 + 128,
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: %s;\r\n"
                        "Content-Length: %zu\r\n"
                        "\r\n",
                        guess_content_type_from_path(req.path, req.path_length),
                        len
                    );

                    memcpy(response + header_len, content, len);

                    n_bytes = header_len + len;
                } else {
                    response = (char *)malloc(2048);
                    if (response == NULL) {
                        close(client_socket);
                        close(server_fd);
                        params.on_stop(WMGR_WEB_ERROR_ALLOC_FAIL);
                        return;
                    }

                    snprintf(response, 2048,
                        "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/plain;\r\n"
                        "Content-Length: %zu\r\n"
                        "\r\n"
                        "%s",
                        strlen(WMGR_WEB_NOT_FOUND_BODY_RESP),
                        WMGR_WEB_NOT_FOUND_BODY_RESP
                    );
                }
            }
        } else puts("err!"); // unhandled error?

        write(client_socket, response, n_bytes);
        close(client_socket);
        free(response);
    }
    close(server_fd);
    if (params.on_stop != NULL)
        params.on_stop(WMGR_WEB_OK);
}
#elif defined(_WIN32)
//#pragma comment(lib, "Ws2_32.lib")

size_t serve_file(char **output, const char *host_path, const char *path, size_t path_max_character_limit) {
    size_t max_path_len = strlen(host_path) + path_max_character_limit;
    char *full_path = (char *)malloc(max_path_len + 1);
    if (full_path == NULL) {
        *output = NULL;
        return 0;
    }
    size_t tot_path_len = snprintf(full_path, max_path_len + 1, "%s%.*s", host_path, (int)path_max_character_limit, path);
    FILE *f = NULL;
    uint8_t retry = 0;
    struct stat st;

    if (full_path[tot_path_len - 1] == '/') {
        full_path[tot_path_len - 1] = '\0';
        tot_path_len--;
    }

    if (stat(full_path, &st) == 0) {
        if (st.st_mode & _S_IFDIR) {
            full_path = (char *)realloc(full_path, tot_path_len + 12); // tot_path_len + "/index.html" + '\0'
            if (full_path == NULL) {
                *output = NULL;
                return 0;
            }
            strcpy(full_path + tot_path_len, full_path[tot_path_len - 1] == '/' ? "index.html" : "/index.html");
            if (stat(full_path, &st) != 0) {
                *output = NULL;
                return 0;
            }
            if (st.st_mode & _S_IFDIR) {
                *output = NULL;
                return 0;
            } else if (st.st_mode & _S_IFREG) {
                
            } else {
                *output = NULL;
                return 0;
            }
            f = fopen(full_path, "rb");
        } else if (st.st_mode & _S_IFREG) {
            f = fopen(full_path, "rb");
        }
    } // add else? it would return anyway cause it's null

    //printf("fp: %s\n", full_path);

    if (f == NULL) {
        *output = NULL;
        return 0;
    }

    size_t sz = fseek(f, 0L, SEEK_END);
    sz = ftell(f);
    rewind(f);

    if (sz == -1) {
        *output = NULL;
        return 0;
    }

    //printf("sz: %zu\n", sz);

    char *content = (char *)malloc((sz + 1) * sizeof(char));
    if (content == NULL) {
        *output = NULL;
        return 0;
    }

    size_t length = 0;
    content[0] = '\0';
    while (fgets(content + (length = strlen(content)), sz, f)) {

    }

    fclose(f);
    free(full_path);
    *output = content;
    return length;
}

void start_webserver(uint16_t port, const char *host_path, struct webserver_params params) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    socklen_t address_length = sizeof(address);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_INIT_FAIL);
        return;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_SOCKET);
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    BOOL opt = TRUE;
    if (setsockopt(server_fd, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (const char *)&opt, sizeof(opt)) < 0) {
        //int err = WSAGetLastError();
        //printf("setsockopt failed, WSA error: %d\n", err);
        closesocket(server_fd);
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_SOCKETOPT);
        return;
    }

    if (bind(server_fd, (struct sockaddr *)&address, address_length) < 0) {
        closesocket(server_fd);
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_BIND);
        return;
    }

    if (listen(server_fd, 20) < 0) {
        closesocket(server_fd);
        if (params.on_stop != NULL)
            params.on_stop(WMGR_WEB_ERROR_LISTEN);
        return;
    }

    *params.status = 1;

    params.on_start_success(port, host_path);

    while (*params.status) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, &address_length)) < 0) {
            if (params.on_connect_error != NULL)
                params.on_connect_error(NULL);
            continue;
        }

        char raw_req[2048] = "";

        char *response = NULL;
        size_t n_bytes = 0;

        int read_size = recv(client_socket, raw_req, 2048 - 1, 0);
        if (read_size <= 0) {
            closesocket(client_socket);
            if (params.on_connect_error != NULL)
                n_bytes = params.on_connect_error(&response);
            continue;
        }
        raw_req[read_size] = '\0';

        struct webserver_request req;
        uint8_t req_err = 0;

        if (!parse_webserver_http_request(&req, raw_req)) {
            if (params.on_connect_error != NULL)
                n_bytes = params.on_connect_error(&response);
            req_err = 1;
        }

        //printf("%s\n", raw_req);
        //printf("|%.*s| |%.*s|\n", (int)req.method_length, req.method, (int)req.path_length, req.path);
        //printf("req_err: %u\n", req_err);
        //printf("(%zu; %zu)\n", req.method_length, req.path_length);
        
        if (!req_err) {
            if (response == NULL && params.on_connect != NULL)
                n_bytes = params.on_connect(&response, &req);

            if (response == NULL) {
                // default case (serve file)
                char *content;
                size_t len = serve_file(&content, host_path, req.path, req.path_length);
                
                if (content != NULL) {
                    response = (char *)malloc((len + 1 + 128) * sizeof(char));
                    if (response == NULL) {
                        closesocket(client_socket);
                        closesocket(server_fd);
                        params.on_stop(WMGR_WEB_ERROR_ALLOC_FAIL);
                        return;
                    }

                    size_t header_len = snprintf(response, len + 1 + 128,
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: %s;\r\n"
                        "Content-Length: %zu\r\n"
                        "\r\n",
                        guess_content_type_from_path(req.path, req.path_length),
                        len
                    );

                    memcpy(response + header_len, content, len);

                    n_bytes = header_len + len;
                } else {
                    response = (char *)malloc(2048);
                    if (response == NULL) {
                        closesocket(client_socket);
                        closesocket(server_fd);
                        params.on_stop(WMGR_WEB_ERROR_ALLOC_FAIL);
                        return;
                    }

                    snprintf(response, 2048,
                        "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/plain;\r\n"
                        "Content-Length: %zu\r\n"
                        "\r\n"
                        "%s",
                        strlen(WMGR_WEB_NOT_FOUND_BODY_RESP),
                        WMGR_WEB_NOT_FOUND_BODY_RESP
                    );
                }
            }
        } else puts("err!"); // unhandled error?

        int bytes_sent = send(client_socket, response, n_bytes, 0);
        closesocket(client_socket);
        free(response);
    }
    closesocket(server_fd);
    if (params.on_stop != NULL)
        params.on_stop(WMGR_WEB_OK);
}
//#elif defined(__APPLE__)
    
#else
    #error "unsupported platform"
#endif

