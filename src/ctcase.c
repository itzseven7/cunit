//
//  ctcase.c
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctcase.h"
#include "ctperf.h"
#include "_ctcase.h"
#include "_ctest.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#pragma mark - Test list

ctestlist_t *ctestlist(ctest_t *test) {
    ctestlist_t *list = malloc(sizeof(ctestlist_t));
    list->test = test;
    list->next = NULL;
    return list;
}

#pragma mark - Test performance list

ctperflist_t *ctperflist(ctperf_t *testPerf) {
    ctperflist_t *list = malloc(sizeof(ctperflist_t));
    list->tperf = testPerf;
    list->next = NULL;
    return list;
}

ctcase_int_t *ctcase_int() {
    ctcase_int_t *tcase_int = malloc(sizeof(ctcase_int_t));
    tcase_int->tests = NULL;
    tcase_int->testCount = 0;
    tcase_int->perfTests = NULL;
    tcase_int->perfTestCount = 0;
    tcase_int->passed = 0;
    tcase_int->failed = 0;
    
    return tcase_int;
}

ctcase_t *ctcase(const char *name) {
    if (name == NULL) {
        return NULL;
    }
    
    ctcase_t *tcase = (ctcase_t *)malloc(sizeof(ctcase_t));
    tcase->name = name;
    tcase->_internal = ctcase_int();
    
    return tcase;
}

void ctctestadd(ctcase_t *tcase, ctest_t *ctest) {
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    if (caseInternal->tests == NULL) {
        caseInternal->tests = ctestlist(ctest);
    } else {
        ctestlist_t *tcurrentList = caseInternal->tests;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = ctestlist(ctest);
    }
    
    caseInternal->testCount++;
}

void ctcperfadd(ctcase_t *tcase, ctest_t *test, double time) {
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    ctperf_t * perf = ctperf(test, time);
    
    if (caseInternal->perfTests == NULL) {
        caseInternal->perfTests = ctperflist(perf);
    } else {
        ctperflist_t *tcurrentList = caseInternal->perfTests;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = ctperflist(perf);
    }
    
    caseInternal->perfTestCount++;
}

void _ctcruntest(ctcase_t *tcase, ctest_t *test) {
    if (test->setup != NULL) {
        test->setup(test->arg);
    }
    
    test->inv(test, test->arg);
    
    if (test->tdown != NULL) {
        test->tdown(test->arg);
    }
    
    ctest_int_t *testInternal = (ctest_int_t *)test->_internal;
    
    if ((testInternal->failures == 0) && (testInternal->unfulfilledExpectations == 0)) {
        printf("--- Test %s succeeded\n", test->name);
    } else {
        printf("--- Test %s failed (%d failure(s), %d unfulfilled expectation(s))\n", test->name, testInternal->failures, testInternal->unfulfilledExpectations);
    }
    
    ((ctcase_int_t *)tcase->_internal)->passed += (testInternal->failures == 0) && (testInternal->unfulfilledExpectations == 0);
    ((ctcase_int_t *)tcase->_internal)->failed += (testInternal->failures > 0) || (testInternal->unfulfilledExpectations > 0);
}

void _ctcrunperf(ctcase_t *tcase, ctperf_t *perf) {
    ctest_t *test = perf->test;
    
    if (test->setup != NULL) {
        test->setup(test->arg);
    }
    
    // Time precision : us
    
    long start, end;
    struct timeval timecheck;
    
    gettimeofday(&timecheck, NULL);
    start = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;
    
    test->inv(test, test->arg);
    
    gettimeofday(&timecheck, NULL);
    end = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;
    
    if (test->tdown != NULL) {
        test->tdown(test->arg);
    }
    
    long time = end - start;
    long expected = (long)(perf->time * 1000000);
    
    if (time <= expected) {
        printf("--- Test perf %s succeeded (took %0.2f seconds, expected %0.2f)\n", perf->test->name, (float)((float)time / 1000000), perf->time);
    } else {
        printf("--- Test perf %s failed (took %0.2f seconds, expected %0.2f)\n", perf->test->name, (float)((float)time / 1000000), perf->time);
    }
    
    ((ctcase_int_t *)tcase->_internal)->passed += (time <= expected);
    ((ctcase_int_t *)tcase->_internal)->failed += (time > expected);
}

void _ctcrun(ctcase_t *tcase) {
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    ctestlist_t *testList = caseInternal->tests;
    
    while (testList != NULL) {
        printf("-- Invoking %s test\n", testList->test->name);
        _ctcruntest(tcase, testList->test);
        printf("-- Finished %s test\n\n", testList->test->name);
        testList = testList->next;
    }
    
    ctperflist_t *perfList = caseInternal->perfTests;
    
    while (perfList != NULL) {
        printf("-- Invoking %s performance test\n", perfList->tperf->test->name);
        _ctcrunperf(tcase, perfList->tperf);
        printf("-- Finished %s test\n\n", perfList->tperf->test->name);
        perfList = perfList->next;
    }
}

void ctcfree(ctcase_t *tcase) {
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    ctestlist_t *testList = caseInternal->tests;
    
    while (testList != NULL) {
        ctfree(testList->test);
        ctestlist_t *nextTest = testList->next;
        free(testList);
        testList = nextTest;
    }
    
    ctperflist_t *perfList = caseInternal->perfTests;
    
    while (perfList != NULL) {
        ctpfree(perfList->tperf);
        ctperflist_t *nextPerf = perfList->next;
        free(perfList);
        perfList = nextPerf;
    }
    
    free(caseInternal);
    free(tcase);
}
