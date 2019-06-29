
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
    ifstream fin;
    char c;
    fin.open(inputFile, ios::in);
    while(true)
    {
        fin.get(c);
        if(fin.eof())
            break;
        if(data.find(c) == data.end())
            data[c] = 1;
        else
            data[c]++;
    }
    fin.close();
}

void FrequencyTable::print()
{
    for(tuple<char, int> t : data)
    {
        cout<<std::get<0>(t)<<" "<<std::get<1>(t)<<endl;
    }
}

bool FrequencyTable::isEmpty() const
{
    return data.empty();
}


