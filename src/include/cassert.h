//
//  cassert.h
//  cunit
//
//  Created by itzseven on 28/11/2017.
//  Copyright © 2017 itzseven. All rights reserved.
//

#ifndef cassert_h
#define cassert_h

/*!
 * @define _CTFailure(assertion, ...)
 * Generates a failure unconditionally (for internal usage, use cfail(...) instead in your code).
 */

#define _CTFailure(assertion, ...) return _cfail(assertion, __FILE__, __LINE__, "" __VA_ARGS__);

/*!
 * @define CTFail(...)
 * Generates a failure unconditionally.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTFail(...) _CTFailure("Assertion", __VA_ARGS__);

/*!
 * @define CTAssertEqual(expression, expression1, ...)
 * Generates a failure when ((\a expression1) != (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertEqual(expression, expression1, ...) if ((expression) != (expression1)) { _CTFailure("Equality assertion", __VA_ARGS__) }

/*!
 * @define CTAssertNotEqual(expression, expression1, ...)
 * Generates a failure when ((\a expression1) == (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNotEqual(expression, expression1, ...) if ((expression) == (expression1)) { _CTFailure("Non equality assertion", __VA_ARGS__) }

/*!
 * @define CTAssertTrue(expression, ...)
 * Generates a failure when ((\a expression) != true).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertTrue(expression, ...) if (!(expression)) { _CTFailure("Truth assertion", __VA_ARGS__) }

/*!
 * @define CTAssertFalse(expression, ...)
 * Generates a failure when ((\a expression) != false).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertFalse(expression, ...) if ((expression)) { _CTFailure("Non truth assertion", __VA_ARGS__) }

/*!
 * @define CTAssertNull(expression, ...)
 * Generates a failure when ((\a expression) != NULL).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNull(expression, ...) if ((expression) != NULL) { _CTFailure("Nullity assertion", __VA_ARGS__) }

/*!
 * @define CTAssertNotNull(expression, ...)
 * Generates a failure when ((\a expression) == NULL).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertNotNull(expression, ...) if ((expression) == NULL) { _CTFailure("Non nullity assertion", __VA_ARGS__) }

/*!
 * @define CTAssertGreaterThan(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) <= (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertGreaterThan(expression1, expression2, ...) if ((expression1) <= (expression2)) { _CTFailure("Greather than assertion", __VA_ARGS__) }

/*!
 * @define CTAssertGreaterThanOrEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) < (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertGreaterThanOrEqual(expression1, expression2, ...) if ((expression1) < (expression2)) { _CTFailure("Greater than or equal assertion", __VA_ARGS__) }

/*!
 * @define CTAssertLessThan(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) >= (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertLessThan(expression1, expression2, ...) if ((expression1) >= (expression2)) { _CTFailure("Less than assertion", __VA_ARGS__) }

/*!
 * @define CTAssertLessThanOrEqual(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) > (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define CTAssertLessThanOrEqual(expression1, expression2, ...) if ((expression1) > (expression2)) { _CTFailure("Less than or equal assertion", __VA_ARGS__) }

/*!
 @function   _cfail
 @abstract   Generates a failure unconditionally.
 
@discussion This function is for internal usage. If you want to generate a failure unconditionally, please use the defined macro CTFail(...)
 */

int _cfail(const char *assertion, const char *filename, unsigned long lineNumber, const char * format, ...);

#endif /* cassert_h */
