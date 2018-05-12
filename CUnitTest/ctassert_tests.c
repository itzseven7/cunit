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

void ctassert_test_string_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    char str1[15] = "Hello there!";
    char *str2 = malloc((sizeof(str1) * sizeof(char)) + 1);
    strcpy(str2, str1);
    char str3[15] = "Hello there! ";
    
    CTAssertStringEqual(test, str1, str2)
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertStringEqual(test, str1, str3)
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
    
    free(str2);
}

void ctassert_test_string_not_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    char str1[15] = "Hello there!";
    char *str2 = malloc((sizeof(str1) * sizeof(char)) + 1);
    strcpy(str2, str1);
    char str3[15] = "Hello there! ";
    
    CTAssertStringNotEqual(test, str1, str3)
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertStringNotEqual(test, str1, str2)
    
    assert(testInternal->failures == 1);
    
    ctfree(test);
    
    free(str2);
}

void ctassert_test_decimal_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    float a = 1.15f, b = 1.15f, c = 1.151f;
    double d = 0.12345678987654321, e = 0.12345678987654321, f = 0.1234567898765432;
    
    CTAssertDecimalEqual(test, a, b, 0.001f)
    CTAssertDecimalEqual(test, d, e, 0.00000000000000001)
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertDecimalEqual(test, a, c, 0.001f)
    CTAssertDecimalEqual(test, d, f, 0.00000000000000001)
    
    assert(testInternal->failures == 2);
    
    ctfree(test);
}

void ctassert_test_decimal_not_equal() {
    ctest_t *test = ctest("", NULL, NULL);
    
    float a = 1.15f, b = 1.15f, c = 1.151f;
    double d = 0.12345678987654321, e = 0.12345678987654321, f = 0.1234567898765432;
    
    CTAssertDecimalNotEqual(test, a, c, 0.001f)
    CTAssertDecimalNotEqual(test, d, f, 0.00000000000000001)
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertDecimalNotEqual(test, a, b, 0.001f)
    CTAssertDecimalNotEqual(test, d, e, 0.00000000000000001)
    
    assert(testInternal->failures == 2);
    
    ctfree(test);
}

struct ctest_acmp_ex_t {
    int a;
    int b;
};

int intComparison(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

int structComparison(const void *a, const void *b) {
    return (((struct ctest_acmp_ex_t *)a)->a - ((struct ctest_acmp_ex_t *)b)->a) + (((struct ctest_acmp_ex_t *)a)->b - ((struct ctest_acmp_ex_t *)b)->b);
}

int stringComparison(const void *a, const void *b) {
    return strcmp(a, b);
}

void ctassert_test_array_equal() {
    int *arr1 = calloc(5, sizeof(int)), *arr2 = calloc(5, sizeof(int));
    arr1[0] = 0;
    arr2[0] = arr1[1] = 1;
    arr2[1] = arr1[2] = 2;
    arr2[2] = arr1[3] = 3;
    arr2[3] = arr1[4] = 4;
    arr2[4] = 5;
    
    struct ctest_acmp_ex_t *arr3 = malloc(sizeof(struct ctest_acmp_ex_t) * 5), *arr4 = malloc(sizeof(struct ctest_acmp_ex_t) * 5);
    arr3[0] = (struct ctest_acmp_ex_t){ .a = 3, .b = 4};
    arr4[0] = arr3[1] = (struct ctest_acmp_ex_t){ .a = 2, .b = 4};
    arr4[1] = arr3[2] = (struct ctest_acmp_ex_t){ .a = 3, .b = 8};
    arr4[2] = arr3[3] = (struct ctest_acmp_ex_t){ .a = 7, .b = 4};
    arr4[3] = arr3[4] = (struct ctest_acmp_ex_t){ .a = 3, .b = 0};
    arr4[4] = (struct ctest_acmp_ex_t){ .a = 3, .b = 0};
    
    const char *arr5[] = {"hello", "how are you", "goodbye"}, *arr6[] = {"hello", "how are you?", "goodbye"};
    
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertArrayEqual(test, arr1, arr1, 5, sizeof(int), intComparison)
    CTAssertArrayEqual(test, arr3, arr3, 5, sizeof(struct ctest_acmp_ex_t), structComparison)
    CTAssertArrayEqual(test, arr5, arr5, 3, sizeof(char *), stringComparison)
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertArrayEqual(test, arr1, arr2, 5, sizeof(int), intComparison)
    CTAssertArrayEqual(test, arr3, arr4, 5, sizeof(struct ctest_acmp_ex_t), structComparison)
    CTAssertArrayEqual(test, arr5, arr6, 5, sizeof(char *), stringComparison)
    
    assert(testInternal->failures == 3);
    
    ctfree(test);
    
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
}

void ctassert_test_array_not_equal() {
    int *arr1 = calloc(5, sizeof(int)), *arr2 = calloc(5, sizeof(int));
    arr1[0] = 0;
    arr2[0] = arr1[1] = 1;
    arr2[1] = arr1[2] = 2;
    arr2[2] = arr1[3] = 3;
    arr2[3] = arr1[4] = 4;
    arr2[4] = 5;
    
    struct ctest_acmp_ex_t *arr3 = malloc(sizeof(struct ctest_acmp_ex_t) * 5), *arr4 = malloc(sizeof(struct ctest_acmp_ex_t) * 5);
    arr3[0] = (struct ctest_acmp_ex_t){ .a = 3, .b = 4};
    arr4[0] = arr3[1] = (struct ctest_acmp_ex_t){ .a = 2, .b = 4};
    arr4[1] = arr3[2] = (struct ctest_acmp_ex_t){ .a = 3, .b = 8};
    arr4[2] = arr3[3] = (struct ctest_acmp_ex_t){ .a = 7, .b = 4};
    arr4[3] = arr3[4] = (struct ctest_acmp_ex_t){ .a = 3, .b = 0};
    arr4[4] = (struct ctest_acmp_ex_t){ .a = 3, .b = 0};
    
    const char *arr5[] = {"hello", "how are you", "goodbye"}, *arr6[] = {"hello", "how are you?", "goodbye"};
    
    ctest_t *test = ctest("", NULL, NULL);
    
    CTAssertArrayNotEqual(test, arr1, arr2, 5, sizeof(int), intComparison)
    CTAssertArrayNotEqual(test, arr3, arr4, 5, sizeof(struct ctest_acmp_ex_t), structComparison)
    CTAssertArrayNotEqual(test, arr5, arr6, 5, sizeof(char *), stringComparison)
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    assert(testInternal->failures == 0);
    
    CTAssertArrayNotEqual(test, arr1, arr1, 5, sizeof(int), intComparison)
    CTAssertArrayNotEqual(test, arr3, arr3, 5, sizeof(struct ctest_acmp_ex_t), structComparison)
    CTAssertArrayNotEqual(test, arr5, arr5, 3, sizeof(char *), stringComparison)
    
    assert(testInternal->failures == 3);
    
    ctfree(test);
    
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
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
    ctassert_test_string_equal();
    ctassert_test_string_not_equal();
    ctassert_test_decimal_equal();
    ctassert_test_decimal_not_equal();
    ctassert_test_array_equal();
    ctassert_test_array_not_equal();
}
