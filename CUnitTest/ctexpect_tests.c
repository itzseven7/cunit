//
//  ctexpect_tests.c
//  CUnitTest
//
//  Created by itzseven on 16/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#include "ctexpect_tests.h"
#include "ctexpect.h"
#include "_ctexpect.h"
#include <assert.h>
#include <string.h>

void ctexpect_test_creation() {
    ctexpect_t *expectation = _ctexpect("Test expectation");
    
    assert(strcmp(expectation->desc, "Test expectation") == 0);
    assert(expectation->inverted == false);
    assert(expectation->expectedFulfillmentCount == 1);
    assert(expectation->assertForOverFulfill == false);
    
    ctexpect_int_t *expectationInternal = (ctexpect_int_t *)expectation->_internal;
    
    assert(expectationInternal->currentFulfillmentCount == 0);
    assert(expectationInternal->fulfilled == false);
}

void ctexpect_test_fulfill_normal() {
    ctexpect_t *expectation = _ctexpect("Test expectation");
    
    fulfill(expectation);
    
    ctexpect_int_t *expectationInternal = (ctexpect_int_t *)expectation->_internal;
    assert(expectationInternal->currentFulfillmentCount == 1);
    assert(expectationInternal->fulfilled == true);
}

void ctexpect_test_fulfill_inverted() {
    ctexpect_t *expectation = _ctexpect("Test expectation");
    expectation->inverted = true;
    
    fulfill(expectation);
    
    ctexpect_int_t *expectationInternal = (ctexpect_int_t *)expectation->_internal;
    assert(expectationInternal->fulfilled == false);
}

void ctexpect_test_fulfill_expected_fulfillment_count() {
    ctexpect_t *expectation = _ctexpect("Test expectation");
    expectation->expectedFulfillmentCount = 3;
    
    fulfill(expectation);
    
    ctexpect_int_t *expectationInternal = (ctexpect_int_t *)expectation->_internal;
    assert(expectationInternal->fulfilled == false);
    
    fulfill(expectation);
    fulfill(expectation);
    assert(expectationInternal->fulfilled == true);
}

void ctexpect_test_fulfill_assert_over_fulfill() {
    ctexpect_t *expectation = _ctexpect("Test expectation");
    expectation->assertForOverFulfill = true;
    
    fulfill(expectation);
    fulfill(expectation);
    
    ctexpect_int_t *expectationInternal = (ctexpect_int_t *)expectation->_internal;
    assert(expectationInternal->fulfilled == false);
}

void ctexpect_tests() {
    ctexpect_test_creation();
    ctexpect_test_fulfill_normal();
    ctexpect_test_fulfill_inverted();
    ctexpect_test_fulfill_expected_fulfillment_count();
    ctexpect_test_fulfill_assert_over_fulfill();
}
