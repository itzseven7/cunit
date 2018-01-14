//
//  ctexpect.c
//  cunit
//
//  Created by Romain on 14/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctexpect.h"
#include "_ctexpect.h"
#include <stdlib.h>
#include <stdbool.h>

ctexpect_t *ctexpect(const char *description) {
    ctexpect_t *expectation = malloc(sizeof(ctexpect_t));
    expectation->desc = description;
    //expectation->inverted = false;
    expectation->expectedFulfillmentCount = 1;
    expectation->assertForOverFulfill = false;
    expectation->_internal = malloc(sizeof(ctexpect_int_t));
    ((ctexpect_int_t *)expectation->_internal)->currentFulfillmentCount = 0;
    ((ctexpect_int_t *)expectation->_internal)->fulfilled = false;
    
    return expectation;
}

void fulfill(ctexpect_t *expectation) {
    ((ctexpect_int_t *)expectation->_internal)->currentFulfillmentCount++;
    
    if (((ctexpect_int_t *)expectation->_internal)->currentFulfillmentCount == expectation->expectedFulfillmentCount) {
        ((ctexpect_int_t *)expectation->_internal)->fulfilled = true;
    } else {
        ((ctexpect_int_t *)expectation->_internal)->fulfilled = false;
    }
}
