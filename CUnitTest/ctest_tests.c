//
//  ctest_tests.c
//  CUnitTest
//
//  Created by itzseven on 16/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctest_tests.h"
#include "ctest.h"
#include "_ctest.h"
#include <string.h>
#include <assert.h>

ctest_return_t ctest_test_invocation(ctest_t *test, void *arg) {
    
}

void ctest_test_creation() {
    int arg = 6;
    ctest_t *test = ctest("testExample", ctest_test_invocation, &arg);
    
    assert(strcmp(test->name, "testExample") == 0);
    assert(test->inv == ctest_test_invocation);
}

void ctest_tests() {
    ctest_test_creation();
}
