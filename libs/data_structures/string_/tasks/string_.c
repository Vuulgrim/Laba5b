//
// Created by vikir on 02.03.2022.
//
#include <stdio.h>
#include <ctype.h>

//сокращает количество пробелов между словами данного предложения до одного
void removeExtraSpaces(char *s) {
    if (!(*s))
        return;

    char *writePos = s;
    s++;
    while (*s) {
        if (isspace(*writePos) && isspace(*s))
            *writePos = ' ';
        else
            *(++writePos) = *s;
        s++;
    }
    *(++writePos) = '\0';
}