# cunit

A C library for creating unit tests (inspired by Apple's **XCTest** framework).

Current release : 1.0

The library provides the following features :

* Standard and performance test
* Test cases
* Test suites
* Test assertions
* Test expectations

## Usage

### Create a test

A **test** is an entity which will invoke the code you want to check.

You create a standard test like this :

    #include <cunit.h>

    ctest_return_t testExample(ctest_t *test, void *arg) {
    	puts("Hello this is a test\n");
    }
    
    int main(int argc, const char * argv[]) {
    	ctest_t *test = ctest("test example", testExample, NULL);
    }
    
Your test function must have the following signature :

* Return type is `ctest_return_t`
* First parameter with `ctest_t` pointer
* Second parameter with `void` pointer

#### Test argument

You can also pass an argument at the test creation :

    ctest_return_t testExample(ctest_t *test, void *arg) {
    	printf("Hello this is a test with argument %d\n", *((int *)arg));
    }
    
    int main(int argc, const char * argv[]) {
    	unsigned int a = 5;
    
	 	ctest_t *test = ctest("test example", testExample, (void *)&arg);
    }
    
#### Optional function : setup and tear down

You may want to do some processing **before** and/or **after** the invocation of your test.

    ctopt_return_t testSetupExample(void *arg) {
    	puts("Hello this is a setup\n");
    }

    ctopt_return_t testTearDownExample(void *arg) {
    	puts("Hello this is a tear down\n");
    }
    
    ctest_return_t testExample(ctest_t *test, void *arg) {
    	puts("Hello this is a test\n");
    }
    
    int main(int argc, const char * argv[]) {
    	ctest_t *test = ctest("test example", testExample, NULL);
    	test->setup = testSetupExample;
    	test-> tdown = testTearDownExample;
    }
    
Your optional function must have the following signature :

* Return type is `ctopt_return_t`
* Second parameter with `void` pointer

*Note* : the `void` pointer used in the optional functions is the same than the one passed to your invocation.
    
### Create a test case

A **test case** is a collection of tests that you create like this.

    ctcase_t *testCase = ctcase("test case example");
    
You can add two types of tests :

* a **standard** test where only the logic will be tested
* a **performance** test where only the execution time matters
    
#### Add a standard test
    
    ctcase_t *testCase = ctcase("test case example");
    ctest_t *test = ctest("test example", testExample, NULL);
    
    ctctestadd(testCase, test);
        
#### Add a performance test

    ctcase_t *testCase = ctcase("test case example");
    ctest_t *test = ctest("test example", testExample, NULL);
    
    ctcperfadd(testCase, test, 0.005);

### Create and run a test suite

A **test suite** is a collection test cases that you create like this.

    ctsuite_t *suite = ctsuite("test suite example");
    
You add a test case to your suite like this

    ctsuite_t *suite = ctsuite("test suite example");
    ctcase_t *testCase = ctcase("test case example");
    ...

    ctscaseadd(suite, testCase);
    
Once everything is configured, you run the tests like this

    ctsrun(suite);

### Assertions and expectations

You use assertions and expectations to ensure that your code is behaving as expected.

#### Assertions

#### Expectations

## Changelog

* v1.0.1 : rename assertion macros
* v1.0 : Initial release