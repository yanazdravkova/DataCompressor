#include<iostream>
#include<CodingTable.h>
using namespace std;

string CodingTable::calculateBinaryForChar(const char c, const Tree& tree) const
{
    if(tree.getLeftSubtree().isCharacterMember(c))
    {
        return "0" + calculateBinaryForChar(c, tree.getLeftSubtree());
    }
    else if(tree.getRightSubtree().isCharacterMember(c))
    {
        return "1" + calculateBinaryForChar(c, tree.getRightSubtree());
    }
    else
    {
        return "";
    }
}

CodingTable::CodingTable(Tree& tree)
{
    if(tree.isEmpty())
    {
        return;
    }
    else
    {
        list<char> leaves;
        tree.getLeaves(leaves);

        for(char character : leaves)
        {
            data.emplace(character,calculateBinaryForChar(character, tree));
        }
    }
}

unordered_map<char, string> CodingTable::getData() const
{
    return data;
}

bool CodingTable::isEmpty() const
{
    return data.empty();
}

void CodingTable::print() const
{
    cout<<endl;

    for(tuple<char, string> t : data)
    {
        cout<<get<0>(t)<<" "<<get<1>(t)<<endl;
    }

    cout<<endl;
}
