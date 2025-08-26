/**
 * (c) WMGR v0.1.0 for HTMW by Woxell.co
 * 
 * [WARNING]
 * The current version is a test version, it's unstable and there are known memory leaks and unhandled errors.
 * The purpose for now is just to implement and test it's functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nx/list.h"

#if defined(__unix__)
#include <sys/stat.h>
#include <sys/types.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#define DEFAULT_INDEX_HTMW "<@include_once \"config.htmw\">\n\
<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head/>\n\
<content>\n\
    <h1>Hello and welcome to <APP_NAME></h1>\n\
    <p>It works!</p>\n\
</content>\n\
</html>"

#define DEFAULT_CONFIG_HTMW "<@ntxt>\n\
\n\
<@template ninner APP_NAME(){}>My App</@template>\n\
\n\
<@template head(){}><#head>\n\
    <meta charset=\"UTF-8\">\n\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
    <title><APP_NAME></title>\n\
    <link rel=\"stylesheet\" href=\"style.css\">$INNER\n\
</#head></@template>\n\
\n\
<@template content(){}><body><@include \"header.htmw\"><div class=\"content\">$INNER</div></body></@template>\n\
\n\
</@ntxt>"

#define DEFAULT_HEADER_HTMW "<div style=\"width: 100%; height: 64px; background-color: black; padding: 10px; position: fixed; top: 0px;\">\n\
    <span style=\"font-size: 41px; font-weight: bold; color: white;\">htmw app</span>\n\
</div>\n\
<div style=\"height: 64px;\"></div>"

#define DEFAULT_STYLE_CSS "html, body {\n\
    font-family: Arial, Helvetica, sans-serif;\n\
    margin: 0px;\n\
}\n\
\n\
div {\n\
    box-sizing: border-box;\n\
}\n\
\n\
.content {\n\
    max-width: 900px;\n\
    padding: 0px 10px;\n\
    margin: 0 auto;\n\
}"

#define DEFAULT_MAKE_TXT "cc: %s;\n\
\n\
mod:\n\
    ;\n\
\n\
target:\n\
    index#html\n\
    style.css;\n\
\n\
assets:\n\
    assets>assets;\n\
\n\
out: out;\n\
src: src;\n\
build: build;\n\
dependencies: dependencies;"

//#define COMMAND_HTMW "~/Desktop/DevSpace/htmw/build/htmw"
#define COMMAND_HTMW "htmw"

#ifdef _WIN32
#error "WMGR is not currently supported on Windows"
#endif

int create_folder(const char *path) {
    #if defined(__unix__)
    return mkdir(path, 0777);
    #elif defined(_WIN32)

    #endif
}

void fatal(const char *msg) {
    if (msg != NULL) {
        fprintf(stderr, "%s\n", msg);
    }

    exit(1);
}

typedef enum {
    ms_null,
    ms_sect,
    ms_cc,
    ms_mod,
    ms_target,
    ms_assets,
    ms_out,
    ms_src,
    ms_dependencies,
    ms_build
} make_sect;

typedef struct {
    char *data;
    size_t len;
} str_view;

char *sv_alloc_from_view(str_view s) {
    if (s.data == NULL)
        return NULL;
    char *o = (char *)malloc((s.len + 1) * sizeof(char));
    strncpy(o, s.data, s.len);
    o[s.len] = '\0';
    return o;
}

typedef struct {
    char *cc;
    list *targets;      // list >> <struct>
    list *mods;         // list >> char *
    char *out;
    char *src;
    char *build;
    char *assets[2];      // char[2] *
    char *dependencies;
} make_t;

typedef struct {
    char *obj;
    char *transf;
    char *format;
} element_t;

void sv_debug(str_view s) {
    char c = '\0';
    puts("---[string debug begin]---");
    printf("(length: %zu)\"", s.len);
    for (size_t i = 0; i < s.len; i++) {
        c = s.data[i];
        putc(c, stdout);
    }
    putc('"', stdout);
    puts("---[string debug end]---");
}

int parse_elements(list **l, const char *begin, size_t length, make_sect ms) {
    //puts("________");
    if (*l == NULL) {
        *l = list_new();
    }

    str_view sv = (str_view){ NULL, 0 };

    /*str_view obj = (str_view){ NULL, 0 };
    str_view format = (str_view){ NULL, 0 };
    str_view transf = (str_view){ NULL, 0 };*/
    /*str_view temp = (str_view){
        begin,
        length
    };

    sv_debug(temp);*/

    element_t *e = NULL;

    u_int8_t phase = 0;
    char c;
    size_t last_begin = 0;
    for (size_t i = 0; i < length; i++) {
        c = begin[i];
        //putc(c, stdout);
        switch (c) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            if (phase) {
                sv.len = i - last_begin;
                ((char **)e)[phase - 1] = sv_alloc_from_view(sv);
                phase = 0;
                list_add(*l, e);
                last_begin = i;
            }
            break;
        case '>':
            if (phase == 1) {
                sv.len = i - last_begin;
                ((char **)e)[phase - 1] = sv_alloc_from_view(sv);
                //printf("> %zu|%s\n", phase - 1, ((char **)e)[phase - 1]);
                sv.data = begin + ++i /*- last_begin*/;
                //sv.len = 0;
                phase = 2;
                last_begin = i;
            } else {
                fatal("unexpected character `>`");
            }
            break;
        case '#':
            if (phase == 1 || phase == 2) {
                sv.len = i - last_begin;
                //e->transf = sv_alloc_from_view(sv);
                ((char **)e)[phase - 1] = sv_alloc_from_view(sv);
                //printf("# %zu|%s\n", phase - 1, ((char **)e)[phase - 1]);
                sv.data = begin + ++i /*- last_begin*/;
                //sv.len = 0;
                phase = 3;
                last_begin = i;
            } else {
                fatal("unexpected character `#`");
            }
            break;
        
        default:
            if (!phase) {
                sv.data = begin + i;
                e = (element_t *)malloc(sizeof(element_t));
                e->obj = NULL;
                e->transf = NULL;
                e->format = NULL;
                last_begin = i;
                phase = 1;
            }/* else {
                //sv.len++;
            }*/
            break;
        }
    }
    if (phase) {
        sv.len = length - last_begin;
        ((char **)e)[phase - 1] = sv_alloc_from_view(sv);
        list_add(*l, e);
    }

    /*for (size_t i = 0; i < (*l)->size; i++) {
        element_t *element = list_get(*l, i);
        printf("%zu\t|%s|%s|%s|\n", i, element->obj, element->transf, element->format);
    }*/
}

make_t make(const char *path) {
    if (path == NULL) {
        path = "make.txt";
    }

    make_t m;

    char buffer[10000];
    make_sect ms = ms_null;
    char *st = NULL;
    str_view sv = (str_view){ NULL, 0 };

    list *l = NULL;

    FILE *f = fopen(path, "r");
    while (fgets(buffer, 10000, f)) {
        if (ms != ms_null && ms != ms_sect) {
            sv.data = buffer;
            sv.len = 0;
        }
        for (size_t i = 0; /*buffer[i] != '\0'*/1; i++) {
            char c = buffer[i];
            if (c == '\0') {
                if (ms == ms_sect) {
                    fatal("sect label must terminate with `:`");
                } else if (ms != ms_null) {
                    parse_elements(&l, sv.data, sv.len, ms);
                }

                break;
            } else switch (ms) {
            case ms_null:
                if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                    break;
                } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.') {
                    sv.data = buffer + i;
                    sv.len = 1;
                    ms = ms_sect;
                } else {
                    fatal("fatal: unexpected symbol");
                }
                break;
            case ms_sect:
                if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                    fatal("fatal: unexpected whitespace in sect label");
                } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.') {
                    sv.len++;
                } else if (c == ':') {
                    if (!strncmp(sv.data, "cc", 2) || !strncmp(sv.data, "tce", 3)) {
                        ms = ms_cc;
                    } else if (!strncmp(sv.data, "mod", 3)) {
                        ms = ms_mod;
                    } else if (!strncmp(sv.data, "target", 6)) {
                        ms = ms_target;
                    } else if (!strncmp(sv.data, "assets", 6)) {
                        ms = ms_assets;
                    } else if (!strncmp(sv.data, "out", 3)) {
                        ms = ms_out;
                    } else if (!strncmp(sv.data, "src", 3)) {
                        ms = ms_src;
                    } else if (!strncmp(sv.data, "build", 5)) {
                        ms = ms_build;
                    } else if (!strncmp(sv.data, "dependencies", 12)) {
                        ms = ms_dependencies;
                    } else break;

                    sv.data = buffer + i + 1;
                    sv.len = 0;
                } else {
                    fatal("fatal: unexpected symbol");
                }
                break;
            default:
                if (c == ';') {
                    /*if (ms == ms_sect) {
                        fatal("sect label cannot contain or terminate with `;`");
                    } else *///if (ms != ms_null) {
                        parse_elements(&l, sv.data, sv.len, ms);
                        //sv.data = buffer + i + 1;
                        //sv.len = 0;


                        switch (ms) {
                        case ms_cc:
                            //if (!l->size)
                                //fatal("error: no compiler specified");
                            if (l->size)
                                m.cc = ((element_t *)(l->head->data))->obj;
                            else {
                                m.cc = (char *)malloc(5 * sizeof(char));
                                //strncpy(m.cc, "htmw", 4);
                                m.cc[0] = 'h';
                                m.cc[1] = 't';
                                m.cc[2] = 'm';
                                m.cc[3] = 'w';
                                m.cc[4] = '\0';
                            }
                            free(l);
                            break;
                        case ms_build:
                            if (l->size)
                                m.build = ((element_t *)(l->head->data))->obj;
                            else {
                                m.build = (char *)malloc(6 * sizeof(char));
                                m.build[0] = 'b';
                                m.build[1] = 'u';
                                m.build[2] = 'i';
                                m.build[3] = 'l';
                                m.build[4] = 'd';
                                m.build[5] = '\0';
                            }
                            free(l);
                            break;
                        case ms_assets:
                            if (l->size) {
                                m.assets[0] = ((element_t *)(l->head->data))->obj;
                                m.assets[1] = ((element_t *)(l->head->data))->transf;
                            } else {
                                m.assets[0] = NULL;
                                m.assets[1] = NULL;
                            }
                            free(l);
                            break;
                        case ms_dependencies:
                            if (l->size) {
                                m.dependencies = ((element_t *)(l->head->data))->obj;
                            } else {
                                m.dependencies = NULL;
                            }
                            free(l);
                            break;
                        case ms_out:
                            if (l->size) {
                                m.out = ((element_t *)(l->head->data))->obj;
                            } else {
                                m.out = (char *)malloc(4 * sizeof(char));
                                m.out[0] = 'o';
                                m.out[1] = 'u';
                                m.out[2] = 't';
                                m.out[3] = '\0';
                            }
                            free(l);
                            break;
                        case ms_src:
                            if (l->size) {
                                m.src = ((element_t *)(l->head->data))->obj;
                            } else {
                                m.src = (char *)malloc(4 * sizeof(char));
                                m.src[0] = 's';
                                m.src[1] = 'r';
                                m.src[2] = 'c';
                                m.src[3] = '\0';
                            }
                            free(l);
                            break;
                        case ms_target:
                            m.targets = l;
                            break;
                        case ms_mod:
                            m.mods = l;
                            break;
                        default:
                            break;
                        }

                        
                        ms = ms_null;
                        l = NULL;
                    //}
                } else {
                    sv.len++;
                }
                break;
            }
        }
    }
    
    fclose(f);

    if (ms != ms_null) {
        fatal("definitions must terminate with `;`");
    }

    return m;
}

void make_out(make_t m) {
    char *out = (char *)malloc(1E7 * sizeof(char));
    size_t len = 0;

    #if defined(__unix__)
    if (m.assets[0] != NULL) {
        len += sprintf(out, "rm -rf %s/%s\ncp -r %s %s/%s\n\n",
            m.out, m.assets[1] != NULL ? m.assets[1] : m.assets[0],
            m.assets[0], m.out, m.assets[1] != NULL ? m.assets[1] : m.assets[0]
        );
    }
    len += sprintf(out + len, "cd %s\n\n", m.src);
    list_node *ln;
    ln = m.targets->head;
    while (ln != NULL) {
        element_t *e = (element_t *)ln->data;

        if (e->format != NULL) {
            len += sprintf(out + len, "%s %s -f %s\n",
                m.cc, e->obj, e->format
            );
        }

        ln = ln->next;
    }
    out[len++] = '\n';
    ln = m.targets->head;
    while (ln != NULL) {
        element_t *e = (element_t *)ln->data;

        if (e->format != NULL) {
            len += sprintf(out + len, "mv %s.%s ../%s/%s.%s\n",
                e->obj, e->format, m.out, e->obj, e->format
            );
        }

        ln = ln->next;
    }
    ln = m.targets->head;
    while (ln != NULL) {
        element_t *e = (element_t *)ln->data;

        if (e->format == NULL) {
            len += sprintf(out + len, "cp %s ../%s/%s\n",
                e->obj, m.out, e->obj
            );
        }

        ln = ln->next;
    }

    out[len] = '\0';

    char out_path[2048];
    strcpy(out_path, m.build);
    strcat(out_path, ".sh");
    FILE *f = fopen(out_path, "w");
    fprintf(f, "%s", out);
    fclose(f);
    #elif defined(_WIN32)

    #endif

    free(out);
}

void create_project(const char *name) {
    size_t name_len = strlen(name);
    char *buffer = (char*)malloc((name_len + 64) * sizeof(char));
    FILE *f = NULL;

    create_folder(name);
    sprintf(buffer, "%s/src", name);
    create_folder(buffer);
    sprintf(buffer, "%s/out", name);
    create_folder(buffer);
    sprintf(buffer, "%s/assets", name);
    create_folder(buffer);
    sprintf(buffer, "%s/dependencies", name);
    create_folder(buffer);

    sprintf(buffer, "%s/src/%s", name, "index.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A1)");
    fprintf(f, "%s", DEFAULT_INDEX_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/%s", name, "config.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A2)");
    fprintf(f, "%s", DEFAULT_CONFIG_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/%s", name, "header.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A3)");
    fprintf(f, "%s", DEFAULT_HEADER_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/%s", name, "style.css");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A3)");
    fprintf(f, "%s", DEFAULT_STYLE_CSS);
    fclose(f);

    #if defined(__unix__)
    sprintf(buffer, "%s/%s", name, "build.sh");
    #elif defined(_WIN32)
    sprintf(buffer, "%s/%s", name, "build.bat");
    #endif
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A3)");
    #if defined(__unix__)
    fprintf(f, "rm -rf out/assets\ncp -r assets out/assets\n\ncd src\n\n%s index -f html\n\nmv index.html ../out/index.html\ncp style.css ../out/style.css", COMMAND_HTMW);
    #elif defined(_WIN32)
    #endif
    fclose(f);

    sprintf(buffer, "%s/%s", name, "make.txt");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A4)");
    fprintf(f, DEFAULT_MAKE_TXT, COMMAND_HTMW);
    fclose(f);

    free(buffer);
}

void print_row(const char *cmd, const char *desc) {
    printf("%-30s %s\n", cmd, desc);
}

void print_actions() {
    print_row("make", "Reads `make.txt` file and generates a shell/batch script to build your project");
    print_row("new <name>", "Creates a new project in a named folder");
    print_row("ver", "Displays the installed WMGR version");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("WMGR by Woxell v0.1.0");
        puts("Usage: wmngr <action>\n\n[Actions table]");
        print_actions();
        putc('\n', stdout);
        return 0;
    }

    if (!strcmp(argv[1], "new")) {
        if (argc > 2) {
            create_project(argv[2]);
        } else {
            puts("Usage: wmngr new <name>");
        }
    } else if (!strcmp(argv[1], "make")) {
        make_t m = make("make.txt");
        make_out(m);
    } else if (!strcmp(argv[1], "ver")) {
        puts("WMGR by Woxell v0.1.0");
    }
}