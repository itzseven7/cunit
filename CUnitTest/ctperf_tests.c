//
//  ctperf_tests.c
//  CUnitTest
//
//  Created by itzseven on 18/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctperf_tests.h"
#include "ctperf.h"
#include "ctest.h"
#include <stdlib.h>
#include <assert.h>

void ctperf_test_creation() {
    ctperf_t *perf = ctperf(ctest("Test perf", NULL, NULL), 20);
    
    assert(perf->time == 20);
    
    ctpfree(perf);
}

void ctperf_tests(void) {
    ctperf_test_creation();
}
