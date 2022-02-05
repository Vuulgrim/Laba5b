//
// Created by vikir on 03.02.2022.
//

#include "vector.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

void badAlloc() {
    fprintf(stderr, "bad alloc");
    exit(1);
}

vector createVector(size_t n) {
    vector v = {malloc(sizeof(int) * n), 0, n};
    if (v.data == NULL) {
        badAlloc();
    } else {
        return v;
    }
}

void reserve(vector *v, size_t newCapacity) {
    v->data = realloc(v->data, sizeof(int) * newCapacity);
    if (v->size == newCapacity) {
        v->size = newCapacity;
    }
    if (v->data == NULL) {
        badAlloc();
    }
    if (newCapacity == 0) {
        return;
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    reserve(v, v->size);
}

void deleteVector (vector *v){
    reserve(v, 0);
}