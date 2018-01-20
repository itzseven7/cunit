//
//  _ctexpect.h
//  cunit
//
//  Created by itzseven on 14/01/2018.
//  Copyright © 2018 itzseven. All rights reserved.
//

#ifndef _ctexpect_h
#define _ctexpect_h

typedef struct ctexpect_int_t {
    unsigned int currentFulfillmentCount;
    bool fulfilled;
}ctexpect_int_t;

ctexpect_t *_ctexpect(const char *description);

#endif /* _ctexpect_h */
