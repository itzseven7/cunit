//
//  main.m
//  CUnitTest
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "cunit.h"

ctcase_fct testFail() {
    puts("testFail execution\n");
    cfail("This library should be more comprehensive :(\n")
    return 0;
}

ctcase_fct testEquality() {
    puts("testEquality execution\n");
    int a = 5, b = 9;
    casserteq(a, b, "testEquality failed: %d and %d are not equal\n", a, b)
    return 0;
}

ctcase_fct testNonEquality() {
    puts("testNonEquality execution\n");
    int a = 5, b = 9;
    cassertneq(a, b, "testNonEquality failed: %d and %d are equal\n", a, b)
    return 2;
}

ctcase_fct testTrue() {
    puts("testTrue execution\n");
    int a = 5, b = 9, c = 14;
    cassertt((a + b) == c)
    return 0;
}

ctcase_fct testFalse() {
    puts("testFalse execution\n");
    int a = 5, b = 9, c = 14;
    cassertf((a + b) == c, "testFalse failed: (%d + %d) is equal to %d\n", a, b, c)
    return 1;
}

ctcase_fct testNull() {
    puts("testNull execution\n");
    const char *string = NULL;
    cassertnull(string, "testNull failed: string is not NULL\n")
    return 0;
}

ctcase_fct testNotNull() {
    puts("testNotNull execution\n");
    const char *string = (const char *)malloc(5 * sizeof(char));
    cassertnnull(string, "testNotNull failed: string is NULL\n")
    return 0;
}

ctcase_fct testGreaterThan() {
    puts("testGreaterThan execution\n");
    int a = 2, b = 10;
    cassertgt(a, b, "testGreaterThan failed: %d is not greater than %d\n", a, b)
    return 2;
}

ctcase_fct testGreaterOrEqual() {
    puts("testGreaterOrEqual execution\n");
    int a = 9, b = 10;
    cassertgteq(a, b, "testGreaterOrEqual failed: %d is not greater or equal to %d\n", a, b)
    return -1;
}

ctcase_fct testLessThan() {
    puts("testLessThan execution\n");
    int a = 2, b = 10;
    cassertgt(a, b, "testLessThan failed: %d is not less than %d\n", a, b)
    return 0;
}

ctcase_fct testLessOrEqual() {
    puts("testLessOrEqual execution\n");
    int a = 9, b = 10;
    cassertgteq(a, b, "testLessOrEqual failed: %d is not less or equal to %d\n", a, b)
    return -1;
}

int main(int argc, const char * argv[]) {
    
    tsuite_t *suite = tsuitealloc("Test assertions1");
    
    tcase_t *tcase0 = tcasealloc("testFail", testFail);
    tcase_t *tcase1 = tcasealloc("testEquality", testEquality);
    tcase_t *tcase2 = tcasealloc("testNonEquality", testNonEquality);
    tcase_t *tcase3 = tcasealloc("testTrue", testTrue);
    tcase_t *tcase4 = tcasealloc("testFalse", testFalse);
    tcase_t *tcase5 = tcasealloc("testNull", testNull);
    tcase_t *tcase6 = tcasealloc("testNotNull", testNotNull);
    tcase_t *tcase7 = tcasealloc("testGreaterThan", testGreaterThan);
    tcase_t *tcase8 = tcasealloc("testGreaterOrEqual", testGreaterOrEqual);
    tcase_t *tcase9 = tcasealloc("testLessThan", testLessThan);
    tcase_t *tcase10 = tcasealloc("testLessOrEqual", testLessOrEqual);
    
    tsuiteadd(tcase0, suite);
    tsuiteadd(tcase1, suite);
    tsuiteadd(tcase2, suite);
    tsuiteadd(tcase3, suite);
    tsuiteadd(tcase4, suite);
    tsuiteadd(tcase5, suite);
    
    tsuite_t *suite2 = tsuitealloc("Test assertions2");
    
    tsuiteadd(tcase6, suite2);
    tsuiteadd(tcase7, suite2);
    tsuiteadd(tcase8, suite2);
    tsuiteadd(tcase9, suite2);
    tsuiteadd(tcase10, suite2);
    
    tsuiterun(suite);
    tsuiterun(suite2);
    
    return 0;
}
