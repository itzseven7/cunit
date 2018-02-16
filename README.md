# cunit

A C unit testing library (inspired by Apple's XCTest framework).

Current release : 1.2

The library provides the following features :

* Basic assertions
* Performance measurement
* Asynchronous testing

## Usage

### Create a test

A **test** is an entity which will execute an individual unit of your source code.

You create a standard test like this :

```c
#include <cunit.h>

ctest_return_t testExample(ctest_t *test, void *arg) {
    puts("Hello this is a test\n");
}
    
int main(int argc, const char * argv[]) {
    ctest_t *test = ctest("test example", testExample, NULL);
}
```

Your test function must have the following signature :

* Return type is `ctest_return_t`
* First parameter is a `ctest_t` pointer
* Second parameter is a `void` pointer

#### Test argument

You can also pass an argument at the test creation :

```c
ctest_return_t testExample(ctest_t *test, void *arg) {
    printf("Hello this is a test with argument %d\n", *((int *)arg));
}
    
int main(int argc, const char * argv[]) {
    unsigned int arg = 5;
    
    ctest_t *test = ctest("test example", testExample, (void *)&arg);
}
```
    
#### Optional function : setup and tear down

You may want to do some processing **before** and/or **after** the invocation of your test.

```c
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
    test->tdown = testTearDownExample;
}
```
    
Your optional function must have the following signature :

* Return type is `ctopt_return_t`
* Second parameter is a `void` pointer

*Note* : the `void` pointer used in the optional functions is the same than the one passed to your test invocation.
    
### Create a test case

A **test case** is a collection of tests that you create like this.

```c
ctcase_t *testCase = ctcase("test case example");
```
    
You can add two types of tests :

* a **standard** test where only the behavior will be tested
* a **performance** test where only the execution time matters
    
#### Add a standard test

```c    
ctcase_t *testCase = ctcase("test case example");
ctest_t *test = ctest("standard test example", testExample, NULL);
    
ctctestadd(testCase, test);
```
        
#### Add a performance test

```c
ctcase_t *testCase = ctcase("test case example");
ctest_t *test = ctest("performance test example", testExample, NULL);
    
ctcperfadd(testCase, test, 0.005);
```

### Create and run a test suite

A **test suite** is a collection of test cases that you create like this.

```c
ctsuite_t *suite = ctsuite("test suite example");
```
    
You add a test case to your suite like this.

```c
ctsuite_t *suite = ctsuite("test suite example");
ctcase_t *testCase = ctcase("test case example");

ctscaseadd(suite, testCase);
```
    
Once everything is configured, you run the tests like this.

```c
ctsrun(suite);
```

### Assertions and expectations

You use **assertions** and **expectations** to ensure that your code is behaving as expected. 

A **failed assertion** or an **unfulfilled expectation** will be interpreted as a failure for your test.

#### Assertions

Assertions are macros that take in parameter :

* the current test
* expression(s) to assert/to compare
* optional supplementary description of the failure

##### Equality

```c
ctest_return_t testExample(ctest_t *test, void *arg) {
    int a = 5, b = 9, c = 7, d = 14;
	
    CTAssertEqual(test, a + b, d, "%d + %d is not equal to %d", a, b, d)
	
    CTAssertNotEqual(test, d - c, b, "%d - %d is equal to %d", d, c, b)
}
```
    
##### Inequality

```c
ctest_return_t testExample(ctest_t *test, void *arg) {
    int a = 5, b = 9, c = 7, d = 14;
	
    CTAssertGreaterThan(test, b + c, d, "%d is not greather than %d", b + c, d)
	
    CTAssertLessThan(test, b - c, a, "%d is not lesser than %d", b - c, a)
	
    CTAssertGreaterThanOrEqual(test, d - b, a, "%d is not greather than or equal to %d", d - b, a)
	
    CTAssertLessThanOrEqual(test, b - a, c, "%d is not lesser or equal to %d", b - a, c)
}
```

##### Truth

```c
ctest_return_t testExample(ctest_t *test, void *arg) {
    int a = 5, b = 9, c = 7, d = 14;
	
    CTAssertTrue(test, ((a + b) == d), "Expression is not true")
	
    CTAssertFalse(test, ((d - b) == c), "Expression is not false")
}
```
    
##### Nullability

```c
ctest_return_t testExample(ctest_t *test, void *arg) {
    void *ptr = NULL;
	
    CTAssertNull(test, ptr, "ptr is not NULL")
	
    ptr = malloc(1);
	
    CTAssertNotNull(test, ptr, "ptr is NULL")
	
    free(ptr);
}
```

##### Unconditional failure

```c
ctest_return_t testExample(ctest_t *test, void *arg) {
	
    int val = *((int *)arg);
	
    if (val <= 0) {
        CTFail(test, "Test argument is not strictly positive\n")
    }
}
```

#### Expectations

An **expectation** can be used when your tested code is being executed asynchronously.

You create an expectation and **fulfill** it when your code has finished the task and behaved as expected.

In your test, once your expectations have been created, you wait for them by specifying a timeout value : if one or several expectations are not fulfilled after the timeout, the test will fail.

Here is an example using a thread.

```c
void *testAsynchronousTask(void *arg) {
    sleep(5);
    fulfill((ctexpect_t *)arg);
    pthread_exit(NULL);
}

ctest_return_t testExample(ctest_t *test, void *arg) {
    
    pthread_t thread;
	
    ctexpect_t *expect = ctexpect(test, "test expectation");
    
    if (pthread_create(&thread, NULL, testAsynchronousTask, (void *)expect) != 0) {
        puts("Couldn't create thread\n");
    }
    
    ctexpectwait(test, 10);
    
    if (pthread_join(thread, NULL) != 0) {
        puts("Couldn't join thread\n");
    }
}
```

### Memory management

The library provides a free function for each kind of object, it frees the object **and** its children :

* the **ctefree** function will only free a `ctexpect_t` object
* the **ctfree** function will free a `ctest_t` object and its `ctexpect_t` children
* the **ctcfree** function will free a `ctcase_t` object and its `ctest_t` children
* the **ctsfree** function will free a `ctsuite_t` object and its `ctcase_t` children

Finally, you just have to free your `ctsuite_t` object and all the associated objects will be freed like a cascade delete.

**Warning : do NOT try to free a child object alone, the library assumes that you will free the parent.**

## Changelog

* v1.2 : 
* v1.1.1 : fix memory issues + improve logging
* v1.1 : complete rewrite + expectations
* v1.0.1 : rename assertion macros
* v1.0 : Initial release
