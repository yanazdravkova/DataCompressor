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
    Node* copy();
};

class Tree
{
    Node* root;
    void erase(Node* node);
    Tree(Node* root): root(root->copy()) {}
    void enterHelp(istream& in, Node*& curr);
    pair<char,int> enterPair(istream& in) const;

public:
    Tree(): root(nullptr) {}

    Tree(const pair<char,int>& data, Tree left, Tree right);

    Tree(Tree&& other) noexcept: Tree()
    {
        std::swap(root, other.root);
    }

    Tree(Tree const& other): root(other.root->copy()) {}
    Tree createFromFrequencyTable(FrequencyTable& frequencyTable);
    Tree& operator=(Tree other);

    ~Tree();
    bool isEmpty()const;

    Tree left() const;

    Tree right() const;

    Tree*& findMinNode(list<Tree*>& nodes);
    void prettyPrint(ostream& out = cout,int currentHeight = 0) const;
    void enter(istream& in);
    bool isMember(const char c) const;
    pair<char, int> getRootData() const;
    void save(string fname) const;

    void getLeaves(list<char>& leaves) const;
    ///използвана програма от семинари
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
