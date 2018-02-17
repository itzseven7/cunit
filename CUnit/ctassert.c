//
//  ctassert.c
//  cunit
//
//  Created by itzseven on 30/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ctassert.h"
#include "_ctest.h"

void _ctfail(ctest_t *test, const char *expr1, const char *assertion, const char *expr2, const char *filename, unsigned long lineNumber, const char * format, ...) {
    
    ctestfail(test);
    
    char buffer[strlen(filename) + strlen(expr1) + strlen(assertion) + strlen(expr2) + strlen (format) + 50];
    sprintf(buffer, "Assertion failed at line %lu of file %s => %s %s %s\n%s", lineNumber, filename, expr1, assertion, expr2, format);
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, buffer, argptr);
    va_end(argptr);
}

int _ctarraycmp(void *arr1, void *arr2, size_t asize, size_t atsize, int (* _aeltcmp)(const void *, const void *)) {
    size_t i = 0;
    int tmp = 0;
    void *elt1 = arr1, *elt2 = arr2;
    
    for (i = asize; i--; ) {
        tmp += abs(_aeltcmp(elt1, elt2));
        elt1 += atsize;
        elt2 += atsize;
    }
    
    return tmp;
}
