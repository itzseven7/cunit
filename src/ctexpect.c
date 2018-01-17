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

ctexpect_t *ctexpect(const char *description) {
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

void fulfill(ctexpect_t *expectation) {
    ctexpect_int_t *expectInternal = (ctexpect_int_t *)expectation->_internal;
    
    if (expectInternal->currentFulfillmentCount == 0) {
        expectInternal->fulfilled = expectation->inverted;
    }
    
    if (expectation->inverted) {
        expectInternal->fulfilled = false;
    } else {
        expectInternal->currentFulfillmentCount++;
        
        if (expectInternal->currentFulfillmentCount == expectation->expectedFulfillmentCount) {
            expectInternal->fulfilled = true;
        } else if ((expectInternal->currentFulfillmentCount > expectation->expectedFulfillmentCount)) {
            expectInternal->fulfilled = !expectation->assertForOverFulfill;
        } else {
            expectInternal->fulfilled = false;
        }
    }
}
