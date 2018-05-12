//
//  ctperf.c
//  cunit
//
//  Created by itzseven on 18/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctperf.h"
#include <stdlib.h>

ctperf_t *ctperf(ctest_t *test, double time) {
    ctperf_t *perf = malloc(sizeof(ctperf_t));
    perf->test = test;
    perf->time = time;
    
    return perf;
}

void ctpfree(ctperf_t *tperf) {
    ctfree(tperf->test);
    free(tperf);
}
