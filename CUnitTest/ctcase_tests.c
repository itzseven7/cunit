//
//  ctcase_tests.c
//  CUnitTest
//
//  Created by itzseven on 16/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctcase_tests.h"
#include "ctcase.h"
#include "_ctcase.h"
#include "_ctest.h"
#include <string.h>
#include <assert.h>
#include <unistd.h>

void ctcase_test_creation() {
    ctcase_t *tcase = ctcase("Test case");
    
    assert(strcmp(tcase->name, "Test case") == 0);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    assert(caseInternal->tests == NULL);
    assert(caseInternal->testCount == 0);
    assert(caseInternal->perfTests == NULL);
    assert(caseInternal->perfTestCount == 0);
    assert(caseInternal->passed == 0);
    assert(caseInternal->failed == 0);
}

void ctcase_test_add_test() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctestadd(tcase, ctest("Test", NULL, NULL));
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    assert(caseInternal->tests != NULL);
    assert(caseInternal->testCount == 1);
}

void ctcase_test_add_perf() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctestperfadd(tcase, ctest("Test", NULL, NULL), 20);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    assert(caseInternal->perfTests != NULL);
    assert(caseInternal->perfTestCount == 1);
}

ctest_return_t ctcase_test_run_test_pass_inv(ctest_t *test, void *arg) {
    return;
}

void ctcase_test_run_test_pass() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctest_t *test = ctest("Test", ctcase_test_run_test_pass_inv, NULL);
    
    _tcruntest(tcase, test);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->passed == 1);
}

ctest_return_t ctcase_test_run_test_fail_inv(ctest_t *test, void *arg) {
    ctestfail(test);
    ctestfail(test);
    return;
}

void ctcase_test_run_test_fail() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctest_t *test = ctest("Test", ctcase_test_run_test_fail_inv, NULL);
    
    _tcruntest(tcase, test);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->failed == 1);
}

ctest_return_t ctcase_test_run_perf_pass_inv(ctest_t *test, void *arg) {
    sleep(3);
    return;
}

void ctcase_test_run_perf_pass() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctperf_t *tperf = ctperf(ctest("Test", ctcase_test_run_perf_pass_inv, NULL), 5);
    
    _tcrunperf(tcase, tperf);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->passed == 1);
}

ctest_return_t ctcase_test_run_perf_fail_inv(ctest_t *test, void *arg) {
    sleep(5);
    return;
}

void ctcase_test_run_perf_fail() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctperf_t *tperf = ctperf(ctest("Test", ctcase_test_run_perf_fail_inv, NULL), 3);
    
    _tcrunperf(tcase, tperf);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->failed == 1);
}

void ctcase_tests() {
    ctcase_test_creation();
    ctcase_test_add_test();
    ctcase_test_add_perf();
    ctcase_test_run_test_pass();
    ctcase_test_run_test_fail();
    ctcase_test_run_perf_pass();
    ctcase_test_run_perf_fail();
}
