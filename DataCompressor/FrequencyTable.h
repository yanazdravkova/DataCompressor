#ifndef _FREQUENCY_TABLE_H_
#define _FREQUENCY_TABLE_H_

#include "iostream"
#include "unordered_map"

using namespace std;


/// class FrequencyTable
/// @brief Abstraction for Frequency table
/// @details The class provides representation and
/// functionality for the frequency of occurrence for every symbol from the input.
class FrequencyTable
{
private:
    unordered_map<char, int> data;

public:
    /// @brief default constructor
    FrequencyTable():data() {}

    /// @brief copy constructor
    FrequencyTable(unordered_map<char, int> _data): data(_data) {}

    /// @brief access the content of the table
    unordered_map<char, int> getData() const;

    /// @brief generate frequency of occurrences
    /// @details calculate and save in the table
    /// the frequency weight of every symbol in the input
    /// @param inputFileName name of the file where the data to be compressed is stored
    /// @return void
    void fillInFromFile(string inputFileName);

    ///@brief check if the table is empty
    ///@return boolean value representing whether the table is empty
    bool isEmpty() const;

    ///@brief print the table data on the console
    void print();

};

#endif // _FREQUENCY_TABLE_H_
