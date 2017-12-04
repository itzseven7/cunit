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
#include "ctypes.h"

typedef void ctperf_return_t;
typedef ctperf_return_t (*ctperf_inv_ptr_t)(void);

/*!
 * @struct ctperf_t
 * @abstract Represents a test performance
 * @discussion You create a test performance when you want to measure the time execution of your test and check if it does not exceed a certain amount of time.
 */

typedef struct tperf_t {
    
    /*!
     *  @brief The name of the test performance
     */
    
    const char *name;
    
    /*! @brief
     *  The pointed function of the test performance
     *  @discussion The function execution time will be measured and compared to the reference time you have defined at object creation.
     */
    
    ctperf_inv_ptr_t inv;
    
    /*! @brief
     *  The setup function of the test performance
     *  @discussion The function will be executed before the invocation so you can prepare some resources or anything mandatory for your test performance.
     */
    
    ctopt_inv_ptr_t setup;
    
    /*! @brief
     *  The teardown function of the test performance
     *  @discussion The function will be executed after the invocation so you can release some resources or cleanup some things you have set in the setup function.
     */
    
    ctopt_inv_ptr_t tdown;
    
    /*!
     *  @brief The expected time of the test performance
     *  @discussion The measured value of the test performance will be compared to this value to decide whether the test performance has passed or failed.
     */
    
    double time;
}ctperf_t;

/*!
 @function   ctperf
 @abstract   Creates a test performance.
 
 @param      name      The name of the test performance.
 @param      inv         The pointed function to call for the measure.
 @param      expectedTime The time you expect the test to take.
 
 @result     Returns an allocated test performance or NULL if name or inv are not valid.
 */

ctperf_t *ctperf(const char *name, ctperf_inv_ptr_t inv, double expectedTime);

#endif /* ctperf_h */
