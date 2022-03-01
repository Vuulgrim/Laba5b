//
// Created by vikir on 01.03.2022.
//

#include "string_.h"
#include <stdio.h>
#include <ctype.h>
#include <memory.h>

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch) {
        begin++;
    }
    return begin;
}

char *findNonSpace(char *begin) {
    while (begin != '\0') {
        if (!isspace(*begin)) {
            return begin;
        }
        begin++;
    }
    return begin;
}

char *findSpace(char *begin) {
    while (begin != '\0') {
        if (isspace(*begin)) {
            return begin;
        }
        begin++;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend) {
        if (!isspace(*rbegin))
            return rbegin;
        rbegin--;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend) {
        if (isspace(*rbegin))
            return rbegin;
        rbegin--;
    }
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs && *lhs == *rhs)
        rhs++, lhs++;
    return *lhs - *rhs;
}

char *copy(const char *beginSource, const char *endSource, char *beginDestination) {
    char size = endSource - beginSource;
    memcpy(beginDestination, beginSource, endSource - beginSource);

    return beginDestination + size;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    for (char *begin = beginSource; begin < endSource; begin++)
        if (f(*begin))
            *beginDestination++ = *begin;
    return beginDestination;
}

char *copyIfReverse(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    for (char *begin = beginSource; begin > endSource; begin--)
        if (f(*begin))
            *beginDestination++ = *begin;
    return beginDestination;
}