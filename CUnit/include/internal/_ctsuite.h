//
//  _ctsuite.h
//  cunit
//
//  Created by Romain on 20/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef _ctsuite_h
#define _ctsuite_h

#include "ctcase.h"

typedef struct ctcaselist_t {
    ctcase_t *tcase;
    struct ctcaselist_t *next;
}ctcaselist_t;

typedef struct ctsuite_int_t {
    ctcaselist_t *tcases;
    unsigned int tcaseCount;
}ctsuite_int_t;

#endif /* _ctsuite_h */
