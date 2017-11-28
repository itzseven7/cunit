//
//  cassert.h
//  CUnit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef cassert_h
#define cassert_h

#define casserteq(a, b, args…)\
if (a != b) { \
printf(args); \
return 1; \
} \

//#define cfail(reason) printf("");return 1;
//
//#define casserteq(a, b, ...) if (a != b) { return 1; }
//#define cassertneq(a, b) if (a == b) { return 1; }

#endif /* cassert_h */
