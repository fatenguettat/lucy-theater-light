REM run this script form Test folder


echo ""
echo "running tests"
echo ""

echo "running OpenWebNet tests"
..\..\build-allTests-5_3_0_Desktop-Release\OpenWebNet\release\tst_OpenWebNet.exe
type out\testOwnInputParser.txt
type out\testOwnLink.txt
type out\testOwnFormatter.txt

echo "running Plant Parser tests"
..\..\build-allTests-5_3_0_Desktop-Release\PlantParser\release\tst_PlantParserTest.exe
type out\testPlantParser.txt
type out\testPalntLoader.txt


echo "running Terminal tests"
..\..\build-allTests-5_3_0_Desktop-Release\Terminal\release\tst_Terminaltest.exe
type out\testCabledNetworkUI.txt
