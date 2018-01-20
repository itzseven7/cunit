//
//  ctsuite.c
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctsuite.h"
#include "_ctsuite.h"
#include "_ctcase.h"
#include <stdio.h>
#include <stdlib.h>

ctcaselist_t *ctcaselist(ctcase_t *tcase) {
    ctcaselist_t *list = malloc(sizeof(ctcaselist_t));
    list->tcase = tcase;
    list->next = NULL;
    return list;
}

ctsuite_int_t *ctsuite_int() {
    ctsuite_int_t *tsuite_int = malloc(sizeof(ctsuite_int_t));
    tsuite_int->tcases = NULL;
    tsuite_int->tcaseCount = 0;
    return tsuite_int;
}

ctsuite_t *ctsuite(const char *name) {
    if (name == NULL) {
        return NULL;
    }
    
    ctsuite_t *tsuite = (ctsuite_t *)malloc(sizeof(ctsuite_t));
    tsuite->name = name;
    tsuite->count = 0;
    tsuite->passed = 0;
    tsuite->failed = 0;
    tsuite->_internal = ctsuite_int();
    
    return tsuite;
}

void ctscaseadd(ctsuite_t *tsuite, ctcase_t *tcase) {
    ctsuite_int_t *suiteInternal = (ctsuite_int_t *)tsuite->_internal;
    ctcase_int_t *caseInternal = (ctcase_int_t *)tcase->_internal;
    
    if (suiteInternal->tcases == NULL) {
        suiteInternal->tcases = ctcaselist(tcase);
    } else {
        ctcaselist_t *tcurrentList = suiteInternal->tcases;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = ctcaselist(tcase);
    }
    
    suiteInternal->tcaseCount++;
    tsuite->count += (caseInternal->testCount + caseInternal->perfTestCount);
}

void ctsrun(ctsuite_t *tsuite) {
    printf("Starting %s test suite\n", tsuite->name);
    
    ctsuite_int_t *suiteInternal = (ctsuite_int_t *)tsuite->_internal;
    ctcaselist_t *caseList = suiteInternal->tcases;
    
    while (caseList != NULL) {
        printf("Starting %s test case\n", caseList->tcase->name);
        
        ctcase_int_t *caseInternal = (ctcase_int_t *)caseList->tcase->_internal;
        
        _ctcrun(caseList->tcase);
        
        printf("Finished %s test case\n", caseList->tcase->name);
        
        tsuite->passed += caseInternal->passed;
        tsuite->failed += caseInternal->failed;
        
        caseList = caseList->next;
    }
    
    printf("Finished %s test suite (%d passed, %d failed on %d tests)\n", tsuite->name, tsuite->passed, tsuite->failed, tsuite->count);
    puts("\n-----------------------------------------------------------------------------------------------\n");
}

void ctsfree(ctsuite_t *tsuite) {
    ctsuite_int_t *suiteInternal = (ctsuite_int_t *)tsuite->_internal;
    
    ctcaselist_t *caseList = suiteInternal->tcases;
    
    while (caseList != NULL) {
        ctcfree(caseList->tcase);
        caseList = caseList->next;
    }
    
    free(suiteInternal);
    free(tsuite);
}
