#include <QtTest>
#include <stdio.h>

#include "tst_PlantParserTest.h"
#include "tst_PlantLoader.h"

int main(int argc, char *argv[])
{
   int failures = 0;

   PlantParserTest testPlantParser;
   failures += QTest::qExec( &testPlantParser, argc, argv);

   PlantLoaderTest testPalntLoader;
   failures += QTest::qExec( &testPalntLoader, argc, argv);

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
