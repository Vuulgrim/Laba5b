//
// Created by vikir on 13.02.2022.
//

#include "matrix.h"
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *arrayOfMatrices = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        arrayOfMatrices[i] = getMemMatrix(nRows, nCols);
    return arrayOfMatrices;
}

void freeMemMatrix(matrix m) {
    int rows = m.nRows;
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *arrayOfMatrices, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(arrayOfMatrices[i]);
    }
    free(arrayOfMatrices->values);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);
        }
    }
}

void inputMatrices(matrix *arrayOfMatrices, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(arrayOfMatrices[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2) {
    swap((int *) &m.values[i1], (int *) &m.values[i2]);
}

void swapColumns(matrix m, int j1, int j2) {
    if (j1 >= m.nCols || j2 >= m.nCols) {
        exit(1);
    }
    for (int i = 0; i < m.nRows; i++) {
        swap(&m.values[i][j1], &m.values[i][j2]);
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int arrayOfCriteria[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        arrayOfCriteria[i] = criteria(m.values[i], m.nCols);
    }

    for (int j = 1; j < m.nRows; j++) {
        int k = j;
        while (k != 0 && arrayOfCriteria[k - 1] > arrayOfCriteria[k]) {
            swapRows(m, k - 1, k);
            swap(&arrayOfCriteria[k - 1], &arrayOfCriteria[k]);
            k--;
        }
    }
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int arrayOfCriteria[m.nCols];
    for (size_t i = 0; i < m.nCols; i++) {
        int arrayRow[m.nRows];
        for (size_t j = 0; j < m.nRows; j++) {
            arrayRow[j] = m.values[i][j];
        }
        arrayOfCriteria[i] = criteria(arrayRow, m.nRows);
    }

    for (int j = 1; j < m.nCols; j++) {
        int k = j;
        while (k != 0 && arrayOfCriteria[k - 1] > arrayOfCriteria[k]) {
            swap(&arrayOfCriteria[k - 1], &arrayOfCriteria[k]);
            swapColumns(m, k - 1, k);
            k--;
        }
    }
}

bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false;
    } else {
        for (int i = 0; i < m1.nRows; i++) {
            if (memcmp(m1.values[i], m2.values[i], sizeof(int) * m1.nCols) != 0)
                return false;
        }
    }

    return true;
}

bool isEMatrix(matrix m) {
    if (isSquareMatrix(m) == false) {
        return false;
    }
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if ((i != j && m.values[i][j] != 0) || (i == j && m.values[i][j] != 1))
                return false;
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        return false;
    }
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; i++)
            if (m.values[i][j] != m.values[j][i])
                return false;
    return true;
}

void transposeSquareMatrix(matrix m) {
    if (isSquareMatrix(m)) {
        for (int i = 0; i < m.nRows; i++)
            for (int j = 0; j < m.nCols; i++)
                if (i == j)
                    swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
    } else {
        exit(1);
    }
}

position getMinValuePos(matrix m) {
    int minValue = m.values[0][0];
    position minPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 1; j < m.nCols; i++) {
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.colIndex = j;
                minPos.rowIndex = i;
            }
        }
    }

    return minPos;
}

position getMaxValuePos(matrix m) {
    int maxValue = m.values[0][0];
    position maxPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 1; j < m.nCols; i++) {
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxPos.colIndex = j;
                maxPos.rowIndex = i;
            }
        }
    }

    return maxPos;
}

matrix createMatrixFromArray(const int *a,
                             int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

//1
void swapRowsOfMinAndMax(matrix m) {
    position max = getMaxValuePos(m);
    position min = getMinValuePos(m);
    swapRows(m, max.rowIndex, min.rowIndex);
}

//2
int getMax(const int *a, int n) {
    int maxValue = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > maxValue)
            maxValue = a[i];
    return maxValue;
}

void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

//3
int getMin(const int *a, int n) {
    int minValue = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < minValue)
            minValue = a[i];
    return minValue;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}

//4
matrix mulMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nRows) {
        fprintf(stderr, "matrices cannot be multiplied");
        exit(1);
    }

    matrix multiplicationMatrix = getMemMatrix(m1.nRows, m2.nCols);

    for (int indexRowM1 = 0; indexRowM1 < m1.nRows; indexRowM1++)
        for (int indexColM2 = 0; indexColM2 < m2.nCols; indexColM2++) {
            multiplicationMatrix.values[indexRowM1][indexColM2] = 0;
            for (int indexRowM2 = 0; indexRowM2 < m2.nRows; indexRowM2++)
                multiplicationMatrix.values[indexRowM1][indexColM2] +=
                        m1.values[indexRowM1][indexRowM2]
                        * m2.values[indexRowM2][indexColM2];
        }

    return (matrix) multiplicationMatrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSquareMatrix(*m)) {
        *m = mulMatrices(*m, *m);
    }
}

//5
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (a[i] == a[j])
                return false;
        }
    }
    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    int a[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        a[i] = getSum(m.values[i], m.nCols);
    }
    if (isUnique(a, m.nRows) == true)
        transposeSquareMatrix(m);
}

//6
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix m3 = mulMatrices(m1, m2);
    if (!isEMatrix(m3))
        return false;
    return true;
}

//7
int max(int a, int b) {
    return a > b ? a : b;
}

int getMaxElementFromDiagonal(matrix m, int iRow, int iCol) {
    int maxValue = m.values[iRow][iCol];
    while (iRow < m.nRows && iCol < m.nCols)
        maxValue = max(maxValue, m.values[iRow++][iCol++]);
    return maxValue;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int sum = 0;
    for (int i = 1; i < m.nRows; i++) {
        sum += getMaxElementFromDiagonal(m, i, 0);
    }

    for (int j = 1; j < m.nCols; j++) {
        sum += getMaxElementFromDiagonal(m, 0, j);
    }
    return sum;
}

//8
int min(int a, int b) {
    return a < b ? b : a;
}

int getMinInArea(matrix m) {
    position minPos = getMaxValuePos(m);
    int minElement = m.values[minPos.rowIndex][minPos.colIndex];

    int jRight = minPos.colIndex;
    int jLeft = minPos.colIndex;
    for (int i = minPos.rowIndex - 1; i >= 0; i--) {
        jLeft = jLeft > 0 ? jLeft - 1 : jLeft;
        jRight = jRight < m.nCols ? jRight + 1 : jRight;
        minElement = min(getMin(&m.values[i][jLeft], jRight - jLeft), minElement);
    }
    return minElement;
}


void transposeMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; i++)
            if (i == j)
                swap((int *) &m.values[i][j], (int *) &m.values[j][i]);
}

//9
float getDistance(int *a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(a[i], 2);
    return sqrt(sum);
}

void swapF(float *a, float *b) {
    float temp = *b;
    *b = *a;
    *a = temp;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (criteria)(int *, int)) {
    float criteriaArray[m.nRows];
    for (size_t i = 0; i < m.nRows; ++i)
        criteriaArray[i] = criteria(m.values[i], m.nCols);

    for (int i = 1; i < m.nRows; ++i) {
        int j = i;
        while (j > 0 && criteriaArray[j - 1] > criteriaArray[j]) {
            swapF(&criteriaArray[j - 1], &criteriaArray[j]);
            swapRows(m, j - 1, j);

            j--;
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

//10
int cmp_long_long(const void *pa, const void *pb) {
    long long a = *((long long *) pa);
    long long b = *((long long *) pb);

    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}

//???????????? ???????????? ?????????????? ???????????? ???????? int, ?? ???? bool?
int countNUnique(long long *a, int n) {

    qsort(a, n, sizeof(long long), cmp_long_long);
    for (int i = 0; i < n; i++) {
        if (a[i - 1] == a[i]) {
            return 0;
        }
    }

    return 1;
}

int countEqClassesByRowsSum(matrix m) {
    long long *arrayOfSums = (long long *) malloc(sizeof(long long) * m.nRows);
    for (int i = 0; i < (m).nRows; ++i) {
        arrayOfSums[i] = getSum((m).values[i], (m).nCols);
    }
    for (int i = 0; i < m.nRows; i++) {
        arrayOfSums[i] = getSum(m.values[i], m.nCols);
    }
    int unique = countNUnique(arrayOfSums, m.nRows);

    return unique;
}

//11
int getNSpecialElement(const matrix m) {
    int counter = 0;

    for (int i = 0; i < m.nCols; i++) {
        long long currentSum = 0;
        for (int j = 0; j < m.nRows; j++)
            currentSum += m.values[j][i];
        for (int j = 0; j < m.nRows; j++)
            if (currentSum < 2 * m.values[j][i])
                counter++;
    }

    return counter;
}

//12
position getLeftMin(matrix m) {
    position minPos = (position) {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            int min = m.values[minPos.rowIndex][minPos.colIndex];
            if (j < minPos.colIndex && m.values[i][j] == min || m.values[i][j] < min) {
                minPos = (position) {i, j};
            }
        }
    }

    return minPos;
}

void swapPenultimateRow(matrix m, int n) {
    int penultimateRow = m.nRows - 2;
    int minColIndex = getLeftMin(m).colIndex;
    int *minCol = (int *) malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++) {
        minCol[i] = m.values[i][minColIndex];
    }

    memcpy(m.values[penultimateRow], minCol, sizeof(int) * m.nCols);
}

//13
bool isNonDescendingSorted(const int *a, const int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])
            return false;
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nRows))
            return false;
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int counterSortedMatrices = 0;
    for (int i = 0; i < nMatrix; i++) {
        counterSortedMatrices += hasAllNonDescendingRows(ms[i]);
    }
    return counterSortedMatrices;
}

//14

int countValues(const int *a, int n, int value) {
    int counterValue = 0;
    for (int i = 0; i < n; ++i)
        counterValue += a[i] == value;

    return counterValue;
}

int countZeroRows(matrix m) {
    int counterOfZeroRows = 0;
    for (int i = 0; i < (m).nRows; i++)
        counterOfZeroRows += countValues((m).values[i], (m).nCols, 0) == (m).nCols;

    return counterOfZeroRows;
}

void printMatrixWithMaxZeroRows(matrix *arrayOfMatrices, int nMatrix) {
    int maxZeroRows = 0;
    for (int i = 0; i <
                    nMatrix; i++) {
        int counterZeroRows = countZeroRows(arrayOfMatrices[i]);
        if (maxZeroRows < counterZeroRows)
            maxZeroRows = counterZeroRows;
    }

    for (int i = 0; i < nMatrix; i++) {
        if (countZeroRows(arrayOfMatrices[i]) == maxZeroRows)
            outputMatrix(arrayOfMatrices[i]);
    }
}

//15

float getAbsoluteMax(matrix m) {
    float absoluteMax = fabs((m).values[0][0]);
    for (int i = 0; i < (m).nRows; i++) {
        for (int j = 0; j < (m).nCols; j++) {
            float absValue = fabs((m).values[i][j]);
            if (absoluteMax < absValue)
                absoluteMax = absValue;
        }
    }

    return absoluteMax;
}

void printMatrixWithMinNormMax(matrix *arrayOfMatrices, int nMatrix) {
    float minAbsoluteMax = getAbsoluteMax(arrayOfMatrices[0]);
    for (int i = 1; i < nMatrix; i++) {
        float absoluteMax = getAbsoluteMax(arrayOfMatrices[i]);
        if (minAbsoluteMax > absoluteMax)
            minAbsoluteMax = absoluteMax;
    }

    for (int i = 0; i < nMatrix; i++) {
        if (getAbsoluteMax(arrayOfMatrices[i]) - minAbsoluteMax)
            outputMatrix(arrayOfMatrices[i]);
    }
}