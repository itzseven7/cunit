//
//  ctsuite.h
//  CUnit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctsuite_h
#define ctsuite_h

#include "ctcase.h"

typedef struct tcaselist_t {
    tcase_t *tcase;
    struct tcaselist_t *next;
}tcaselist_t;

typedef struct tsuite_t {
    const char *name;
    int count;
    int passed;
    int failed;
    tcaselist_t *tcaselist;
}tsuite_t;

tsuite_t *tsuitealloc(const char *name);
void tsuiteadd(tcase_t *tcase, tsuite_t *tsuite);
void tsuiterun(tsuite_t *tsuite);

#endif /* ctsuite_h */
