#ifndef _CODING_TABLE_H_
#define _CODING_TABLE_H_

#include "iostream"
#include "string"
#include "fstream"
#include "unordered_map"
#include "set"
#include "list"
#include "Tree.h"

using namespace std;

/// class CodingTable
/// @brief Abstraction for Coding table
/// @details The class provides representation and
/// functionality for the coding table consisting of characters from the input and their binary representations after the coding.
class CodingTable
{
private:
    unordered_map<char, string> data;
    string calculateBinaryForChar(const char c, const Tree& start) const;

public:
    /// @brief Default constructor
    CodingTable():data() {};

    /// @brief Parameter constructor
    CodingTable(unordered_map<char, string> _data): data(_data) {}

    /// @brief Copy constructor
    CodingTable(Tree& tree);

    /// @brief Get the content of the table
    /// @return unordered_map of table values
    unordered_map<char, string> getData() const;

    ///@brief Check if the table is empty
    ///@return Boolean value representing whether the table is empty
    bool isEmpty() const;

    ///@brief Print the table data on the console
    void print() const;
};

#endif // _CODING_TABLE_H_
