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
#include <stdlib.h>
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
    
    ctcfree(tcase);
}

void ctcase_test_add_test() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctctestadd(tcase, ctest("Test 1", NULL, NULL));
    
    ctctestadd(tcase, ctest("Test 2", NULL, NULL));
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    assert(caseInternal->tests != NULL);
    assert(caseInternal->testCount == 2);
    
    ctcfree(tcase);
}

void ctcase_test_add_perf() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctcperfadd(tcase, ctest("Test 1", NULL, NULL), 20);
    ctcperfadd(tcase, ctest("Test 2", NULL, NULL), 30);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    assert(caseInternal->perfTests != NULL);
    assert(caseInternal->perfTestCount == 2);
    
    ctcfree(tcase);
}

ctest_return_t ctcase_test_run_test_pass_inv(ctest_t *test, void *arg) {
    return;
}

void ctcase_test_run_test_pass() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctest_t *test = ctest("Test", ctcase_test_run_test_pass_inv, NULL);
    
    _ctcruntest(tcase, test);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->passed == 1);
    
    ctcfree(tcase);
    ctfree(test);
}

ctest_return_t ctcase_test_run_test_fail_inv(ctest_t *test, void *arg) {
    ctestfail(test);
    ctestfail(test);
    return;
}

void ctcase_test_run_test_fail() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctest_t *test = ctest("Test", ctcase_test_run_test_fail_inv, NULL);
    
    _ctcruntest(tcase, test);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->failed == 1);
    
    ctcfree(tcase);
    ctfree(test);
}

ctest_return_t ctcase_test_run_perf_pass_inv(ctest_t *test, void *arg) {
    sleep(3);
    return;
}

void ctcase_test_run_perf_pass() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctperf_t *tperf = ctperf(ctest("Test", ctcase_test_run_perf_pass_inv, NULL), 5);
    
    _ctcrunperf(tcase, tperf);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->passed == 1);
    
    ctpfree(tperf);
    ctcfree(tcase);
}

ctest_return_t ctcase_test_run_perf_fail_inv(ctest_t *test, void *arg) {
    sleep(5);
    return;
}

void ctcase_test_run_perf_fail() {
    ctcase_t *tcase = ctcase("Test case");
    
    ctperf_t *tperf = ctperf(ctest("Test", ctcase_test_run_perf_fail_inv, NULL), 3);
    
    _ctcrunperf(tcase, tperf);
    
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    assert(caseInternal->failed == 1);
    
    ctcfree(tcase);
    ctpfree(tperf);
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
