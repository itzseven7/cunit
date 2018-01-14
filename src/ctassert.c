//
//  ctassert.c
//  cunit
//
//  Created by itzseven on 30/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "ctassert.h"
#include "_ctest.h"

void _cfail(const ctest_t *test, const char *expr1, const char *assertion, const char *expr2, const char *filename, unsigned long lineNumber, const char * format, ...) {
    
    ((ctest_int_t *)test->_internal)->failures++;
    
    char buffer[strlen(filename) + strlen(expr1) + strlen(assertion) + strlen(expr2) + strlen (format) + 50];
    sprintf(buffer, "Assertion failed at line %lu of file %s => %s %s %s\n%s", lineNumber, filename, expr1, assertion, expr2, format);
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, buffer, argptr);
    va_end(argptr);
}
