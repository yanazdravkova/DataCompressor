#ifndef _TREE_HUFFMAN_H_
#define _TREE_HUFFMAN_H_

#include "iostream"
#include "iomanip"
#include "fstream"
#include "list"
#include "FrequencyTable.h"

using namespace std;

/// Structure representing node in a tree
struct Node
{
    ///@brief Pair of character and number saved in each node
    ///@details For nodes without letter as a character the empty char is saved instead
    pair<char,int> data;

    ///@brief Pointer to the left node
    Node* left;

    ///@brief Pointer to the right node
    Node* right;

    ///@brief Default constructor
    Node():data(), left(nullptr), right(nullptr) {}

    ///@brief Parameter constructor
    ///@param data Value saved in the node
    ///@param left Pointer to the left node @note default value nullptr
    ///@param right Pointer to the right node @note default value nullptr
    Node(const pair<char,int>& data, Node* left = nullptr, Node* right = nullptr)
        : data(data), left(left), right(right) {}

    ///@brief Access character saved in the node
    ///@return Character saved in the node
    char getCharacter();

    ///@brief Access number saved in the node
    ///@return Number saved in the node
    int getNumber();

    ///@brief Copy node
    ///@return Pointer to a new node identical to the current one
    Node* copy();
};

///@brief Representation of Huffman tree
class Tree
{
private:
    Node* root;
    Tree(Node* root): root(root->copy()) {}
    void eraseNode(Node* node);

public:
    ///@brief Default constructor
    Tree(): root(nullptr) {}

    ///@brief Parameter constructor
    ///@param data Root value
    ///@param left Left tree object
    ///@param left Right tree object
    Tree(const pair<char,int>& data, Tree left, Tree right);

    ///@brief Move constructor
    ///@details New object tree is not created but it rather steals resources of other object
    ///@param other Tree object which resource to steal
    Tree(Tree&& other) noexcept: Tree()
    {
        std::swap(root, other.root);
    }

    ///@brief Copy constructor
    ///@param other Tree object to be copied
    Tree(Tree const& other): root(other.root->copy()) {}

    ///@brief Operator= overload redirect root pointer
    ///@param other Tree object to which the current root is going to point
    ///@return Reference to already existing tree object
    Tree& operator=(Tree other);

    ///@brief Destructor
    ~Tree();

    ///@brief Get left subtree of the current tree
    ///@return new Tree - copy of the left subtree
    Tree getLeftSubtree() const;

    ///@brief Get right subtree of the current tree
    ///@return new Tree - copy of the right subtree
    Tree getRightSubtree() const;

    ///@brief Get root character value
    ///@return root char value
    char getRootCharacter() const;

    ///@brief Get root number value
    ///@return root number value
    int getRootNumber() const;

    ///@brief Generate list of char values saved in the leaves of the tree
    ///@param list<char>& leaves where to save the leaves char values
    void getLeaves(list<char>& leaves) const;

    ///@brief Check if the tree is empty
    ///@return Boolean value representing whether the tree is empty
    bool isEmpty()const;

    ///@brief Check if the tree contains a character
    ///@param const char c The character to be checked for
    ///@return Boolean value representing whether the character is a member
    bool isCharacterMember(const char c) const;

    ///@brief Find tree with the minimum number value in the root among a list of trees
    ///@param list<Tree*>& nodes List of pointer to trees among which to search for the minimum compared by
    /// root number value
    ///@return Pointer to the tree with the minimum root value
    Tree*& findTreeWithMinRootNumber(list<Tree*>& nodes);

    ///@brief Create List of Trees consisting of only one vertex - a certain value from a frequency table
    ///@param FrequencyTable& frequencyTable from which to take values for tree root data
    ///@return List of pointers to tree objects consisting of root only
    list<Tree*> createForestFromFrequencyTable(FrequencyTable& frequencyTable) const;

    ///@brief Create tree based on frequency table
    ///@param FrequencyTable& frequencyTable containing characters and their frequency weight
    ///@return new Tree filled with node values
    Tree createFromFrequencyTable(FrequencyTable& frequencyTable);

    ///@brief Print the table data on the console
    void print(ostream& out = cout,int currentHeight = 0) const;

    ///@brief Save tree into file
    ///@param string outputFileName file to save to
    void saveInFile(string outputFileName) const;

    ///@brief Class for iteration over the tree
    ///@details used program from seminars
    class Position
    {
    private:
        Node*& p;

    public:
        explicit Position(Node*& p): p(p) {};

        explicit operator bool()
        {
            return p != nullptr;
        }

        bool operator!()
        {
            return !(bool)*this;
        }

        pair<char, int> operator*()
        {
            return p->data;
        }

        Position left() const
        {
            return Position(p->left);
        }

        Position right() const
        {
            return Position(p->right);
        }

        bool isLeaf()
        {
            return !(left()) && !(right());
        }
    };

    Position getRoot()
    {
        return Position(root);
    }
};

#endif // _TREE_HUFFMAN_H_
