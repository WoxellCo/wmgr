/**
 * (c) WMGR v0.3.1 for HTMW by Woxell.co
 * 
 * [WARNING]
 * The current version is a test version, it's unstable and there are known memory leaks and unhandled errors.
 * The purpose for now is just to implement and test it's functionality.
 */

#include "wmgr.h"
#include "wmgr_boilerplate.h"
#include "wmgr_vect.h"
#include <stddef.h>

wmgr_def_vect_push_back(1, char *);
wmgr_def_vect_push_back(2, element_t);

int create_folder(const char *path) {
    #if defined(__unix__)
    return mkdir(path, 0777);
    #elif defined(_WIN32)
    return CreateDirectory(path, NULL);
    #endif
}

void fatal(const char *msg) {
    if (msg != NULL) {
        fprintf(stderr, "%s\n", msg);
    }

    exit(1);
}

char *sv_alloc_from_view(str_view s) {
    if (s.data == NULL)
        return NULL;
    char *o = (char *)malloc((s.len + 1) * sizeof(char));
    strncpy(o, s.data, s.len);
    o[s.len] = '\0';
    return o;
}

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

int parse_wmgr_elements(wmgr_element_vect *section_elements, char *begin, size_t length, make_sect ms) {
    //puts("________");
    if (wmgr_vect_is_null(*section_elements)) {
        *section_elements = wmgr_vect_new(2, element_t, 16);
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

    //element_t *e = NULL;
    element_t e;

    uint8_t phase = 0;
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
                ((char **)&e)[phase - 1] = sv_alloc_from_view(sv);
                phase = 0;
                wmgr_vect_push_back_2(section_elements, e);
                last_begin = i;
            }
            break;
        case '>':
            if (phase == 1) {
                sv.len = i - last_begin;
                ((char **)&e)[phase - 1] = sv_alloc_from_view(sv);
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
                ((char **)&e)[phase - 1] = sv_alloc_from_view(sv);
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
                //e = (element_t *)malloc(sizeof(element_t));
                e.obj = NULL;
                e.transf = NULL;
                e.format = NULL;
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
        ((char **)&e)[phase - 1] = sv_alloc_from_view(sv);
        wmgr_vect_push_back_2(section_elements, e);
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
    make_sect section_type = ms_null;
    char *st = NULL;
    str_view sv = (str_view){ NULL, 0 };

    wmgr_element_vect section_elements = wmgr_vect_null(2);

    FILE *f = fopen(path, "r");
    while (fgets(buffer, 10000, f)) {
        if (section_type != ms_null && section_type != ms_sect) {
            sv.data = buffer;
            sv.len = 0;
        }
        for (size_t i = 0; /*buffer[i] != '\0'*/1; i++) {
            char c = buffer[i];
            if (c == '\0') {
                if (section_type == ms_sect) {
                    fatal("sect label must terminate with `:`");
                } else if (section_type != ms_null) {
                    parse_wmgr_elements(&section_elements, sv.data, sv.len, section_type);
                }

                break;
            } else switch (section_type) {
            case ms_null:
                if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                    break;
                } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.') {
                    sv.data = buffer + i;
                    sv.len = 1;
                    section_type = ms_sect;
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
                        section_type = ms_cc;
                    } else if (!strncmp(sv.data, "mod", 3)) {
                        section_type = ms_mod;
                    } else if (!strncmp(sv.data, "target", 6)) {
                        section_type = ms_target;
                    } else if (!strncmp(sv.data, "assets", 6)) {
                        section_type = ms_assets;
                    } else if (!strncmp(sv.data, "out", 3)) {
                        section_type = ms_out;
                    } else if (!strncmp(sv.data, "src", 3)) {
                        section_type = ms_src;
                    } else if (!strncmp(sv.data, "build", 5)) {
                        section_type = ms_build;
                    } else if (!strncmp(sv.data, "dependencies", 12)) {
                        section_type = ms_dependencies;
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
                        parse_wmgr_elements(&section_elements, sv.data, sv.len, section_type);
                        //sv.data = buffer + i + 1;
                        //sv.len = 0;


                        switch (section_type) {
                        case ms_cc:
                            //if (!l->size)
                                //fatal("error: no compiler specified");
                            if (section_elements.size)
                                m.cc = section_elements.data[0].obj;
                            else {
                                m.cc = (char *)malloc(5 * sizeof(char));
                                //strncpy(m.cc, "htmw", 4);
                                m.cc[0] = 'h';
                                m.cc[1] = 't';
                                m.cc[2] = 'm';
                                m.cc[3] = 'w';
                                m.cc[4] = '\0';
                            }
                            wmgr_vect_delete(section_elements);
                            break;
                        case ms_build:
                            if (section_elements.size)
                                m.build = section_elements.data[0].obj;
                            else {
                                m.build = (char *)malloc(6 * sizeof(char));
                                m.build[0] = 'b';
                                m.build[1] = 'u';
                                m.build[2] = 'i';
                                m.build[3] = 'l';
                                m.build[4] = 'd';
                                m.build[5] = '\0';
                            }
                            wmgr_vect_delete(section_elements);
                            break;
                        case ms_assets:
                            if (section_elements.size) {
                                m.assets[0] = section_elements.data[0].obj;
                                m.assets[1] = section_elements.data[0].transf;
                            } else {
                                m.assets[0] = NULL;
                                m.assets[1] = NULL;
                            }
                            wmgr_vect_delete(section_elements);;
                            break;
                        case ms_dependencies:
                            if (section_elements.size) {
                                m.dependencies = section_elements.data[0].obj;
                            } else {
                                m.dependencies = NULL;
                            }
                            wmgr_vect_delete(section_elements);
                            break;
                        case ms_out:
                            if (section_elements.size) {
                                m.out = section_elements.data[0].obj;
                            } else {
                                m.out = (char *)malloc(4 * sizeof(char));
                                m.out[0] = 'o';
                                m.out[1] = 'u';
                                m.out[2] = 't';
                                m.out[3] = '\0';
                            }
                            wmgr_vect_delete(section_elements);
                            break;
                        case ms_src:
                            if (section_elements.size > 0) {
                                m.src = section_elements.data[0].obj;
                            } else {
                                m.src = (char *)malloc(4 * sizeof(char));
                                m.src[0] = 's';
                                m.src[1] = 'r';
                                m.src[2] = 'c';
                                m.src[3] = '\0';
                            }
                            wmgr_vect_delete(section_elements);
                            break;
                        case ms_target:
                            m.targets = section_elements;
                            break;
                        case ms_mod:
                            m.mods = section_elements;
                            break;
                        default:
                            break;
                        }

                        
                        section_type = ms_null;
                        section_elements = wmgr_vect_null(2);
                    //}
                } else {
                    sv.len++;
                }
                break;
            }
        }
    }
    
    fclose(f);

    if (section_type != ms_null) {
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
    
    wmgr_vect_foreach(element_t, v, i, m.targets) {
        if (v.format != NULL) {
            len += sprintf(out + len, "%s %s -f %s\n",
                m.cc, v.obj, v.format
            );
        }
    }
    out[len++] = '\n';
    
    wmgr_vect_foreach(element_t, v, i, m.targets) {
        if (v.format != NULL) {
            len += sprintf(out + len, "mv %s.%s ../%s/%s.%s\n",
                v.obj, v.format, m.out, v.obj, v.format
            );
        }
    }

    wmgr_vect_foreach(element_t, v, i, m.targets) {
        if (v.format == NULL) {
            len += sprintf(out + len, "cp %s ../%s/%s\n",
                v.obj, m.out, v.obj
            );
        }
    }

    out[len] = '\0';

    char out_path[2048];
    strcpy(out_path, m.build);
    strcat(out_path, ".sh");
    FILE *f = fopen(out_path, "w");
    fprintf(f, "%s", out);
    fclose(f);
    #elif defined(_WIN32)
    if (m.assets[0] != NULL) {
        len += sprintf(out, "rd /s /q \"%s/%s\"\nrobocopy \"%s\" \"%s/%s\" /E\n\n",
            m.out, m.assets[1] != NULL ? m.assets[1] : m.assets[0],
            m.assets[0], m.out, m.assets[1] != NULL ? m.assets[1] : m.assets[0]
        );
    }
    len += sprintf(out + len, "cd \"%s\"\n\n", m.src);
    
    wmgr_vect_foreach(element_t, v, i, m.targets) {
        if (v.format != NULL) {
            len += sprintf(out + len, "%s %s -f %s\n",
                m.cc, v.obj, v.format
            );
        }
    }
    out[len++] = '\n';
    
    wmgr_vect_foreach(element_t, v, i, m.targets) {
        if (v.format != NULL) {
            len += sprintf(out + len, "move \"%s.%s\" \"../%s/%s.%s\"\n",
                v.obj, v.format, m.out, v.obj, v.format
            );
        }
    }
    
    wmgr_vect_foreach(element_t, v, i, m.targets) {
        if (v.format == NULL) {
            len += sprintf(out + len, "copy \"%s\" \"../%s/%s\"\n",
                v.obj, m.out, v.obj
            );
        }
    }

    out[len] = '\0';

    char out_path[2048];
    strcpy(out_path, m.build);
    strcat(out_path, ".bat");
    FILE *f = fopen(out_path, "w");
    fprintf(f, "%s", out);
    fclose(f);
    #endif

    free(out);
}

uint8_t wmgr_is_valid_name(const char *name) {
    const char *p = name;
    for (char c = *p; *p != '\0'; p++) {
        switch (c) {
            case '_':
            case '-':
            case '.':
                if (p == name)
                    return 0;
                continue;
            default:
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
                    continue;
                else
                    return 0;
        }
    }
    return 1;
}

void create_xmw_project(const char *name) {
    if (!wmgr_is_valid_name(name))
        fatal("invalid project name: allowed characters [a-z, A-Z, 0-9] and [_, -, .] (the latter cannot be the first character)");
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
    sprintf(buffer, "%s/src/templates", name);
    create_folder(buffer);
    sprintf(buffer, "%s/src/configs", name);
    create_folder(buffer);
    sprintf(buffer, "%s/src/templates/page_structure", name);
    create_folder(buffer);
    sprintf(buffer, "%s/src/templates/pretty", name);
    create_folder(buffer);

    sprintf(buffer, "%s/src/%s", name, "index.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A1)");
    fprintf(f, "%s", WMGR_BOILERPLATE_DEFAULT_INDEX_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/configs/%s", name, "config.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A2)");
    fprintf(f, WMGR_BOILERPLATE_DEFAULT_CONFIG_HTMW, name);
    fclose(f);

    sprintf(buffer, "%s/src/configs/%s", name, "header.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A3)");
    fprintf(f, "%s", WMGR_BOILERPLATE_DEFAULT_HEADER_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/%s", name, "style.css");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A4)");
    fprintf(f, "%s", WMGR_BOILERPLATE_DEFAULT_STYLE_CSS);
    fclose(f);

    sprintf(buffer, "%s/src/%s", name, "i.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A5)");
    fprintf(f, "%s", WMGR_BOILERPLATE_DEFAULT_I_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/templates/page_structure/%s", name, "Page.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A6)");
    fprintf(f, "%s", WMGR_BOILERPLATE_DEFAULT_PAGE_HTMW);
    fclose(f);

    sprintf(buffer, "%s/src/templates/pretty/%s", name, "Text.htmw");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A7)");
    fprintf(f, "%s", WMGR_BOILERPLATE_DEFAULT_PRETTYTEXT_HTMW);
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
    fprintf(f, "rd /s /q \"out/assets\"\nrobocopy \"assets\" \"out/assets\" /E\n\ncd \"src\"\n\n%s index -f html\n\nmove \"index.html\" \"../out/index.html\"\ncopy \"style.css\" \"../out/style.css\"", COMMAND_HTMW);
    #endif
    fclose(f);

    sprintf(buffer, "%s/%s", name, "make.txt");
    f = fopen(buffer, "w");
    if (f == NULL)
        fatal("An error has occurred (A4)");
    fprintf(f, WMGR_BOILERPLATE_DEFAULT_MAKE_TXT, COMMAND_HTMW);
    fclose(f);

    free(buffer);
}

void wmgr_print_row(const char *cmd, const char *desc) {
    printf("%-30s %s\n", cmd, desc);
}

void wmgr_print_actions() {
    wmgr_print_row("make", "Reads `make.txt` file and generates a shell/batch script to build your project");
    wmgr_print_row("new <name>", "Creates a new project in a named folder");
    wmgr_print_row("test", "Hosts a local test environment");
    wmgr_print_row("ver", "Displays the installed WMGR version");
}