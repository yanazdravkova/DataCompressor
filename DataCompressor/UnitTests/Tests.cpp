#include "iostream"
#include "../Tree.h"
#include "../CodingTable.h"
#include "../Compressor.h"
#include "../FrequencyTable.h"
#include "../Constants.h"

#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "FillInFromFile_WithExistingFile_ReturnsNotEmptyTable", "[frequency table]" ) {
    FrequencyTable frequencyTable;

    frequencyTable.fillInFromFile(INPUT_FILE_NAME);

    REQUIRE( frequencyTable.isEmpty() == false );
}

TEST_CASE( "FillInFromFile_WithExistingFile_ReturnsFilledTable", "[frequency table]" ) {
    FrequencyTable frequencyTable;

    frequencyTable.fillInFromFile(INPUT_FILE_NAME);
    unordered_map<char, int> frequencyTableData = frequencyTable.getData();

    REQUIRE( frequencyTableData.at('D') == 1 );
    REQUIRE( frequencyTableData.at('C') == 1 );
    REQUIRE( frequencyTableData.at('R') == 2 );
    REQUIRE( frequencyTableData.at('B') == 2 );
    REQUIRE( frequencyTableData.at('A') == 5 );
}

