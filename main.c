#include "wmgr_webserver.h"
#include <stdio.h>
#include <wmgr.h>

void on_start_success(uint16_t port, const char *host_path) {
    printf("\nTest environment successfully started:\nhttp://127.0.0.1:%u\n\n"
           "Press CTRL + C to stop the server\n", port);
}

void on_stop(int code) {
    if (code == WMGR_WEB_OK) {
        printf("Server stopped\n");
    } else {
        printf("An error occurred, server stopped (%d)\n", code);
    }
}

void default_help() {
    printf("WMGR by Woxell v%s\n", WMGR_VER_STR);
    puts("Usage: wmgr <action>\n\n[Actions table]");
    wmgr_print_actions();
    putc('\n', stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        default_help();
        return 0;
    }

    if (!strcmp(argv[1], "new")) {
        if (argc > 2) {
            create_xmw_project(argv[2]);
        } else {
            puts("Usage: wmgr new <name>");
        }
    } else if (!strcmp(argv[1], "make")) {
        make_t m = make("make.txt");
        make_out(m);
    } else if (!strcmp(argv[1], "ver")) {
        printf("WMGR by Woxell v%s\n", WMGR_VER_STR);
    } else if (!strcmp(argv[1], "test")) {
        unsigned char status = 0;
        make_t m = make("make.txt");
        start_webserver(4379, m.out, (struct webserver_params){
            on_start_success,
            on_stop,
            NULL,
            NULL,
            &status
        });
    } else {
        default_help();
    }
}