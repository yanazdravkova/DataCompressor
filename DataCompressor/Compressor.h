#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

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
    ~Compressor();

    string calculateCodeForCharacter(char c);
    string calculateCodmpressedCode();
    void saveInFile(string outputFileName) const;
};

#endif // _COMPRESSOR_H_
