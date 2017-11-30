//
//  ctcase.c
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctcase.h"
#include <stdlib.h>

ctcase_t *ctcase(const char *name, ctcase_inv_ptr_t inv, ctopt_inv_ptr_t setup, ctopt_inv_ptr_t teardown) {
    ctcase_t *tcase = (ctcase_t *)malloc(sizeof(ctcase_t));
    tcase->name = name;
    tcase->inv = inv;
    tcase->setup = setup;
    tcase->teardown = teardown;
    
    return tcase;
}
