//
//  _ctcase.h
//  cunit
//
//  Created by itzseven on 13/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef _ctcase_h
#define _ctcase_h

#include "ctperf.h"

typedef struct ctestlist_t {
    ctest_t *test;
    struct ctestlist_t *next;
}ctestlist_t;

typedef struct ctperflist_t {
    ctperf_t *tperf;
    struct ctperflist_t *next;
}ctperflist_t;

typedef struct ctcase_int_t {
    ctestlist_t *tests;
    unsigned int testCount;
    ctperflist_t *perfTests;
    unsigned int perfTestCount;
    unsigned int passed;
    unsigned int failed;
}ctcase_int_t;

void _tcrun(ctcase_t *tcase);
void _tcruntest(ctcase_t *tcase, ctest_t *test);
void _tcrunperf(ctcase_t *tcase, ctperf_t *perf);

#endif /* _ctcase_h */
