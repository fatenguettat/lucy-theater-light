#include <QtTest>
#include <stdio.h>

#include "tst_PlantParserTest.h"
#include "tst_PlantLoader.h"

int main(int argc, char *argv[])
{
   Q_UNUSED(argc);
   Q_UNUSED(argv);

   int failures = 0;

   PlantParserTest testPlantParser;
   char *args1[] =  { "appName", "-o", "out/testPlantParser.txt" };
   failures += QTest::qExec( &testPlantParser, 3, args1);

   PlantLoaderTest testPalntLoader;
   char *args2[] =  { "appName", "-o", "out/testPalntLoader.txt" };
   failures += QTest::qExec( &testPalntLoader, 3, args2);

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
