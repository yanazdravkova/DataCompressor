#include "iostream"
#include "FrequencyTable.h"
#include "Tree.h"
#include "CodingTable.h"

using namespace std;

class Compressor
{
private:
    string inputFileName;
    CodingTable* codingTable;
    string compressedCode;
public:
    Compressor():  inputFileName(""), codingTable(), compressedCode(""){}
    Compressor(string inputFileName);

    string calculateCodmpressedCode();
    void saveInFile(string outputFileName) const;
};

