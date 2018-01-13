//
//  ctsuite.c
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctsuite.h"
#include "_ctcase.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ctcaselist_t {
    ctcase_t *tcase;
    struct ctcaselist_t *next;
}ctcaselist_t;

ctcaselist_t *ctcaselist(ctcase_t *tcase) {
    ctcaselist_t *list = malloc(sizeof(ctcaselist_t));
    list->tcase = tcase;
    list->next = NULL;
    return list;
}

typedef struct ctsuite_int_t {
    ctcaselist_t *tcases;
    unsigned int tcaseCount;
}ctsuite_int_t;

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

void ctsaddtc(ctsuite_t *tsuite, ctcase_t *tcase) {
    ctsuite_int_t *suite_int = (ctsuite_int_t *)tsuite->_internal;
    
    if (suite_int->tcases == NULL) {
        suite_int->tcases = ctcaselist(tcase);
    } else {
        ctcaselist_t *tcurrentList = suite_int->tcases;
        
        while (tcurrentList->next != NULL) {
            tcurrentList = tcurrentList->next;
        }
        
        tcurrentList->next = ctcaselist(tcase);
    }
    
    suite_int->tcaseCount++;
    tsuite->count += (((ctcase_int_t *)tcase->_internal)->testListCount + ((ctcase_int_t *)tcase->_internal)->testPerfListCount);
}

void ctsrun(ctsuite_t *tsuite) {
    printf("Starting %s test suite\n", tsuite->name);
    
    ctsuite_int_t *suite_int = (ctsuite_int_t *)tsuite->_internal;
    
    ctcaselist_t *caseList = suite_int->tcases;
    
    while (caseList != NULL) {
        _tcrun(caseList->tcase);
        
        tsuite->passed += ((ctcase_int_t *)caseList->tcase->_internal)->passed;
        tsuite->failed += ((ctcase_int_t *)caseList->tcase->_internal)->failed;
        
        caseList = caseList->next;
    }
    
    printf("Finished %s test suite (%d passed, %d failed on %d tests)\n", tsuite->name, tsuite->passed, tsuite->failed, tsuite->count);
    puts("\n-----------------------------------------------------------------------------------------------\n");
}

void fctsuite(ctsuite_t *tsuite) {
    ctsuite_int_t *suite_int = (ctsuite_int_t *)tsuite->_internal;
    
    ctcaselist_t *caseList = suite_int->tcases;
    
    while (caseList != NULL) {
        fctcase(caseList->tcase);
        caseList = caseList->next;
    }
    
    free(suite_int);
    free(tsuite);
}
