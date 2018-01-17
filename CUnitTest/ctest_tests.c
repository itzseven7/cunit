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
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

ctest_return_t ctest_test_invocation(ctest_t *test, void *arg) {
    return;
}

void ctest_test_creation() {
    int arg = 6;
    ctest_t *test = ctest("testExample", ctest_test_invocation, &arg);
    
    assert(strcmp(test->name, "testExample") == 0);
    assert(test->inv == ctest_test_invocation);
    assert(*((int *)test->arg) == 6);
    assert(test->setup == NULL);
    assert(test->tdown == NULL);
    assert(test->_internal != NULL);
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->expectations == NULL);
    assert(testInternal->expectCount == 0);
    assert(testInternal->failures == 0);
    assert(testInternal->unfulfilledExpectations == 0);
}

void ctest_test_add_expectation() {
    ctest_t *test = ctest("testExample", NULL, NULL);
    
    ctexpectwdesc(test, "testExpectation");
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->expectations != NULL);
    assert(testInternal->expectCount == 1);
}

void *testWaitThread(void *arg) {
    sleep(1);
    fulfill((ctexpect_t *)arg);
    
    pthread_exit(NULL);
}

void *testWaitTooLongThread(void *arg) {
    sleep(5);
    fulfill((ctexpect_t *)arg);
    pthread_exit(NULL);
}

ctest_return_t ctest_test_wait_expectation_valid_inv(ctest_t *test, void *arg) {
    ctexpect_t *expect = ctexpectwdesc(test, "Test expectation");
    
    pthread_t thread;
    
    if (pthread_create(&thread, NULL, testWaitThread, (void *)expect) != 0) {
        puts("Couldn't create thread\n");
    }
    
    ctexpectwait(test, 3);
}

ctest_return_t ctest_test_wait_expectation_too_long_inv(ctest_t *test, void *arg) {
    ctexpect_t *expect = ctexpectwdesc(test, "Test expectation too long");
    
    pthread_t thread;
    
    if (pthread_create(&thread, NULL, testWaitTooLongThread, (void *)expect) != 0) {
        puts("Couldn't create thread\n");
    }
    
    ctexpectwait(test, 3);
}

void ctest_test_wait_expectation_valid() {
    ctest_t *test = ctest("testExample", ctest_test_wait_expectation_valid_inv, NULL);
    test->inv(test, NULL);
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    assert(testInternal->unfulfilledExpectations == 0);
}

void ctest_test_wait_expectation_too_long() {
    ctest_t *test = ctest("testExample", ctest_test_wait_expectation_too_long_inv, NULL);
    test->inv(test, NULL);
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    assert(testInternal->unfulfilledExpectations == 1);
}

void ctest_tests() {
    ctest_test_creation();
    ctest_test_add_expectation();
    ctest_test_wait_expectation_valid();
    ctest_test_wait_expectation_too_long();
}
