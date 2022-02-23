#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
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
    assert(atVector(&v, v.size - 1) == v.data + v.size - 1);
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

void test_swapRows_standartMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  4, 5, 6}, 2, 3);
    matrix needM = createMatrixFromArray((int[]) {4, 5, 6,
                                                  1, 2, 3}, 2, 3);
    swapRows(readM, 0, 1);
    assert(twoMatricesEqual(readM, needM));

    freeMemMatrix(readM);
    freeMemMatrix(needM);
}
void test_swapRows() {
    test_swapRows_standartMatrix();
}

void test_swapColumns_standartMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  4, 5, 6}, 2, 3);
    matrix needM = createMatrixFromArray((int[]) {2, 1, 3,
                                                  5, 4, 6}, 2, 3);
    swapColumns(readM, 0, 1);
    assert(twoMatricesEqual(readM, needM));

    freeMemMatrix(readM);
    freeMemMatrix(needM);
}
void test_swapColumns() {
    test_swapColumns_standartMatrix();
}

void test_swapRows_defaultMatrix() {
    matrix read = createMatrixFromArray((int[]) {1, 2, 3,
                                                 4, 5, 6}, 2, 3);

    matrix need = createMatrixFromArray((int[]) {4, 5, 6,
                                                 1, 2, 3}, 2, 3);

    swapRows(read, 0, 1);

    assert(twoMatricesEqual(read, need));

    freeMemMatrix(read);
    freeMemMatrix(need);
}

void test_swapCol_defaultMatrix() {
    matrix read = createMatrixFromArray((int[]) {1, 2, 3,
                                                 4, 5, 6}, 2, 3);

    matrix need = createMatrixFromArray((int[]) {2, 1, 3,
                                                 5, 4, 6}, 2, 3);

    swapColumns(read, 0, 1);

assert(twoMatricesEqual(read, need));

    freeMemMatrix(read);
    freeMemMatrix(need);
}

void test_swapCols() {
    test_swapCol_defaultMatrix();
}

void test_insertionSortRowsMatrixByCriteria_sumArr() {
    matrix read = createMatrixFromArray((int[]) {2, 2, 2,
                                                 3, 3, 3,
                                                 1, 1, 1}, 3, 3);

    matrix need = createMatrixFromArray((int[]) {1, 1, 1,
                                                 2, 2, 2,
                                                 3, 3, 3}, 3, 3);

    insertionSortRowsMatrixByRowCriteria(read, getSum);
    assert(twoMatricesEqual(read, need));

    freeMemMatrix(read);
    freeMemMatrix(need);
}

void test_insertionSortRowsByCriteria() {
    test_insertionSortRowsMatrixByCriteria_sumArr();
}

void test_insertionSortColsMatrixByCriteria_sumArr() {
    matrix read = createMatrixFromArray((int[]) {2, 1, 3,
                                                 2, 1, 3,
                                                 2, 1, 3}, 3, 3);

    matrix need = createMatrixFromArray((int[]) {1, 2, 3,
                                                 1, 2, 3,
                                                 1, 2, 3}, 3, 3);

    insertionSortColsMatrixByColCriteria(read, getSum);
    assert(twoMatricesEqual(read, need));

    freeMemMatrix(read);
    freeMemMatrix(need);
}

void test_insertionSortColsByCriteria() {
    test_insertionSortColsMatrixByCriteria_sumArr();
}

void test_isSquareMatrix_trueSquareMatrix() {
    matrix read = createMatrixFromArray((int[]) {1, 1, 1,
                                                 1, 1, 1,
                                                 1, 1, 1}, 3, 3);
    assert(isSquareMatrix(read));

    freeMemMatrix(read);
}

void test_isSquareMatrix_nonSquareMatrixBySize() {
    matrix readM = createMatrixFromArray((int[]) {1, 1, 1,
                                                  1, 1, 1}, 2, 3);
    assert(!isSquareMatrix(readM));

    freeMemMatrix(readM);
}

void test_isSquareMatrix() {
    test_isSquareMatrix_trueSquareMatrix();
    test_isSquareMatrix_nonSquareMatrixBySize();
}

void test_twoMatricesEqual_equalMatrices() {
    matrix readM = createMatrixFromArray((int[]) {42, 84, 126}, 1, 3);
    matrix needM = createMatrixFromArray((int[]) {42, 84, 126}, 1, 3);
    assert(twoMatricesEqual(readM, needM));

    freeMemMatrix(readM);
    freeMemMatrix(needM);
}

void test_twoMatricesEqual_nonEqualMatricesBySize() {
    matrix readM = createMatrixFromArray((int[]) {3, 2, 3}, 1, 3);
    matrix needM = createMatrixFromArray((int[]) {3, 2,
                                                  3, 4}, 2, 2);
    assert(!twoMatricesEqual(readM, needM));

    freeMemMatrix(readM);
    freeMemMatrix(needM);
}

void test_twoMatricesEqual_nonEqualMatricesByValue() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3}, 1, 3);
    matrix needM = createMatrixFromArray((int[]) {4, 2, 3}, 1, 3);
    assert(!twoMatricesEqual(readM, needM));

    freeMemMatrix(readM);
    freeMemMatrix(needM);
}

void test_twoMatricesEqual() {
    test_twoMatricesEqual_equalMatrices();
    test_twoMatricesEqual_nonEqualMatricesBySize();
    test_twoMatricesEqual_nonEqualMatricesByValue();
}

void test_isEMatrix_trueEMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 0,
                                                  0, 1}, 2, 2);
    assert(isEMatrix(readM));

    freeMemMatrix(readM);
}

void test_isEMatrix_nonEMatrixBySize() {
    matrix readM = createMatrixFromArray((int[]) {1, 0, 0,
                                                  0, 1, 0}, 2, 3);
    assert(!isEMatrix(readM));

    freeMemMatrix(readM);
}

void test_isEMatrix_nonEMatrixByValue() {
    matrix readM = createMatrixFromArray((int[]) {1, 2,
                                                  0, 1}, 2, 2);
    assert(!isEMatrix(readM));

    freeMemMatrix(readM);
}

void test_isEMatrix() {
    test_isEMatrix_trueEMatrix();
    test_isEMatrix_nonEMatrixBySize();
    test_isEMatrix_nonEMatrixByValue();
}

void test_isEMatrix_trueSymmetricMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  2, 5, 6,
                                                  3, 6, 9}, 3, 3);
    assert(isSymmetricMatrix(readM));

    freeMemMatrix(readM);
}

void test_isEMatrix_nonSymmetricMatrixBySize() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  2, 5, 6}, 2, 3);
    assert(!isSymmetricMatrix(readM));

    freeMemMatrix(readM);
}

void test_isEMatrix_nonSymmetricMatrixByValue() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  2, 5, 6,
                                                  3, 10, 9}, 3, 3);
    assert(!isSymmetricMatrix(readM));

    freeMemMatrix(readM);
}

void test_isSymmetricMatrix() {
    test_isEMatrix_trueSymmetricMatrix();
    test_isEMatrix_nonSymmetricMatrixBySize();
    test_isEMatrix_nonSymmetricMatrixByValue();
}

void test_transposeSquareMatrix_defaultMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  4, 5, 6,
                                                  7, 8, 9}, 3, 3);
    matrix needM = createMatrixFromArray((int[]) {1, 4, 7,
                                                  2, 5, 8,
                                                  3, 6, 9}, 3, 3);
    transposeSquareMatrix(readM);
    assert(twoMatricesEqual(readM, needM));

    freeMemMatrix(readM);
    freeMemMatrix(needM);
}

void test_transposeSquareMatrix() {
    test_transposeSquareMatrix_defaultMatrix();
}

void test_getMinValuePos_defaultMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  4, 5, 6}, 2, 3);
    position minIndex = getMinValuePos(readM);
    assert(minIndex.rowIndex == 0 && minIndex.colIndex == 0);

    freeMemMatrix(readM);
}

void test_getMinValuePos() {
    test_getMinValuePos_defaultMatrix();
}

void test_getMaxValuePos_defaultMatrix() {
    matrix readM = createMatrixFromArray((int[]) {1, 2, 3,
                                                  4, 5, 6}, 2, 3);
    position maxIndex = getMaxValuePos(readM);
    assert(maxIndex.rowIndex == 1 && maxIndex.colIndex == 2);

    freeMemMatrix(readM);
}

void test_getMaxValuePos() {
    test_getMaxValuePos_defaultMatrix();
}

void test_transposeIfMatrixHasNotEqualSumOfRows_hasEqualSum() {
    matrix m1 = createMatrixFromArray((int[]) {7, 1, 2,
                                               1, 8, 1,
                                               3, 1, 3}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]) {7, 1, 2,
                                               1, 8, 1,
                                               3, 1, 3}, 3, 3);
    transposeSquareMatrix(m1);
    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_matrix() {
    test_swapRows();
    test_swapCols();
    test_insertionSortRowsByCriteria();
    test_insertionSortColsByCriteria();
    test_isSquareMatrix();
    test_twoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_getMinValuePos();
    test_getMaxValuePos();
}
int main() {

    test_matrix();

    return 0;
}