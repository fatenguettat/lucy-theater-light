#include <QtTest>
#include <stdio.h>

#include "tst_OwnInputParser.h"
#include "tst_OwnLink.h"

int main(int argc, char *argv[])
{
   Q_UNUSED(argc);
   Q_UNUSED(argv);

   int failures = 0;

   tst_OwnInputParser testOwnInputParser;
   char *args1[] =  { "appName", "-o", "out/testOwnInputParser.txt" };
   failures += QTest::qExec( &testOwnInputParser, 3, args1);

   tst_OwnLink testOwnLink;
   char *args2[] =  { "appName", "-o", "out/testOwnLink.txt" };
   failures += QTest::qExec( &testOwnLink, 3, args2);

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
