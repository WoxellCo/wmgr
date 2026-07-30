#ifndef WMGR_H
#define WMGR_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
    #if defined(__unix__) || defined(__APPLE__)
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
#include "wmgr_boilerplate.h"

#define WMGR_VER_MAJOR 0
#define WMGR_VER_MINOR 4
#define WMGR_VER_PATCH 3

#define WMGR_STRINGIFY(x) #x
#define WMGR_TOSTRING(x) WMGR_STRINGIFY(x)

#define WMGR_VER_STR \
    WMGR_TOSTRING(WMGR_VER_MAJOR) "." \
    WMGR_TOSTRING(WMGR_VER_MINOR) "." \
    WMGR_TOSTRING(WMGR_VER_PATCH)

//#define COMMAND_HTMW "~/Desktop/DevSpace/htmw/build/htmw"
#define COMMAND_HTMW "htmw"

static const uint32_t WMGR_VER[3] = { WMGR_VER_MAJOR, WMGR_VER_MINOR, WMGR_VER_PATCH };

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