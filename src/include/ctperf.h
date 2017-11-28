//
//  ctperf.h
//  CUnit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctperf_h
#define ctperf_h

#include <stdio.h>
#include <time.h>
#include "ctcase.h"

typedef struct tperf_t {
    const char *name;
    tcase_fct_ptr fct_ptr;
    time_t exptime;
}tperf_t;

#endif /* ctperf_h */
