#include<iostream>
#include<Compressor.h>

using namespace std;

Compressor::Compressor(string inputFileName)
{
    this->inputFileName = inputFileName;
    FrequencyTable* frequencyTable = new FrequencyTable;
    frequencyTable->fillInFromFile(inputFileName);
    //frequencyTable->print();
    Tree* tree = new Tree();
    Tree filledTree = (tree->createFromFrequencyTable(*frequencyTable));
    //filledTree.print();
    codingTable = new CodingTable(filledTree);
    //codingTable->print();
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
                for(pair<char,string> p : codingTable->getData())
                {
                    if(p.first == c)
                    {
                        compressedCode += p.second;
                    }
                }
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
        outputFileStream.open(outputFileName, ios::out | ios::app);
        outputFileStream<<compressedCode ;
        outputFileStream.close();
    }
}
