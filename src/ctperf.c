//
//  ctperf.c
//  cunit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctperf.h"
#include <stdlib.h>

ctperf_t *ctperf(const char *name, ctperf_inv_ptr_t inv, double expectedTime) {
    ctperf_t *tperf = (ctperf_t *)malloc(sizeof(ctperf_t));
    tperf->name = name;
    tperf->inv = inv;
    tperf->time = expectedTime;
    
    return tperf;
}
