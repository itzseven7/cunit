//
//  ctcase.c
//  CUnit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include "ctcase.h"
#include <stdlib.h>

tcase_t *tcasealloc(const char *name, tcase_fct_ptr ptr) {
    tcase_t *tcase = (tcase_t *)malloc(sizeof(tcase_t));
    tcase->name = name;
    tcase->fct_ptr = ptr;
    
    return tcase;
}
