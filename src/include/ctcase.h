//
//  ctcase.h
//  CUnit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctcase_h
#define ctcase_h

typedef enum {
    CTPASSED = 0,
    CTFAILED = 1
}CTestResultType;

typedef CTestResultType ctcase_return_t;
typedef ctcase_return_t (*ctcase_inv_ptr_t)(void);

typedef void ctopt_return_t;
typedef ctopt_return_t (*ctopt_inv_ptr_t)(void);

typedef struct tcase_t {
    const char *name;
    ctcase_inv_ptr_t inv;
    ctopt_inv_ptr_t setup;
    ctopt_inv_ptr_t teardown;
}ctcase_t;

ctcase_t *ctcase(const char *name, ctcase_inv_ptr_t inv);

#endif /* ctcase_h */
