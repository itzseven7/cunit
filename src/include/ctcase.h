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

typedef enum {
    CTPassed = 0,
    CTFailed = 1,
    CTUndefined = -1
}CTestResultType;

typedef CTestResultType ctcase_return_t;
typedef ctcase_return_t (*ctcase_inv_ptr_t)(void);

typedef struct tcase_t {
    const char *name;
    ctcase_inv_ptr_t inv;
    ctopt_inv_ptr_t setup;
    ctopt_inv_ptr_t tdown;
}ctcase_t;

ctcase_t *ctcase(const char *name, ctcase_inv_ptr_t inv);

#endif /* ctcase_h */
