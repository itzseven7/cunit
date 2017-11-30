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

tsuite_t *tsuitealloc(const char *name) {
    tsuite_t *tsuite = (tsuite_t *)malloc(sizeof(tsuite_t));
    tsuite->name = name;
    tsuite->count = 0;
    tsuite->passed = 0;
    tsuite->failed = 0;
    tsuite->tcaselist = NULL;
    tsuite->tperflist = NULL;
    
    return tsuite;
}

#warning rename to tsaddcase
void tsuiteadd(tcase_t *tcase, tsuite_t *tsuite) {
    tcaselist_t *tcaselist = (tcaselist_t *)malloc(sizeof(tcaselist_t));
    tcaselist->tcase = tcase;
    tcaselist->next = NULL;
    
    if (tsuite->tcaselist == NULL) {
        tsuite->tcaselist = tcaselist;
    } else {
        tcaselist_t *tcurrentList = tsuite->tcaselist;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = tcaselist;
    }
    
    tsuite->count += 1;
}

void tsaddperf(tperf_t *tperf, tsuite_t *tsuite) {
    tperflist_t *tperflist = (tperflist_t *)malloc(sizeof(tperflist_t));
    tperflist->tperf = tperf;
    tperflist->next = NULL;
    
    if (tsuite->tperflist == NULL) {
        tsuite->tperflist = tperflist;
    } else {
        tperflist_t *tcurrentList = tsuite->tperflist;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = tperflist;
    }
    
    tsuite->count += 1;
}

void _tsuiteruncases(tsuite_t *tsuite) {
    tcaselist_t *tcurrentList = tsuite->tcaselist;
    
    while (tcurrentList != NULL) {
        
        printf("Starting %s test case\n", tcurrentList->tcase->name);
        
        int result = tcurrentList->tcase->fct_ptr();
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

void _tsuiterunperf(tsuite_t *tsuite) {
    tperflist_t *tcurrentList = tsuite->tperflist;
    
    while (tcurrentList != NULL) {
        
        printf("Starting %s test perf\n", tcurrentList->tperf->name);
        
        clock_t begin = clock();
        tcurrentList->tperf->fct_ptr();
        clock_t end = clock();
        
        double time = (double)(end - begin) / CLOCKS_PER_SEC;
        double comp = time - tcurrentList->tperf->exptime;
        
        tsuite->failed += comp > 0.f;
        tsuite->passed += comp <= 0.f;
        
        if (comp <= 0.f) {
            printf("Test perf %s succeeded (took %lf seconds, expected %lf)\n", tcurrentList->tperf->name, time, tcurrentList->tperf->exptime);
        } else {
            printf("Test perf %s failed (took %lf seconds, expected %lf)\n", tcurrentList->tperf->name, time, tcurrentList->tperf->exptime);
        }
        
        tcurrentList = tcurrentList->next;
    }
}

void tsuiterun(tsuite_t *tsuite) {
    printf("Starting %s test suite\n", tsuite->name);
    
    _tsuiteruncases(tsuite);
    _tsuiterunperf(tsuite);
    
    printf("Finished %s test suite (%d passed, %d failed on %d tests)\n", tsuite->name, tsuite->passed, tsuite->failed, tsuite->count);
    puts("\n-----------------------------------------------------------------------------------------------\n");
}
