#include "iostream"
#include "Compressor.h"

using namespace std;

Compressor::Compressor(string inputFileName)
{
    //prints left for demonstration purposes
    this->inputFileName = inputFileName;

    FrequencyTable frequencyTable ;
    frequencyTable.fillInFromFile(inputFileName);
    frequencyTable.print();

    Tree tree = Tree();
    Tree filledTree = (tree.createFromFrequencyTable(frequencyTable));
    filledTree.print();

    codingTable = new CodingTable(filledTree);
    codingTable->print();
}

Compressor::~Compressor()
{
    delete codingTable;
}

string Compressor::calculateCodeForCharacter(char c)
{
    if(codingTable->isEmpty())
    {
        cerr<<"Empty code table\n";
        return "";
    }
    else
    {
        for(pair<char,string> p : codingTable->getData())
        {
            if(p.first == c)
            {
                string characterCode = p.second;
                return characterCode;
            }
            else {} //continue iteration
        }
    }
}

string Compressor::calculateCodmpressedCode()
{
    if(codingTable->isEmpty())
    {
        cerr<<"Empty code table\n";
        return "";
    }
    else
    {
        ifstream inputFileStream;
        char c;
        inputFileStream.open(inputFileName, ios::in);

        while(true)
        {
            inputFileStream.get(c);
            if(inputFileStream.eof())
            {
                break;
            }
            else
            {
                compressedCode += calculateCodeForCharacter(c);
            }
        }

        inputFileStream.close();
        return compressedCode;
    }
}

void Compressor::saveInFile(string outputFileName) const
{
    if(compressedCode.empty())
    {
        cerr<<"Empty binary code\n";
        return;
    }
    else
    {
        ofstream outputFileStream;
        outputFileStream.open(outputFileName, ios::out );
        outputFileStream<<compressedCode ;
        outputFileStream.close();
    }
}
