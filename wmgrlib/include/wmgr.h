#ifndef WMGR_H
#define WMGR_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
    #if defined(__unix__)
        #include <sys/stat.h>
        #include <sys/types.h>
    #elif defined(_WIN32)
        #include <windows.h>
    #endif
#endif

#ifndef __cplusplus
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stddef.h>
    #include <stdint.h>
#endif

#include "wmgr_vect.h"

#define DEFAULT_INDEX_HTMW "<@include_once \"config.htmw\">\n\
<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head/>\n\
<content>\n\
    <h1>Hello and welcome to <PrettyText><@{ APP.name }></PrettyText></h1>\n\
    <p>It works!</p>\n\
</content>\n\
</html>"

#define DEFAULT_CONFIG_HTMW "<@ntxt>\n\
<@area \"config\">\n\
\n\
<@ -> {\n\
    APP = {\n\
        name = \"%s\"\n\
    }\n\
}>\n\
\n\
<@template head(){}><#head>\n\
    <meta charset=\"UTF-8\">\n\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
    <title><@{ APP.name }></title>\n\
    <link rel=\"stylesheet\" href=\"style.css\">$INNER\n\
</#head></@template>\n\
\n\
<@template content(){}><body><@include \"header.htmw\"><main class=\"content-pad\">$INNER</main></body></@template>\n\
\n\
</@area>\n\
\n\
</@ntxt>"

#define DEFAULT_HEADER_HTMW "<@include_once \"config.htmw\">\n<div style=\"width: 100%; height: 64px; background-color: black; padding: 10px; position: fixed; top: 0px; display: flex; align-items: center;\">\n\
    <span style=\"font-size: 25px; font-weight: bold; color: white;\"><@{ APP.name }></span>\n\
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
.content-pad {\n\
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

#define WMGR_VER_MAJOR 0
#define WMGR_VER_MINOR 2
#define WMGR_VER_PATCH 0

#define WMGR_STRINGIFY(x) #x
#define WMGR_TOSTRING(x) WMGR_STRINGIFY(x)

#define WMGR_VER_STR \
    WMGR_TOSTRING(WMGR_VER_MAJOR) "." \
    WMGR_TOSTRING(WMGR_VER_MINOR) "." \
    WMGR_TOSTRING(WMGR_VER_PATCH)

//#define COMMAND_HTMW "~/Desktop/DevSpace/htmw/build/htmw"
#define COMMAND_HTMW "htmw"

static const uint32_t WMGR_VER[3] = { WMGR_VER_MAJOR, WMGR_VER_MINOR, WMGR_VER_PATCH };

#ifdef _WIN32
#error "WMGR is not currently supported on Windows"
#endif



typedef struct {
    char *obj;
    char *transf;
    char *format;
} element_t;

typedef wmgr_vect(1, char *) wmgr_cstring_vect;
typedef wmgr_vect(2, element_t) wmgr_element_vect;

// srting or element type
typedef union {
    wmgr_cstring_vect srtings;
    wmgr_element_vect elements;
} wmgr_se_list;

int create_folder(const char *path);
void fatal(const char *msg);

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

char *sv_alloc_from_view(str_view s);

typedef struct {
    char *cc;
    wmgr_element_vect targets;      // list >> <struct>
    //wmgr_cstring_vect mods;         // list >> char *
    wmgr_element_vect mods;      // list >> <struct>
    char *out;
    char *src;
    char *build;
    char *assets[2];      // char[2] *
    char *dependencies;
} make_t;

int parse_wmgr_elements(wmgr_element_vect *section_elements, char *begin, size_t length, make_sect ms);
make_t make(const char *path);
void make_out(make_t m);
void create_xmw_project(const char *name);
void wmgr_print_row(const char *cmd, const char *desc);
void wmgr_print_actions();



#ifdef __cplusplus
}
#endif

#endif