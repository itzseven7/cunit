//
//  ctperf.c
//  cunit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctperf.h"
#include <stdlib.h>

tperf_t *tperf(const char *name, tperf_fct_ptr ptr, double expectedTime) {
    tperf_t *tperf = (tperf_t *)malloc(sizeof(tperf_t));
    tperf->name = name;
    tperf->fct_ptr = ptr;
    tperf->exptime = expectedTime;
    
    return tperf;
}
