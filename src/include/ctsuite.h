//
//  ctsuite.h
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctsuite_h
#define ctsuite_h

#include "ctcase.h"

typedef struct ctsuite_t {
    const char *name;
    unsigned int count;
    unsigned int passed;
    unsigned int failed;
    void *_internal;
}ctsuite_t;

ctsuite_t *ctsuite(const char *name);
void ctscaseadd(ctsuite_t *tsuite, ctcase_t *tcase);
void ctsrun(ctsuite_t *tsuite);
void ctsfree(ctsuite_t *tsuite);

#endif /* ctsuite_h */
