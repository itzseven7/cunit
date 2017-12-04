//
//  main.m
//  CUnitTest
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "cunit.h"

ctcase_return_t testFail() {
    puts("testFail execution\n");
    cfail("This library should be more comprehensive :(\n")
    return CTPassed;
}

ctcase_return_t testEquality() {
    puts("testEquality execution\n");
    int a = 5, b = 9;
    casserteq(a, b, "testEquality failed: %d and %d are not equal\n", a, b)
    return CTPassed;
}

ctcase_return_t testNonEquality() {
    puts("testNonEquality execution\n");
    int a = 5, b = 9;
    cassertneq(a, b, "testNonEquality failed: %d and %d are equal\n", a, b)
    return CTFailed;
}

ctcase_return_t testTrue() {
    puts("testTrue execution\n");
    int a = 5, b = 9, c = 14;
    cassertt((a + b) == c)
    return CTPassed;
}

ctcase_return_t testFalse() {
    puts("testFalse execution\n");
    int a = 5, b = 9, c = 14;
    cassertf((a + b) == c, "testFalse failed: (%d + %d) is equal to %d\n", a, b, c)
    return CTFailed;
}

ctcase_return_t testNull() {
    puts("testNull execution\n");
    const char *string = NULL;
    cassertnull(string, "testNull failed: string is not NULL\n")
    return CTPassed;
}

ctcase_return_t testNotNull() {
    puts("testNotNull execution\n");
    const char *string = (const char *)malloc(5 * sizeof(char));
    cassertnnull(string, "testNotNull failed: string is NULL\n")
    return CTPassed;
}

ctcase_return_t testGreaterThan() {
    puts("testGreaterThan execution\n");
    int a = 2, b = 10;
    cassertgt(a, b, "testGreaterThan failed: %d is not greater than %d\n", a, b)
    return CTFailed;
}

ctcase_return_t testGreaterOrEqual() {
    puts("testGreaterOrEqual execution\n");
    int a = 9, b = 10;
    cassertgteq(a, b, "testGreaterOrEqual failed: %d is not greater or equal to %d\n", a, b)
    return CTPassed;
}

ctcase_return_t testLessThan() {
    puts("testLessThan execution\n");
    int a = 2, b = 10;
    cassertgt(a, b, "testLessThan failed: %d is not less than %d\n", a, b)
    return CTPassed;
}

ctcase_return_t testLessOrEqual() {
    puts("testLessOrEqual execution\n");
    int a = 9, b = 10;
    cassertgteq(a, b, "testLessOrEqual failed: %d is not less or equal to %d\n", a, b)
    return CTFailed;
}

ctperf_return_t testPerformanceNotTooLong() {
    int i = 0;
    
    FILE* debug = fopen("/dev/null", "w");
    
    for (i = 0; i < 10000; i++) {
        fprintf(debug, "%d.", i);
    }
    
    puts("testPerformanceNotTooLong finished\n");
}

ctcase_return_t testWithOptionalFunctions() {
    puts("testWithOptionalFunctions execution\n");
    return CTPassed;
}

ctopt_return_t testCaseSetup() {
    puts("testCaseSetup execution\n");
}

ctopt_return_t testCaseTeardown() {
    puts("testCaseTeardown execution\n");
}

ctopt_return_t testPerformanceSetup() {
    puts("testPerformanceSetup execution\n");
}

ctopt_return_t testPerformanceTeardown() {
    puts("testPerformanceTeardown execution\n");
}

ctperf_return_t testPerformanceTooLong() {
    int i = 0;
    
    FILE* debug = fopen("/dev/null", "w");
    
    for (i = 0; i < 10000; i++) {
        fprintf(debug, "%d.", i);
    }
    
    puts("testPerformanceTooLong finished\n");
}

int main(int argc, const char * argv[]) {
    
    ctsuite_t *suite = ctsuite("Test assertions1");
    
    ctcase_t *tcase0 = ctcase("testFail", testFail);
    ctcase_t *tcase1 = ctcase("testEquality", testEquality);
    ctcase_t *tcase2 = ctcase("testNonEquality", testNonEquality);
    ctcase_t *tcase3 = ctcase("testTrue", testTrue);
    ctcase_t *tcase4 = ctcase("testFalse", testFalse);
    ctcase_t *tcase5 = ctcase("testNull", testNull);
    ctcase_t *tcase6 = ctcase("testNotNull", testNotNull);
    ctcase_t *tcase7 = ctcase("testGreaterThan", testGreaterThan);
    ctcase_t *tcase8 = ctcase("testGreaterOrEqual", testGreaterOrEqual);
    ctcase_t *tcase9 = ctcase("testLessThan", testLessThan);
    ctcase_t *tcase10 = ctcase("testLessOrEqual", testLessOrEqual);
    
    ctcase_t *tcase11 = ctcase("testWithOptionalFunctions", testWithOptionalFunctions);
    tcase11->setup = testCaseSetup;
    tcase11->tdown = testCaseTeardown;
    
    ctsaddtc(tcase0, suite);
    ctsaddtc(tcase1, suite);
    ctsaddtc(tcase2, suite);
    ctsaddtc(tcase3, suite);
    ctsaddtc(tcase4, suite);
    ctsaddtc(tcase5, suite);
    
    ctsuite_t *suite2 = ctsuite("Test assertions2");
    
    ctperf_t *tperf1 = ctperf("testPerformanceNotTooLong", testPerformanceNotTooLong, 0.005);
    
    ctperf_t *tperf2 = ctperf("testPerformanceTooLong", testPerformanceTooLong, 0.0005);
    tperf2->setup = testPerformanceSetup;
    tperf2->tdown = testPerformanceTeardown;
    
    ctsaddtc(tcase6, suite2);
    ctsaddtc(tcase7, suite2);
    ctsaddtc(tcase8, suite2);
    ctsaddtc(tcase9, suite2);
    ctsaddtc(tcase10, suite2);
    ctsaddtc(tcase11, suite2);
    
    ctsaddtp(tperf1, suite2);
    ctsaddtp(tperf2, suite2);
  
    ctsrun(suite);
    ctsrun(suite2);
    
    return 0;
}
