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

void test_testAtVector_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    assert(atVector(&v, 1) == v.data + 1);
}

void test_testAtVector_requestToLastElement() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    assert(atVector(&v, v.size - 1) == v.data + v.size + 1);
}

void test_testAtVector_requestToFirstElement() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    assert(atVector(&v, 0) == v.data);
}

void test_back_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(back(&v) == v.data + v.size - 1);
}

void test_front_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(front(&v) == v.data);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_nonEmptyVector();
    test_testAtVector_notEmptyVector();
    test_testAtVector_requestToLastElement();
    test_testAtVector_requestToFirstElement();
    test_back_oneElementInVector();
}

int main() {

    test();

    return 0;
}
