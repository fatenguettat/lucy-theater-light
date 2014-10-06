#include <QtTest>
#include <stdio.h>

#include "tst_OwnInputParser.h"
#include "tst_OwnLink.h"
#include "tst_OwnFormatter.h"
#include "tst_OwnEngine.h"

#include "OwnTypes.h"

Q_DECLARE_METATYPE(own::Where)


int main(int argc, char *argv[])
{
   Q_UNUSED(argc);
   Q_UNUSED(argv);

   qRegisterMetaType<own::Where>("own::Where");

   int failures = 0;

   tst_OwnInputParser testOwnInputParser;
   char *args1[] =  { "appName", "-o", "out/testOwnInputParser.txt" };
   failures += QTest::qExec( &testOwnInputParser, 3, args1);

   tst_OwnLink testOwnLink;
   char *args2[] =  { "appName", "-o", "out/testOwnLink.txt" };
   failures += QTest::qExec( &testOwnLink, 3, args2);

   tst_OwnFormatter testOwnFormatter;
   char *args3[] =  { "appName", "-o", "out/testOwnFormatter.txt" };
   failures += QTest::qExec( &testOwnFormatter, 3, args3);


   tst_OwnEngine testOwnEngine;
   char *args4[] =  { "appName", "-o", "out/testOwnEngine.txt" };
   failures += QTest::qExec( &testOwnEngine, 3, args4);

   if (failures == 0)
   {
      printf("\n\nALL TESTS PASSED\n\n");
   }
   else
   {
      printf("\n\nTHERE WERE ERRORS\n\n");
   }

   return 0;
}
