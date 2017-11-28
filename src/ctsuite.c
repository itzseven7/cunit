//
//  ctsuite.c
//  CUnit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctsuite.h"
#include <stdio.h>
#include <stdlib.h>

tsuite_t *tsuitealloc(const char *name) {
    tsuite_t *tsuite = (tsuite_t *)malloc(sizeof(tsuite_t));
    tsuite->name = name;
    tsuite->count = 0;
    tsuite->passed = 0;
    tsuite->failed = 0;
    tsuite->tcaselist = NULL;
    
    return tsuite;
}

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

void tsuiterun(tsuite_t *tsuite) {
    printf("Starting %s test suite\n", tsuite->name);
    
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
    
    printf("Finished %s test suite (%d passed, %d failed on %d tests)\n", tsuite->name, tsuite->passed, tsuite->failed, tsuite->count);
    puts("\n-----------------------------------------------------------------------------------------------\n");
}
