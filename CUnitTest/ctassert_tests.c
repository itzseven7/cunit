//
//  ctassert_tests.c
//  CUnitTest
//
//  Created by itzseven on 16/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctassert_tests.h"
#include "ctassert.h"
#include "_ctest.h"
#include <stdlib.h>
#include <assert.h>

void ctassert_test_fail() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTFail(test, "Test fail")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertEqual(test, 3 + 4, 7, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertEqual(test, 3 + 5, 7, "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_not_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertNotEqual(test, 3 + 5, 7, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertNotEqual(test, 3 + 4, 7, "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_true() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertTrue(test, ((3 + 4) == 7), "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertTrue(test, ((3 + 5) == 7), "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_false() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertFalse(test, ((3 + 5) == 7), "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertFalse(test, ((3 + 4) == 7), "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_null() {
    ctest_t *test = ctest("", NULL, NULL);
    
    void *ptr = NULL;
    
    CTAssertNull(test, ptr, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    ptr = malloc(1);
    
    CTAssertNull(test, ptr, "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
    free(ptr);
}

void ctassert_test_not_null() {
    ctest_t *test = ctest("", NULL, NULL);
    
    void *ptr = malloc(1);
    
    CTAssertNotNull(test, ptr, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    free(ptr);
    ptr = NULL;
    
    CTAssertNotNull(test, ptr, "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_greater_than() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertGreaterThan(test, 3 + 5, 7, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertGreaterThan(test, 3 + 3, 7, "")
    CTAssertGreaterThan(test, 3 + 4, 7, "")
    
    assert(testInternal->failures == 2);
    
    ctfree(test);
}

void ctassert_test_greater_than_or_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertGreaterThanOrEqual(test, 3 + 4, 7, "")
    CTAssertGreaterThanOrEqual(test, 3 + 5, 7, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertGreaterThanOrEqual(test, 3 + 3, 7, "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_test_less_than() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertLessThan(test, 3 + 3, 7, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertLessThan(test, 3 + 4, 7, "")
    CTAssertLessThan(test, 3 + 5, 7, "")
    
    assert(testInternal->failures == 2);
    
    ctfree(test);
}

void ctassert_test_less_than_or_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertLessThanOrEqual(test, 3 + 3, 7, "")
    CTAssertLessThanOrEqual(test, 3 + 4, 7, "")
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertLessThanOrEqual(test, 3 + 5, 7, "")
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
}

void ctassert_tests() {
    ctassert_test_fail();
    ctassert_test_equal();
    ctassert_test_not_equal();
    ctassert_test_true();
    ctassert_test_false();
    ctassert_test_null();
    ctassert_test_not_null();
    ctassert_test_greater_than();
    ctassert_test_greater_than_or_equal();
    ctassert_test_less_than();
    ctassert_test_less_than_or_equal();
}
