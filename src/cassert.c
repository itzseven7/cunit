//
//  cassert.c
//  cunit
//
//  Created by itzseven on 30/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int _cfail(const char *assertion, const char *filename, unsigned long lineNumber, const char * format, ...) {
    
    char buffer[strlen(assertion) + strlen(filename) + strlen (format) + 50];
    sprintf(buffer, "%s failed at line %lu of file %s.\n%s", assertion, lineNumber, filename, format);
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, buffer, argptr);
    va_end(argptr);
    
    return 1;
}