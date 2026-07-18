#include <wmgr.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("WMGR by Woxell v%s\n", WMGR_VER_STR);
        puts("Usage: wmgr <action>\n\n[Actions table]");
        wmgr_print_actions();
        putc('\n', stdout);
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
    }
}