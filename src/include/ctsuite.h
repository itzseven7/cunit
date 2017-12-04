//
//  ctsuite.h
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctsuite_h
#define ctsuite_h

#include "ctcase.h"
#include "ctperf.h"

typedef struct ctcaselist_t {
    ctcase_t *tcase;
    struct ctcaselist_t *next;
}ctcaselist_t;

typedef struct ctperflist_t {
    ctperf_t *tperf;
    struct ctperflist_t *next;
}ctperflist_t;

/*!
 * @struct ctsuite_t
 * @abstract Represents a test suite
 * @discussion The test suite is the core of unit testing. Adds test cases or performance tests and run them together to ensure that your code works as expected.
 */

typedef struct ctsuite_t {
    
    /*!
     *  @brief The name of the test suite
     */
    
    const char *name;
    
    /*!
     *  @brief The test count in the suite
     *  @discussion This value includes test cases and performance.
     */
    
    int count;
    
    /*!
     *  @brief The passed test count
     *  @discussion This value includes test cases and performance.
     */
    
    int passed;
    
    /*!
     *  @brief The failed test count
     *  @discussion This value includes test cases and performance.
     */
    
    int failed;
    
    /*!
     *  @brief The list of test cases
     */
    
    ctcaselist_t *tcaselist;
    
    /*!
     *  @brief The list of test performances
     */
    
    ctperflist_t *tperflist;
}ctsuite_t;

/*!
 @function   ctsuite
 @abstract   Creates a test suite.
 
 @param      name      The name of the test suite.
 
 @result     Returns an allocated test suite or NULL if name is not valid.
 */

ctsuite_t *ctsuite(const char *name);

/*!
 @function   ctsaddtc
 @abstract   Adds a test case to the suite.
 
 @param      tcase      The test case to add.
 @param      tsuite      The destination test suite.
 */

void ctsaddtc(ctcase_t *tcase, ctsuite_t *tsuite);

/*!
 @function   ctsaddtp
 @abstract   Adds a test performance to the suite.
 
 @param      tperf      The test performance to add.
 @param      tsuite      The destination test suite.
 */

void ctsaddtp(ctperf_t *tperf, ctsuite_t *tsuite);

/*!
 @function   ctsrun
 @abstract   Runs the test suite.
 
 @param      tsuite      The test suite to run.
 
 @discussion This function will start by executing all test cases and terminate by test performances.
 */

void ctsrun(ctsuite_t *tsuite);

#endif /* ctsuite_h */
