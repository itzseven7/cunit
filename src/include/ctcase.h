//
//  ctcase.h
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctcase_h
#define ctcase_h

#include "ctypes.h"

/*!
 @enum       CTestResultType
 @abstract   Test result types
 
 @constant   CTPassed    Test passed
 @constant   CTFailed     Test failed
 @constant   CTUndefined    Undefined test result
 */

typedef enum {
    CTPassed = 0,
    CTFailed = 1,
    CTUndefined = -1
}CTestResultType;

typedef CTestResultType ctcase_return_t;
typedef ctcase_return_t (*ctcase_inv_ptr_t)(void);

/*!
 * @struct ctcase_t
 * @abstract Represents a test case
 * @discussion You create a test case when you want to assert that your code satisfies some conditions during execution.
 */

typedef struct tcase_t {
    
    /*!
     *  @brief The name of the test case
     */
    
    const char *name;
    
    /*! @brief
     *  The pointed function of the test case
     *  @discussion Set the pointer of the function you want to test. Your function must conforms to the definition type : it does not take parameters and should return a CTestResultType value.
     *  For preparing and cleaning resources for your test, please use the setup and tdown fields.
     */
    
    ctcase_inv_ptr_t inv;
    
    /*! @brief
     *  The setup function of the test case
     *  @discussion The function will be executed before the invocation so you can prepare some resources or anything mandatory for your test case.
     */
    
    ctopt_inv_ptr_t setup;
    
    /*! @brief
     *  The teardown function of the test case
     *  @discussion The function will be executed after the invocation so you can release some resources or cleanup some things you have set in the setup function.
     */
    
    ctopt_inv_ptr_t tdown;
}ctcase_t;

/*!
 @function   ctcase
 @abstract   Creates a test case.
 
 @param      name      The name of the test case.
 @param      inv         The pointed function to call for the test case.
 
 @result     Returns an allocated test case or NULL if name or inv are not valid.
 */

ctcase_t *ctcase(const char *name, ctcase_inv_ptr_t inv);

#endif /* ctcase_h */
