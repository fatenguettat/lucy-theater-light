#include <QtTest>
#include <stdio.h>

#include "tst_CabledNetworkUI.h"


int main(int argc, char *argv[])
{
   Q_UNUSED(argc);
   Q_UNUSED(argv);

   int failures = 0;

   tst_CabledNetworkUI testCabledNetworkUI;
   char *args1[] =  { "appName", "-o", "out/testCabledNetworkUI.txt" };
   failures += QTest::qExec( &testCabledNetworkUI, 3, args1);

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
