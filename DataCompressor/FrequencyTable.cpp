
#include <FrequencyTable.h>
#include <iostream>
#include <fstream>

using namespace std;

unordered_map<char, int> FrequencyTable::getData() const
{
    return data;
}
void FrequencyTable::fillInFromFile(string inputFile)
{
    ifstream inputFileStream;
    inputFileStream.open(inputFile, ios::in);

    while(true)
    {
        char c;
        inputFileStream.get(c);
        if(inputFileStream.eof())
            {
                break;
            }
        else if(data.find(c) == data.end())
            {
                data[c] = 1;
            }
        else
            {
                data[c]++;
            }
    }

    inputFileStream.close();
}

bool FrequencyTable::isEmpty() const
{
    return data.empty();
}

void FrequencyTable::print()
{
    for(tuple<char, int> t : data)
    {
        cout<<std::get<0>(t)<<" "<<std::get<1>(t)<<endl;
    }
}
