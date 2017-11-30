//
//  ctsuite.c
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

ctsuite_t *ctsuite(const char *name) {
    ctsuite_t *tsuite = (ctsuite_t *)malloc(sizeof(ctsuite_t));
    tsuite->name = name;
    tsuite->count = 0;
    tsuite->passed = 0;
    tsuite->failed = 0;
    tsuite->tcaselist = NULL;
    tsuite->tperflist = NULL;
    
    return tsuite;
}

void ctsaddcase(ctcase_t *tcase, ctsuite_t *tsuite) {
    ctcaselist_t *tcaselist = (ctcaselist_t *)malloc(sizeof(ctcaselist_t));
    tcaselist->tcase = tcase;
    tcaselist->next = NULL;
    
    if (tsuite->tcaselist == NULL) {
        tsuite->tcaselist = tcaselist;
    } else {
        ctcaselist_t *tcurrentList = tsuite->tcaselist;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = tcaselist;
    }
    
    tsuite->count += 1;
}

void ctsaddperf(ctperf_t *tperf, ctsuite_t *tsuite) {
    ctperflist_t *tperflist = (ctperflist_t *)malloc(sizeof(ctperflist_t));
    tperflist->tperf = tperf;
    tperflist->next = NULL;
    
    if (tsuite->tperflist == NULL) {
        tsuite->tperflist = tperflist;
    } else {
        ctperflist_t *tcurrentList = tsuite->tperflist;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = tperflist;
    }
    
    tsuite->count += 1;
}

void _tsruncases(ctsuite_t *tsuite) {
    ctcaselist_t *tcurrentList = tsuite->tcaselist;
    
    while (tcurrentList != NULL) {
        
        printf("Starting %s test case\n", tcurrentList->tcase->name);
        
        if (tcurrentList->tcase->setup != NULL) {
            tcurrentList->tcase->setup();
        }
        
        int result = tcurrentList->tcase->inv();
        
        if (tcurrentList->tcase->teardown != NULL) {
            tcurrentList->tcase->teardown();
        }
        
        tsuite->failed += result != 0;
        tsuite->passed += result == 0;
        
        if (!result) {
            printf("Test case %s succeeded\n", tcurrentList->tcase->name);
        } else {
            printf("Test case %s failed\n", tcurrentList->tcase->name);
        }
        
        tcurrentList = tcurrentList->next;
    }
}

void _tsrunperf(ctsuite_t *tsuite) {
    ctperflist_t *tcurrentList = tsuite->tperflist;
    
    while (tcurrentList != NULL) {
        
        printf("Starting %s test perf\n", tcurrentList->tperf->name);
        
        clock_t begin = clock();
        tcurrentList->tperf->inv();
        clock_t end = clock();
        
        clock_t time = end - begin;
        clock_t expected = (clock_t)(tcurrentList->tperf->time * CLOCKS_PER_SEC);
        
        tsuite->failed += time > expected;
        tsuite->passed += time <= expected;
        
        if (time <= expected) {
            printf("Test perf %s succeeded (took %lf seconds, expected %lf)\n", tcurrentList->tperf->name, (double)((double)time / CLOCKS_PER_SEC), tcurrentList->tperf->time);
        } else {
            printf("Test perf %s failed (took %lf seconds, expected %lf)\n", tcurrentList->tperf->name, (double)((double)time / CLOCKS_PER_SEC), tcurrentList->tperf->time);
        }
        
        tcurrentList = tcurrentList->next;
    }
}

void ctsrun(ctsuite_t *tsuite) {
    printf("Starting %s test suite\n", tsuite->name);
    
    _tsruncases(tsuite);
    _tsrunperf(tsuite);
    
    printf("Finished %s test suite (%d passed, %d failed on %d tests)\n", tsuite->name, tsuite->passed, tsuite->failed, tsuite->count);
    puts("\n-----------------------------------------------------------------------------------------------\n");
}
