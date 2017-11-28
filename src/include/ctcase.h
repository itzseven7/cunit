//
//  ctcase.h
//  CUnit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctcase_h
#define ctcase_h

typedef int ctcase_fct;

typedef ctcase_fct (*tcase_fct_ptr)(void);

typedef struct tcase_t {
    const char *name;
    tcase_fct_ptr fct_ptr;
}tcase_t;

tcase_t *tcasealloc(const char *name, tcase_fct_ptr ptr);

#endif /* ctcase_h */
