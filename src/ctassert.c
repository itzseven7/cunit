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

void _cfail(const ctest_t *test, const char *assertion, const char *filename, unsigned long lineNumber, const char * format, ...) {
    
    ((ctest_int_t *)test->_internal)->failures++;
    
    char buffer[strlen(assertion) + strlen(filename) + strlen (format) + 50];
    sprintf(buffer, "%s failed at line %lu of file %s.\n%s", assertion, lineNumber, filename, format);
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, buffer, argptr);
    va_end(argptr);
}
