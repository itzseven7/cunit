//
//  ctcase.h
//  cunit
//
//  Created by itzseven on 26/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef ctcase_h
#define ctcase_h

#include "ctest.h"

typedef struct ctcase_t {
    const char *name;
    void *_internal;
}ctcase_t;

ctcase_t *ctcase(const char *name);
void ctctestadd(ctcase_t *tcase, ctest_t *test);
void ctcperfadd(ctcase_t *tcase, ctest_t *test, double time);
void ctcfree(ctcase_t *tcase);

#endif /* ctcase_h */
