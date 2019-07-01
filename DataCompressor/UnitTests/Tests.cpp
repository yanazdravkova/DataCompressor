#include "iostream"
#include "../Tree.h"
#include "../CodingTable.h"
#include "../Compressor.h"
#include "../FrequencyTable.h"
#include "../Constants.h"

#include "catch.hpp"

TEST_CASE( "FillInFromFile_WithExistingFile_ReturnsNonEmptyTable", "[frequency table]" )
{
    FrequencyTable frequencyTable;

    frequencyTable.fillInFromFile(INPUT_FILE_NAME);

    REQUIRE( frequencyTable.isEmpty() == false );
}

TEST_CASE( "FillInFromFile_WithExistingFile_ReturnsFilledTable", "[frequency table]" )
{
    FrequencyTable frequencyTable;

    frequencyTable.fillInFromFile(INPUT_FILE_NAME);
    unordered_map<char, int> frequencyTableData = frequencyTable.getData();

    REQUIRE( frequencyTableData.at('D') == 1 );
    REQUIRE( frequencyTableData.at('C') == 1 );
    REQUIRE( frequencyTableData.at('R') == 2 );
    REQUIRE( frequencyTableData.at('B') == 2 );
    REQUIRE( frequencyTableData.at('A') == 5 );
}

TEST_CASE("TreeParameterConstructor_WithValidRootAndEmptySubtrees_TreeConstructed", "[tree]")
{
    pair<char, int> root ('A', 1);
    Tree tree = Tree(root, Tree(), Tree());

    REQUIRE(tree.isEmpty() == false);
}

TEST_CASE("TreeParameterConstructor_WithValidRootAndNonEmptySubtrees_TreeConstructed", "[tree]")
{
    Tree tree = Tree(make_pair('A', 1),
                     Tree(make_pair('B', 2), Tree(), Tree()),
                     Tree(make_pair('C', 3), Tree(),
                          Tree(make_pair('D', 4), Tree(), Tree())));

    REQUIRE(tree.isEmpty() == false);
}

TEST_CASE("GetRootCharacter_OnTreeWithOnlyCentralVertex_ReturnsCharacter", "[tree]")
{
    pair<char, int> root ('A', 1);
    char expectedResult = 'A';
    Tree tree = Tree(root, Tree(), Tree());

    char rootCharacter = tree.getRootCharacter();

    REQUIRE(rootCharacter == expectedResult);
}

TEST_CASE("GetRootNumber_OnTreeWithOnlyCentralVertex_ReturnsNumber", "[tree]")
{
    pair<char, int> root ('A', 1);
    int expectedResult = 1;

    Tree tree = Tree(root, Tree(), Tree());
    int rootNumber = tree.getRootNumber();

    REQUIRE(rootNumber == expectedResult);
}

TEST_CASE("CreateFromFrequencyTable_ValidFrequencyTable_GeneratedNonEmptyTree", "[tree]")
{
    FrequencyTable frequencyTable;
    frequencyTable.fillInFromFile(INPUT_FILE_NAME);
    Tree tree;

    Tree filledTree = tree.createFromFrequencyTable(frequencyTable);

    REQUIRE( filledTree.isEmpty() == false);
}

