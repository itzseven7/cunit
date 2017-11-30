//
//  ctperf.h
//  cunit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctperf_h
#define ctperf_h

#include <stdio.h>
#include <time.h>

typedef void ctperf_fct;

typedef ctperf_fct (*tperf_fct_ptr)(void);

typedef struct tperf_t {
    const char *name;
    tperf_fct_ptr fct_ptr;
    double exptime;
}tperf_t;

tperf_t *tperf(const char *name, tperf_fct_ptr ptr, double expectedTime);

#endif /* ctperf_h */
