REM run this script form Test folder


echo ""
echo "running tests"
echo ""

echo "running OpenWebNet tests"
..\..\build-allTests-MSVC_2012-Release\OpenWebNet\release\tst_OpenWebNet.exe
type out\testOwnInputParser.txt
type out\testOwnLink.txt
type out\testOwnFormatter.txt
type out\testOwnEngine.txt

echo "running Plant Parser tests"
..\..\build-allTests-MSVC_2012-Release\PlantParser\release\tst_PlantParser.exe
type out\testPlantParser.txt
type out\testPlantLoader.txt


echo "running Terminal tests"
..\..\build-allTests-MSVC_2012-Release\Terminal\release\tst_Terminal.exe -o out\testCabledNetworkUI.txt
type out\testCabledNetworkUI.txt

echo "running UI tests"
..\..\build-allTests-MSVC_2012-Release\QtGui\release\tst_GuiInterfaceQt.exe -o out\testGui.txt
type out\testGui.txt
