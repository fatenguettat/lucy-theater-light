#include <QtTest>
#include <stdio.h>

#include "tst_OwnInputParser.h"
#include "tst_OwnLink.h"

int main(int argc, char *argv[])
{
   int failures = 0;

   tst_OwnInputParser testOwnInputParser;
   failures += QTest::qExec( &testOwnInputParser, argc, argv);

   tst_OwnLink testOwnLink;
   failures += QTest::qExec( &testOwnLink, argc, argv);

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
