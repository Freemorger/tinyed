/// Data structures util header

#pragma once

/// Dynamic array (don't forget to zero initialize!)
#define TE_VEC_DEFINE(elem_type, name) \
    typedef struct { \
        elem_type* data; \
        size_t     cap; \
        size_t     len; \
    } name;

#define TE_VEC_PUSH(xs, x) \
    do {\
        if (xs.len >= xs.cap) {\
            if (xs.cap == 0) xs.cap = 32;\
            else xs.cap *= 2;\
            void* tmp = realloc(xs.data, xs.cap*sizeof(*xs.data));\
            CHECK_NULL(tmp);\
            xs.data = tmp;\
        }\
        xs.data[xs.len++] = x;\
    } while (0)


/// Define a queue (circular buf) 
#define TE_QUEUE_DEFINE(elem_type, name) \
    typedef struct {\
        elem_type* data;\
        size_t     cap ;\
        size_t     len ;\
        size_t     head;\
        size_t     tail;\
    } name;\

/// Define methods for queue type `name` with element type `elem_type`
#define TE_QUEUE_DEF_METHODS(elem_type, name) \
    static void name##_grow(name* q) {\
        size_t new_cap;\
        if (q->cap == 0) new_cap = 32;\
        else new_cap = q->cap * 2;\
        \
        elem_type* new_data = malloc(new_cap * sizeof(*new_data));\
        CHECK_NULL(new_data);\
        \
        for (size_t i = 0; i < q->len; ++i) {\
            new_data[i] = q->data[(q->head + i) % q->cap];\
        }\
        \
        if (q->data != NULL) \
            free(q->data);\
        \
        q->data = new_data;\
        q->cap = new_cap;\
        q->head = 0;\
        q->tail = q->len;\
    }\
    static void name##_enqueue(name* q, elem_type e) {\
        if (q->len == q->cap) {\
            name##_grow(q);\
        }\
        q->data[q->tail] = e;\
        q->tail = (q->tail + 1) % q->cap;\
        q->len += 1;\
    }\
    \
    static bool name##_dequeue(name* q, elem_type* out) {\
        if (q->len == 0) {\
            return false;\
        }\
        *out = q->data[q->head];\
        q->head = (q->head + 1) % q->cap;\
        q->len -= 1;\
        return true;\
    }\
    static void name##_free(name* q) {\
        free(q->data);\
        q->data = NULL;\
        q->cap = q->len = q->head = q->tail = 0;\
    }
