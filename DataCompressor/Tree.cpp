#include<tree.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<list>
#include<set>
using namespace std;
bool sortBySecond(const Tree* firstTree,const Tree* secondTree)
{
    int firstRootNumber = firstTree->getRootNumber();
    const int secondRootNumber = secondTree->getRootNumber();
    return (firstRootNumber < secondRootNumber);
}

Node* Node::copy()
{
    if (this == nullptr)
    {
        return nullptr;
    }

    return new Node(data, left->copy(), right->copy());
}

char Node::getCharacter()
{
    char result = data.first;
    return result;
}

int Node::getNumber()
{
    int result = data.second;
    return result;
}

void Tree::eraseNode(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    eraseNode(node->left);
    eraseNode(node->right);
    delete node;
}

Tree::Tree(const pair<char,int>& data, Tree left, Tree right)
{
    root = new Node(data);
    std::swap(root->left, left.root);
    std::swap(root->right, right.root);
}
Tree& Tree::operator=(Tree other)
{
    std::swap(root, other.root);
    return *this;
}
Tree::~Tree()
{
    eraseNode(root);
}
bool Tree::isEmpty()const
{
    return root == nullptr;
}
Tree Tree::getLeftSubtree() const
{
    return Tree(root->left);
}

Tree Tree::getRightSubtree() const
{
    return Tree(root->right);
}

Tree*& Tree::findMinNode(list<Tree*>& nodes)
{
    nodes.sort(sortBySecond);
    return nodes.front();
}

Tree Tree::createFromFrequencyTable(FrequencyTable& frequencyTable)
{
    if(frequencyTable.isEmpty())
    {
        cerr<<"Empty frequency table\n";
        exit(1);
    }

    list<Tree*> nodes;

    for(const pair<char,int> p : frequencyTable.getData())
    {
        nodes.push_front(new Tree(p, Tree(), Tree()));
    }

    while(nodes.size() > 1)
    {
        Tree* first = findMinNode(nodes);
        nodes.pop_front();
        Tree* second = findMinNode(nodes);
        nodes.pop_front();
        Tree* firstAndSecondCombined = new Tree(make_pair(' ',first->getRootNumber() + second->getRootNumber()), *first, *second);//строим ново дърво с поддървета 2те най-малки досега
        nodes.push_front(firstAndSecondCombined);
    }

    Tree resultTree = *(nodes.front());
    nodes.pop_front();
    return resultTree;
}

void Tree::print(ostream& outputStream, int currentHeight) const
{
    if(isEmpty())
    {
        return;
    }
    else
    {
        getRightSubtree().print(outputStream, currentHeight + 1);
        outputStream<<setw(5*currentHeight)<<root->getCharacter()<<root->getNumber()<<endl;
        getLeftSubtree().print(outputStream, currentHeight + 1);
    }
}

bool Tree::isCharacterMember(const char c) const
{
    if(isEmpty())
        {
            return false;
        }
    else if(root->getCharacter() == c)
        {
            return true;
        }
    else
    {
        bool result = getLeftSubtree().isCharacterMember(c) || getRightSubtree().isCharacterMember(c);
        return result;
    }
}

char Tree::getRootCharacter() const
{
    char rootCharacter = root->getCharacter();
    return rootCharacter;
}
int Tree::getRootNumber() const
{
    int rootNumber = root->getNumber();
    return rootNumber;
}
void Tree::saveInFile(string fileName) const
{
    ofstream fout;
    fout.open(fileName, ios::out);//изтрива всичко друго, което е имало преди във файла
    print(fout,0);
    fout.close();
}

void Tree::getLeaves(list<char>& leaves) const
{
    if(root == nullptr)
    {
        return;
    }
    else if(root->getCharacter() == ' ')
    {
        getRightSubtree().getLeaves(leaves);
        getLeftSubtree().getLeaves(leaves);
    }
    else
    {
        leaves.push_back(root->getCharacter());
        return;
    }
}
