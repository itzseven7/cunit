//
//  _ctcase.h
//  cunit
//
//  Created by itzseven on 13/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef _ctcase_h
#define _ctcase_h

typedef struct ctestlist_t {
    ctest_t *test;
    struct ctestlist_t *next;
}ctestlist_t;

typedef struct ctperf_t {
    ctest_t *test;
    double time;
}ctperf_t;

typedef struct ctperflist_t {
    ctperf_t *tperf;
    struct ctperflist_t *next;
}ctperflist_t;

typedef struct ctcase_int_t {
    ctestlist_t *testList;
    unsigned int testListCount;
    ctperflist_t *testPerfList;
    unsigned int testPerfListCount;
    unsigned int passed;
    unsigned int failed;
}ctcase_int_t;

void _tcrun(ctcase_t *tcase);

#endif /* _ctcase_h */
