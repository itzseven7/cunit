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
 * @define cfailure(assertion, ...)
 * Generates a failure unconditionally (for internal usage, use cfail(...) instead in your code).
 */

#define cfailure(assertion, ...) return _cfail(assertion, __FILE__, __LINE__, "" __VA_ARGS__);

/*!
 * @define cfail(...)
 * Generates a failure unconditionally.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cfail(...) cfailure("Assertion", __VA_ARGS__);

/*!
 * @define casserteq(expression, expression1, ...)
 * Generates a failure when ((\a expression1) != (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define casserteq(expression, expression1, ...) if ((expression) != (expression1)) { cfailure("Equality assertion", __VA_ARGS__) }

/*!
 * @define cassertneq(expression, expression1, ...)
 * Generates a failure when ((\a expression1) == (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertneq(expression, expression1, ...) if ((expression) == (expression1)) { cfailure("Non equality assertion", __VA_ARGS__) }

/*!
 * @define cassertt(expression, ...)
 * Generates a failure when ((\a expression) != true).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertt(expression, ...) if (!(expression)) { cfailure("Truth assertion", __VA_ARGS__) }

/*!
 * @define cassertf(expression, ...)
 * Generates a failure when ((\a expression) != false).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertf(expression, ...) if ((expression)) { cfailure("Non truth assertion", __VA_ARGS__) }

/*!
 * @define cassertnull(expression, ...)
 * Generates a failure when ((\a expression) != NULL).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertnull(expression, ...) if ((expression) != NULL) { cfailure("Nullity assertion", __VA_ARGS__) }

/*!
 * @define cassertnnull(expression, ...)
 * Generates a failure when ((\a expression) == NULL).
 * @param expression An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertnnull(expression, ...) if ((expression) == NULL) { cfailure("Non nullity assertion", __VA_ARGS__) }

/*!
 * @define cassertgt(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) <= (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertgt(expression1, expression2, ...) if ((expression1) <= (expression2)) { cfailure("Greather than assertion", __VA_ARGS__) }

/*!
 * @define cassertgteq(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) < (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertgteq(expression1, expression2, ...) if ((expression1) < (expression2)) { cfailure("Greater than or equal assertion", __VA_ARGS__) }

/*!
 * @define cassertlt(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) >= (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertlt(expression1, expression2, ...) if ((expression1) >= (expression2)) { cfailure("Less than assertion", __VA_ARGS__) }

/*!
 * @define cassertlteq(expression1, expression2, ...)
 * Generates a failure when ((\a expression1) > (\a expression2)).
 * @param expression1 An expression of C scalar type.
 * @param expression2 An expression of C scalar type.
 * @param ... An optional supplementary description of the failure. A literal string, optionally with format specifiers. This parameter can be completely omitted.
 */

#define cassertlteq(expression1, expression2, ...) if ((expression1) > (expression2)) { cfailure("Less than or equal assertion", __VA_ARGS__) }

/*!
 @function   _cfail
 @abstract   Generates a failure unconditionally.
 
@discussion This function is for internal usage. If you want to generate a failure unconditionally, please use the defined macro cfail(...)
 */

int _cfail(const char *assertion, const char *filename, unsigned long lineNumber, const char * format, ...);

#endif /* cassert_h */
