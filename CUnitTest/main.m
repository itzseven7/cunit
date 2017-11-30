//
//  main.m
//  CUnitTest
//
//  Created by Romain on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "cunit.h"

ctcase_fct fct1() {
    puts("fct1 execution\n");
    return 0;
}

ctcase_fct fct2() {
    puts("fct2 execution\n");
    return 2;
}

ctcase_fct fct3() {
    puts("fct3 execution\n");
    return 0;
}

ctcase_fct fct4() {
    puts("fct4 execution\n");
    return 1;
}

ctcase_fct fct5() {
    puts("fct5 execution\n");
    return 0;
}

ctcase_fct fct6() {
    puts("fct6 execution\n");
    return 0;
}

ctcase_fct fct7() {
    puts("fct7 execution\n");
    return 2;
}

ctcase_fct fct8() {
    puts("fct8 execution\n");
    return -1;
}

ctperf_fct testPerformanceNotTooLong() {
    int i = 0;
    
    FILE* debug = fopen("/dev/null", "w");
    
    for (i = 0; i < 10000; i++) {
        fprintf(debug, "%d.", i);
    }
    
    puts("testPerformanceNotTooLong finished\n");
}

ctperf_fct testPerformanceTooLong() {
    int i = 0;
    
    FILE* debug = fopen("/dev/null", "w");
    
    for (i = 0; i < 10000; i++) {
        fprintf(debug, "%d.", i);
    }
    
    puts("testPerformanceTooLong finished\n");
}

int main(int argc, const char * argv[]) {
    
    tsuite_t *suite = tsuitealloc("test");
    
    tcase_t *tcase1 = tcasealloc("fct1", fct1);
    tcase_t *tcase2 = tcasealloc("fct2", fct2);
    tcase_t *tcase3 = tcasealloc("fct3", fct3);
    tcase_t *tcase4 = tcasealloc("fct4", fct4);
    tcase_t *tcase5 = tcasealloc("fct5", fct5);
    
    tsuiteadd(tcase1, suite);
    tsuiteadd(tcase2, suite);
    tsuiteadd(tcase3, suite);
    tsuiteadd(tcase4, suite);
    tsuiteadd(tcase5, suite);
    
    tsuiterun(suite);
    
    tsuite_t *suite2 = tsuitealloc("test2");
    
    tcase_t *tcase6 = tcasealloc("fct6", fct6);
    tcase_t *tcase7 = tcasealloc("fct7", fct7);
    tcase_t *tcase8 = tcasealloc("fct8", fct8);
    
    tperf_t *tperf1 = tperf("testPerformanceNotTooLong", testPerformanceNotTooLong, 0.005);
    tperf_t *tperf2 = tperf("testPerformanceTooLong", testPerformanceTooLong, 0.0005);
    
    tsuiteadd(tcase6, suite2);
    tsuiteadd(tcase7, suite2);
    tsuiteadd(tcase8, suite2);
    
    tsaddperf(tperf1, suite2);
    tsaddperf(tperf2, suite2);
    
    tsuiterun(suite2);
    
    return 0;
}
