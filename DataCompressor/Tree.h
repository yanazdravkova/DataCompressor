#ifndef _TREE_HUFFMAN_H_
#define _TREE_HUFFMAN_H_
#include<iostream>
#include<iomanip>
#include<fstream>
#include<list>
#include<FrequencyTable.h>
using namespace std;

struct Node
{
    pair<char,int> data;
    Node* left;
    Node* right;

    Node():data(), left(nullptr), right(nullptr) {}
    Node(const pair<char,int>& data, Node* left = nullptr, Node* right = nullptr)
        : data(data), left(left), right(right) {}

    char getCharacter();
    int getNumber();

    Node* copy();
};

class Tree
{
private:
    Node* root;
    Tree(Node* root): root(root->copy()) {}
    void eraseNode(Node* node);

public:
    Tree(): root(nullptr) {}
    Tree(const pair<char,int>& data, Tree left, Tree right);
    Tree(Tree&& other) noexcept: Tree()
    {
        std::swap(root, other.root);
    }
    Tree(Tree const& other): root(other.root->copy()) {}

    Tree& operator=(Tree other);
    ~Tree();

    Tree getLeftSubtree() const;
    Tree getRightSubtree() const;
    char getRootCharacter() const;
    int getRootNumber() const;
    void getLeaves(list<char>& leaves) const;

    bool isEmpty()const;
    bool isCharacterMember(const char c) const;


    Tree createFromFrequencyTable(FrequencyTable& frequencyTable);
    Tree*& findMinNode(list<Tree*>& nodes);

    void print(ostream& out = cout,int currentHeight = 0) const;
    void saveInFile(string fileName) const;

    ///used program from seminars
    class Position
    {
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
