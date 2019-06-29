#ifndef _CODING_TABLE_H_
#define _CODING_TABLE_H_

#include <iostream>
#include<tree.h>
#include<string>
#include<fstream>
#include<unordered_map>
#include<set>
#include<list>

using namespace std;
class CodingTable
{
private:
    unordered_map<char, string> data;
    string calculateBinaryForChar(const char c, const Tree& start) const;

public:
    CodingTable():data() {};
    CodingTable(unordered_map<char, string> _data): data(_data) {}
    CodingTable(Tree& tree);

    unordered_map<char, string> getData() const;

    bool isEmpty() const;
    void print() const;
};

#endif // _CODING_TABLE_H_
