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

typedef void ctperf_return_t;
typedef ctperf_return_t (*ctperf_inv_ptr_t)(void);

typedef struct tperf_t {
    const char *name;
    ctperf_inv_ptr_t inv;
    double time;
}ctperf_t;

ctperf_t *ctperf(const char *name, ctperf_inv_ptr_t ptr, double expectedTime);

#endif /* ctperf_h */
