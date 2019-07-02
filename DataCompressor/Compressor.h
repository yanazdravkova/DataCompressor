#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "iostream"
#include "FrequencyTable.h"
#include "Tree.h"
#include "CodingTable.h"

using namespace std;

/// class Compressor
/// @brief Worker responsible for the run of the compression
class Compressor
{
private:
    string inputFileName;
    CodingTable* codingTable;
    string compressedCode;

public:
    /// @brief Default constructor
    Compressor():  inputFileName(""), codingTable(), compressedCode(""){}

    /// @brief Parameter constructor
    /// @param string inputFileName name of the file where the data to be compressed is stored
    Compressor(string inputFileName);

    /// @brief Destructor
    ~Compressor();

    /// @brief Extract binary code from coding table for a certain character
    /// @param char c The character which code to look for
    /// @return string of binary code for c
    string calculateCodeForCharacter(char c);

    /// @brief Generate the final compressed code
    /// @return string of compressed code in binary format
    string calculateCodmpressedCode();

    ///@brief Save compressed code into file
    ///@param string outputFileName file to save to
    void saveInFile(string outputFileName) const;
};

#endif // _COMPRESSOR_H_
