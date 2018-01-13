//
//  ctest.c
//  cunit
//
//  Created by itzseven on 13/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctest.h"
#include "_ctest.h"
#include <stdlib.h>

ctest_int_t *ctest_int() {
    ctest_int_t *test_int = malloc(sizeof(ctest_int_t));
    test_int->failures = 0;
    return test_int;
}

ctest_t *ctest(const char *name, ctinv_ptr_t inv, void *arg) {
    ctest_t *test = malloc(sizeof(ctest_t));
    test->name = name;
    test->inv = inv;
    test->arg = arg;
    test->setup = NULL;
    test->tdown = NULL;
    test->_internal = ctest_int();
    
    return test;
}

void fctest(ctest_t *test) {
    free(test->_internal);
    free(test);
}
