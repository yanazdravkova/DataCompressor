#ifndef _FREQUENCY_TABLE_H_
#define _FREQUENCY_TABLE_H_
#include<iostream>
#include<unordered_map>
using namespace std;

class FrequencyTable
{
private:
    unordered_map<char, int> data;

public:
    FrequencyTable():data() {}
    FrequencyTable(unordered_map<char, int> _data): data(_data) {}

    unordered_map<char, int> getData() const;

    void fillInFromFile(string inputFileName);

    bool isEmpty() const;
    void print();

};
#endif // _FREQUENCY_TABLE_H_
