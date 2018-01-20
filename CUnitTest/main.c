//
//  main.c
//  CUnitTest
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#include <stdio.h>
#include "ctest_tests.h"
#include "ctexpect_tests.h"
#include "ctcase_tests.h"
#include "ctperf_tests.h"
#include "ctsuite_tests.h"
#include "ctassert_tests.h"

int main(int argc, const char * argv[]) {
    puts("Starts 'unit' testing'\n");
    
    ctest_tests();
    ctexpect_tests();
    ctcase_tests();
    ctperf_tests();
    ctsuite_tests();
    ctassert_tests();
    
    return 0;
}

