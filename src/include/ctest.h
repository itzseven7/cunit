//
//  ctest.h
//  cunit
//
//  Created by itzseven on 13/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef ctest_h
#define ctest_h

#include "ctexpect.h"

struct ctest_t;

typedef void ctest_return_t;
typedef void ctopt_return_t;

typedef ctest_return_t (*ctinv_ptr_t)(struct ctest_t *test, void *arg);
typedef ctopt_return_t (*ctoptinv_ptr_t)(void *arg);

typedef struct ctest_t {
    const char *name;
    ctinv_ptr_t inv;
    void *arg;
    ctoptinv_ptr_t setup;
    ctoptinv_ptr_t tdown;
    void *_internal;
}ctest_t;

ctest_t *ctest(const char *name, ctinv_ptr_t inv, void *arg);
void fctest(ctest_t *test);

ctexpect_t *expectationWithDescription(ctest_t *test, const char *desc);
void waitForExpectationsWithTimeout(ctest_t *test, unsigned int timeout);

#endif /* ctest_h */
