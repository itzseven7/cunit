//
//  ctperf.h
//  cunit
//
//  Created by itzseven on 18/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef ctperf_h
#define ctperf_h

#include "ctest.h"

typedef struct ctperf_t {
    ctest_t *test;
    double time;
}ctperf_t;

ctperf_t *ctperf(ctest_t *test, double time);

#endif /* ctperf_h */
