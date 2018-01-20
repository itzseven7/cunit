//
//  ctsuite_tests.c
//  CUnitTest
//
//  Created by itzseven on 16/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctsuite_tests.h"
#include "ctsuite.h"
#include "_ctsuite.h"
#include "_ctest.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void ctsuite_test_creation() {
    ctsuite_t *suite = ctsuite("Test suite");
    
    assert(strcmp(suite->name, "Test suite") == 0);
    
    assert(suite->count == 0);
    assert(suite->passed == 0);
    assert(suite->failed == 0);
    
    ctsuite_int_t *suiteInternal = (ctsuite_int_t *)suite->_internal;
    
    assert(suiteInternal->tcases == NULL);
    assert(suiteInternal->tcaseCount == 0);
    
    ctsfree(suite);
}

void ctsuite_test_add_test_case() {
    ctsuite_t *suite = ctsuite("Test suite");
    
    ctcase_t *firstTestCase = ctcase("First test case");
    
    ctctestadd(firstTestCase, ctest("Test 1", NULL, NULL));
    ctctestadd(firstTestCase, ctest("Test 2", NULL, NULL));
    ctctestadd(firstTestCase, ctest("Test 3", NULL, NULL));
    
    ctscaseadd(suite, firstTestCase);
    
    ctcase_t *secondTestCase = ctcase("Second test case");
    ctctestadd(secondTestCase, ctest("Test 4", NULL, NULL));
    ctctestadd(secondTestCase, ctest("Test 5", NULL, NULL));
    
    ctscaseadd(suite, secondTestCase);
    
    ctsuite_int_t *suiteInternal = (ctsuite_int_t *)suite->_internal;
    
    assert(suite->count == 5);
    assert(suiteInternal->tcases != NULL);
    assert(suiteInternal->tcaseCount == 2);
    
    ctsfree(suite);
}

ctest_return_t ctsuite_test_run_pass_inv(ctest_t *test, void *arg) {
    return;
}

ctest_return_t ctsuite_test_run_fail_inv(ctest_t *test, void *arg) {
    ctestfail(test);
}

void ctsuite_test_run() {
    ctsuite_t *suite = ctsuite("Test suite");
    
    ctcase_t *casePass = ctcase("First test case");
    ctctestadd(casePass, ctest("First test", ctsuite_test_run_pass_inv, NULL));
    
    ctcase_t *caseFail = ctcase("Second test case");
    ctctestadd(caseFail, ctest("Second test", ctsuite_test_run_fail_inv, NULL));
    
    ctscaseadd(suite, casePass);
    ctscaseadd(suite, caseFail);
    
    ctsrun(suite);
    
    assert(suite->passed == 1);
    assert(suite->failed == 1);
    
    ctsfree(suite);
}

void ctsuite_tests() {
    ctsuite_test_creation();
    ctsuite_test_add_test_case();
    ctsuite_test_run();
}
