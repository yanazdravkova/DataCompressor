#include <iostream>
#include<Tree.h>
#include<CodingTable.h>
#include<FrequencyTable.h>
#include<Compressor.h>
using namespace std;

int main()
{
    Compressor* compressor = new Compressor("input.txt");
    compressor->calculateCodmpressedCode();
    compressor->saveInFile("output.txt");
    return 0;
}
