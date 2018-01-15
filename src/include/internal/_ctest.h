//
//  _ctest.h
//  cunit
//
//  Created by itzseven on 13/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef _ctest_h
#define _ctest_h

typedef struct ctexpectlist_t {
    ctexpect_t *expect;
    struct ctexpectlist_t *next;
}ctexpectlist_t;

typedef struct ctest_int_t {
    unsigned int failures;
    unsigned int unfulfilledExpectations;
    ctexpectlist_t *expectations;
    unsigned int expectCount;
}ctest_int_t;

#endif /* _ctest_h */
