#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/*
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
*/

#define TIME_TEST(testCode, time){ \
clock_t start_time = clock () ; \
testCode \
clock_t end_time = clock () ;\
clock_t sort_time = end_time - start_time ; \
time = ( double ) sort_time / CLOCKS_PER_SEC ; \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

void outputArray_(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d", arr[i]);
    }
}

void swap2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

//обменная сортировка
void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap2(&a[j - 1], &a[j]);
}

//сортировка выбором
void selectionSort(int *a, const size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap2(&a[i], &a[minPos]);
    }
}

//сортировка вставками
void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

//сортировка расческой
void combSort(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap2(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

//сортировка Шелла
void shellSort(int *a, const size_t size) {
    for (int step = size / 2; step > 0; step /= 2) {
        for (size_t i = step; i < size; i++) {
            int t = a[i];
            int j = i;
            while (j - step >= 0 && a[j - step] > t) {
                a[j] = a[j - step];
                j -= step;
            }
            a[j] = t;
        }
    }
}

//цифровая сортировка
void radixSort_(int *a, int *n) {
    int bit = 8;
    int k = (32 + bit - 1) / bit;
    int M = 1 << bit;
    int sz = n - a;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = a; j < n; j++)
            c[digit(*j, i, bit, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = n - 1; j >= a; j--)
            b[--c[digit(*j, i, bit, M)]] = *j;

        int cur = 0;
        for (int *j = a; j < n; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

void radixSort(int *a, size_t n) {
    radixSort_(a, a + n);
}

typedef struct SortFunc {
    void (*sort)(int *arr, int size);

    char arr[64];
} SortFunc;

typedef struct GeneratingFunc {
    void (*generate)(int *arr, int size);

    char arr[64];
} GeneratingFunc;

void generateOrderedArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = i;
    }
}

void generateOrderedBackwards(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = size - i;
    }
}

void generateRandomArray(int *a, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 10000;
    }
}

double getTime() {
    clock_t start_time = clock();

    clock_t end_time = clock();
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

bool isOrdered(int *arr, int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

void checkTime(void (*sortFunc)(int *, int), void (*generateFunc)(int *, int), int size, char *experimentName) {
    static int runCounter = 1;
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%d| ", runCounter++);
    printf("Name : %s\n", experimentName);

    double time;
    TIME_TEST({ sortFunc(innerBuffer, size); }, time)
// результаты замера
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);
// запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", "experiment");
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong !\n");

// вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);
        exit(1);
    }
}

void timeExperiment() {
// описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {shellSort, "shellSort"},
            {bubbleSort, "bubbleSort"},
            {combSort, "сombSort"},
            {radixSort, "radixSort"}
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

// описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            //{generateRandomArray, "random"} ,
            //{generateOrderedArray, "ordered"},
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

// запись статистики в файл
    for (int size = 10000; size <= 100000; size += 10000) {
        printf("-----------------------------------------------------\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
// генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ", sorts[i].arr, generatingFuncs[j].arr);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf("\n");
    }
}

int main() {
    timeExperiment();
    return 0;
}