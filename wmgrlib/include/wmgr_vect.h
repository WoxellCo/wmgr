#ifndef WMGR_VECT_H
#define WMGR_VECT_H

#ifndef __cplusplus
    #include <stddef.h>
#endif

#define wmgr_vect(ID, TYPE) \
struct wmgr_vect_##ID { \
    size_t size; \
    size_t capacity; \
    TYPE *data; \
}

#define wmgr_def_vect_push_back(ID, TYPE) \
void wmgr_vect_push_back_##ID(struct wmgr_vect_##ID *vector, TYPE data) { \
    if (vector->size >= vector->capacity) {\
        TYPE *t = (TYPE *)realloc(vector->data, (vector->capacity * 1.5) * sizeof(TYPE)); \
        if (t == NULL) \
            {return;} \
        vector->data = t; \
        vector->capacity = vector->capacity * 1.5; \
    } \
    vector->data[vector->size++] = data; \
}

#define wmgr_vect_new(ID, TYPE, INIT) \
    ((struct wmgr_vect_##ID) { \
        .capacity = INIT, \
        .size = 0, \
        .data = (TYPE *)malloc((INIT * 1.5) * sizeof(TYPE)) \
    })

#define wmgr_vect_delete(vector) \
    {free((vector).data);(vector).size = 0;(vector).capacity = 0;}

//void wmgr_vect_free_##ID(wmgr_vect_##ID *vector) {

#define wmgr_vect_is_null(vector) ((vector).data == NULL)

#define wmgr_vect_null(ID) ((struct wmgr_vect_##ID){0, 0, NULL})

#define wmgr_vect_foreach(TYPE, v, i, o) \
    for (size_t i = 0; i < (o).size; ++i) \
        for (int wmgr_brk_##i = 0; !wmgr_brk_##i; wmgr_brk_##i = 1) \
            for (TYPE v = (o).data[i]; !wmgr_brk_##i; wmgr_brk_##i = 1)

#endif