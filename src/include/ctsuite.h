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
#include "ctperf.h"

typedef struct ctcaselist_t {
    ctcase_t *tcase;
    struct ctcaselist_t *next;
}ctcaselist_t;

typedef struct ctperflist_t {
    ctperf_t *tperf;
    struct ctperflist_t *next;
}ctperflist_t;

typedef struct ctsuite_t {
    const char *name;
    int count;
    int passed;
    int failed;
    ctcaselist_t *tcaselist;
    ctperflist_t *tperflist;
}ctsuite_t;

ctsuite_t *ctsuite(const char *name);

void ctsaddc(ctcase_t *tcase, ctsuite_t *tsuite);
void ctsaddp(ctperf_t *tperf, ctsuite_t *tsuite);
void ctsrun(ctsuite_t *tsuite);

#endif /* ctsuite_h */
