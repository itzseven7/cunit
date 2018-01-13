//
//  ctcase.c
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctcase.h"
#include "_ctcase.h"
#include "_ctest.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#pragma mark - Test list

ctestlist_t *ctestlist(ctest_t *test) {
    ctestlist_t *list = malloc(sizeof(ctestlist_t));
    list->test = test;
    list->next = NULL;
    return list;
}

#pragma mark - Test performance list

ctperf_t *ctperf(ctest_t *test, double time) {
    ctperf_t *perf = malloc(sizeof(ctperf_t));
    perf->test = test;
    perf->time = time;
    
    return perf;
}

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

void ctestadd(ctcase_t *tcase, ctest_t *ctest) {
    ctcase_int_t *case_int = (ctcase_int_t *)tcase->_internal;
    
    if (case_int->tests == NULL) {
        case_int->tests = ctestlist(ctest);
    } else {
        ctestlist_t *tcurrentList = case_int->tests;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = ctestlist(ctest);
    }
    
    case_int->testCount++;
}

void ctestperfadd(ctcase_t *tcase, ctest_t *test, double time) {
    ctcase_int_t *case_int = (ctcase_int_t *)tcase->_internal;
    ctperf_t * perf = ctperf(test, time);
    
    if (case_int->perfTests == NULL) {
        case_int->perfTests = ctperflist(perf);
    } else {
        ctperflist_t *tcurrentList = case_int->perfTests;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = ctperflist(perf);
    }
    
    case_int->perfTestCount++;
}

void _tcruntest(ctcase_t *tcase, ctest_t *test) {
    if (test->setup != NULL) {
        test->setup(test->arg);
    }
    
    test->inv(test, test->arg);
    
    if (test->tdown != NULL) {
        test->tdown(test->arg);
    }
    
    if (((ctest_int_t *)test->_internal)->failures == 0) {
        printf("Test %s succeeded\n", test->name);
    } else {
        printf("Test %s failed (%d failures)\n", test->name, ((ctest_int_t *)test->_internal)->failures);
    }
    
    ((ctcase_int_t *)tcase->_internal)->passed += ((ctest_int_t *)test->_internal)->failures == 0;
    ((ctcase_int_t *)tcase->_internal)->failed += ((ctest_int_t *)test->_internal)->failures > 0;
}

void _tcrunperf(ctcase_t *tcase, ctperf_t *perf) {
    ctest_t *test = perf->test;
    
    if (test->setup != NULL) {
        test->setup(test->arg);
    }
    
    clock_t begin = clock();
    test->inv(test, test->arg);
    clock_t end = clock();
    
    if (test->tdown != NULL) {
        test->tdown(test->arg);
    }
    
    clock_t time = end - begin;
    clock_t expected = (clock_t)(perf->time * CLOCKS_PER_SEC);
    
    if (time <= expected) {
        printf("Test perf %s succeeded (took %lf seconds, expected %lf)\n", perf->test->name, (double)((double)time / CLOCKS_PER_SEC), perf->time);
    } else {
        printf("Test perf %s failed (took %lf seconds, expected %lf)\n", perf->test->name, (double)((double)time / CLOCKS_PER_SEC), perf->time);
    }
    
    ((ctcase_int_t *)tcase->_internal)->passed += (time <= expected);
    ((ctcase_int_t *)tcase->_internal)->failed += (time > expected);
}

void _tcrun(ctcase_t *tcase) {
    ctcase_int_t *case_int = (ctcase_int_t *)tcase->_internal;
    
    ctestlist_t *testList = case_int->tests;
    
    while (testList != NULL) {
        printf("Invoking %s test\n", testList->test->name);
        _tcruntest(tcase, testList->test);
        printf("Finished %s test\n", testList->test->name);
        testList = testList->next;
    }
    
    ctperflist_t *perfList = case_int->perfTests;
    
    while (perfList != NULL) {
        printf("Invoking %s performance test\n", perfList->tperf->test->name);
        _tcrunperf(tcase, perfList->tperf);
        printf("Finished %s test\n", perfList->tperf->test->name);
        perfList = perfList->next;
    }
}

void fctcase(ctcase_t *tcase) {
    ctcase_int_t *case_int = (ctcase_int_t *)tcase->_internal;
    
    ctestlist_t *testList = case_int->tests;
    
    while (testList != NULL) {
        fctest(testList->test);
        testList = testList->next;
    }
    
    ctperflist_t *perfList = case_int->perfTests;
    
    while (perfList != NULL) {
        fctest(perfList->tperf->test);
        free(perfList->tperf);
        perfList = perfList->next;
    }
    
    free(case_int);
    free(tcase);
}
