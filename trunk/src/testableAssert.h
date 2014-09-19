#include <QString>

/** @file testableAssert.h
 *  This file exports macro T_ASSERT.
 *  Such macro is the same as Q_ASSERT if current build is not inside a
 *  unit test suite, while it throws an exception in case of unit test.
 *  Exception has a QString parameter with a fixed string.
 */

#ifndef  UNIT_TEST
#define T_ASSERT(c)    Q_ASSERT(c)
#else
#define T_ASSERT(c)    if (c==false) throw QString("Assert fail: %1").arg(#c);
#endif
