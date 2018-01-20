//
//  ctexpect.h
//  cunit
//
//  Created by itzseven on 14/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef ctexpect_h
#define ctexpect_h

#include <stdbool.h>

typedef struct ctexpect_t {
    const char *desc;
    bool inverted;
    unsigned int expectedFulfillmentCount;
    bool assertForOverFulfill;
    void *_internal;
}ctexpect_t;

void fulfill(ctexpect_t *expectation);

#endif /* ctexpect_h */
