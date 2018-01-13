//
//  cassert.h
//  cunit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef cassert_h
#define cassert_h

#include "ctest.h"

/*!
 * @define _CTFailure(assertion, ...)
 * Generates a failure unconditionally (for internal usage, use cfail(...) instead in your code).
 */

#define _CTFailure(test, assertion, ...) _cfail(test, assertion, __FILE__, __LINE__, "" __VA_ARGS__);

/*!
 * @define CTFail(...)
 * Generates a failure unconditionally.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTFail(test, ...) _CTFailure(test, "Assertion", __VA_ARGS__);

/*!
 * @define CTAssertEqual(expression, expression1, ...)
 * Generates a failure when ((\a expression1) != (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertEqual(test, expression, expression1, ...) if ((expression) != (expression1)) { _CTFailure(test, "Equality assertion", __VA_ARGS__) }

/*!
 * @define CTAssertNotEqual(expression, expression1, ...)
 * Generates a failure when ((\a expression1) == (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNotEqual(test, expression, expression1, ...) if ((expression) == (expression1)) { _CTFailure(test, "Non equality assertion", __VA_ARGS__) }

/*!
 * @define CTAssertTrue(expression, ...)
 * Generates a failure when ((\a expression) != true).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertTrue(test, expression, ...) if (!(expression)) { _CTFailure(test, "Truth assertion", __VA_ARGS__) }

/*!
 * @define CTAssertFalse(expression, ...)
 * Generates a failure when ((\a expression) != false).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertFalse(test, expression, ...) if ((expression)) { _CTFailure(test, "Non truth assertion", __VA_ARGS__) }

/*!
 * @define CTAssertNull(expression, ...)
 * Generates a failure when ((\a expression) != NULL).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNull(test, expression, ...) if ((expression) != NULL) { _CTFailure(test, "Nullity assertion", __VA_ARGS__) }

/*!
 * @define CTAssertNotNull(expression, ...)
 * Generates a failure when ((\a expression) == NULL).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNotNull(test, expression, ...) if ((expression) == NULL) { _CTFailure(test, "Non nullity assertion", __VA_ARGS__) }

/*!
 * @define CTAssertGreaterThan(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) <= (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertGreaterThan(test, expression1, expression2, ...) if ((expression1) <= (expression2)) { _CTFailure(test, "Greather than assertion", __VA_ARGS__) }

/*!
 * @define CTAssertGreaterThanOrEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) < (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertGreaterThanOrEqual(test, expression1, expression2, ...) if ((expression1) < (expression2)) { _CTFailure(test, "Greater than or equal assertion", __VA_ARGS__) }

/*!
 * @define CTAssertLessThan(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) >= (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertLessThan(test, expression1, expression2, ...) if ((expression1) >= (expression2)) { _CTFailure(test, "Less than assertion", __VA_ARGS__) }

/*!
 * @define CTAssertLessThanOrEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) > (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertLessThanOrEqual(test, expression1, expression2, ...) if ((expression1) > (expression2)) { _CTFailure(test, "Less than or equal assertion", __VA_ARGS__) }

/*!
 @function   _cfail
 @abstract   Generates a failure unconditionally.
 
@discussion This function is for internal usage. If you want to generate a failure unconditionally, please use the defined macro CTFail(...)
 */

void _cfail(const ctest_t *test, const char *assertion, const char *filename, unsigned long lineNumber, const char * format, ...);

#endif /* cassert_h */
