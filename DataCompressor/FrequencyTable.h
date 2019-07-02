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
    /// @brief Default constructor
    FrequencyTable():data() {}

    /// @brief Copy constructor
    FrequencyTable(unordered_map<char, int> _data): data(_data) {}

    /// @brief Get the content of the table
    /// @return unordered_map of table values
    unordered_map<char, int> getData() const;

    /// @brief Generate frequency of occurrences
    /// @details Calculate and save in the table
    /// the frequency weight of every symbol in the input
    /// @param inputFileName name of the file where the data to be compressed is stored
    /// @return void
    void fillInFromFile(string inputFileName);

    ///@brief Check if the table is empty
    ///@return Boolean value representing whether the table is empty
    bool isEmpty() const;

    ///@brief Print the table data on the console
    void print();

};

#endif // _FREQUENCY_TABLE_H_
