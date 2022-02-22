//
// Created by vikir on 13.02.2022.
//

#include "matrix.h"
#include <malloc.h>
#include <assert.h>


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
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(ms[i]);
    }
    free(ms->values);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d", m.values[i][j]);
        }
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
    for (int i = 0; i < m.nCols; i++) {
        int arrayRow[m.nRows];
        for (int j = 0; j < m.nRows; j++) {
            arrayRow[j] = m.values[i][j];
        }
        arrayOfCriteria[i] = criteria(arrayRow, m.nRows);
    }

    for (int j = 1; j < m.nCols; j++) {
        int k = j;
        while (k != 0 && arrayOfCriteria[k - 1] > arrayOfCriteria[k]) {
            swapRows(m, k - 1, k);
            swap(&arrayOfCriteria[k - 1], &arrayOfCriteria[k]);

            k--;
        }
    }
}

bool isSquareMatrix(matrix m) {
    if (m.nRows == m.nCols) {
        return true;
    } else {
        return false;
    }
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false;
    } else {
        for (int i = 0; i < m1.nRows; i++) {
            for (int j = 0; j < m1.nCols; j++) {
                if (m1.values[i][j] != m2.values[i][j]) {
                    return false;
                }
            }
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
    if (isSquareMatrix(m) == false) {
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