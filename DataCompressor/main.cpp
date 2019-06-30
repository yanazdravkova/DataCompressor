#include "iostream"
#include "Tree.h"
#include "CodingTable.h"
#include "Compressor.h"
#include "FrequencyTable.h"

using namespace std;

int main()
{
    Compressor compressor("input.txt");
    compressor.calculateCodmpressedCode();
    compressor.saveInFile("output.txt");

    return 0;
}
