//
//  ctexpect.c
//  cunit
//
//  Created by itzseven on 14/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctexpect.h"
#include "_ctexpect.h"
#include <stdlib.h>
#include <stdbool.h>

ctexpect_t *_ctexpect(const char *description) {
    ctexpect_t *expectation = malloc(sizeof(ctexpect_t));
    expectation->desc = description;
    expectation->inverted = false;
    expectation->expectedFulfillmentCount = 1;
    expectation->assertForOverFulfill = false;
    expectation->_internal = malloc(sizeof(ctexpect_int_t));
    ((ctexpect_int_t *)expectation->_internal)->currentFulfillmentCount = 0;
    ((ctexpect_int_t *)expectation->_internal)->fulfilled = false;
    
    return expectation;
}

void fulfill(ctexpect_t *texpect) {
    ctexpect_int_t *expectInternal = (ctexpect_int_t *)texpect->_internal;
    
    if (expectInternal->currentFulfillmentCount == 0) {
        expectInternal->fulfilled = texpect->inverted;
    }
    
    if (texpect->inverted) {
        expectInternal->fulfilled = false;
    } else {
        expectInternal->currentFulfillmentCount++;
        
        if (expectInternal->currentFulfillmentCount == texpect->expectedFulfillmentCount) {
            expectInternal->fulfilled = true;
        } else if ((expectInternal->currentFulfillmentCount > texpect->expectedFulfillmentCount)) {
            expectInternal->fulfilled = !texpect->assertForOverFulfill;
        } else {
            expectInternal->fulfilled = false;
        }
    }
}

void ctefree(ctexpect_t *texpect) {
    free(texpect->_internal);
    free(texpect);
}
