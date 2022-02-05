#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include <assert.h>

void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(getVectorValue(&v, 0) == 1);
    assert(v.size == 1);
    assert(v.capacity == 1);
}

void test_pushBack_fullVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    assert(getVectorValue(&v, 1) == 2);
    assert(v.size == 2);
    assert(v.capacity == 2);
}

void test_popBack_nonEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_nonEmptyVector();
}

int main() {

    test();

    return 0;
}
