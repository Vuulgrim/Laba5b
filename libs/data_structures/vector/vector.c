//
// Created by vikir on 03.02.2022.
//

#include "vector.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

void badAlloc() {
    fprintf(stderr, "bad alloc");
    exit(1);
}

vector createVector(const size_t n) {
    vector v = {malloc(sizeof(int) * n), 0, n};
    if (v.data == NULL) {
        badAlloc();
    } else {
        return v;
    }
}

void reserve(vector *v, const size_t newCapacity) {
    v->data = realloc(v->data, sizeof(int) * newCapacity);
    v->capacity = newCapacity;
    v->size = newCapacity < v->size ? newCapacity : v->size;
    if (v->data == NULL && newCapacity != 0) {
        badAlloc();
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    reserve(v, v->size);
}

void deleteVector(vector *v) {
    reserve(v, 0);
}

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, const size_t i) {
    return v->data[i];
}

void pushBack(vector *v, const int x) {
    if (isFull(v) && v->capacity != 0) {
        reserve(v, v->capacity * 2);
    } else if (v->capacity == 0) {
        reserve(v, 1);
    }
    v->data[v->size] = x;
    v->size++;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        badAlloc();
    }
    v->size--;
}

int *atVector(vector *v, const size_t index) {
    if (index > v->size) {
        fprintf(stderr, "IndexError: a[%llu] is not exist\n", index);
        exit(1);
    }

    return v->data + index;
}

int *back(vector *v) {
    return atVector(v, v->size - 1);
}

int *front(vector *v) {
    return atVector(v, 0);
}