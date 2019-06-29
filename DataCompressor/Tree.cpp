#include "algorithm"
#include "iostream"
#include "iomanip"
#include "fstream"
#include "list"
#include "set"
#include "Tree.h>

using namespace std;

bool sortBySecond(const Tree* firstTree,const Tree* secondTree)
{
    int firstRootNumber = firstTree->getRootNumber();
    const int secondRootNumber = secondTree->getRootNumber();
    return (firstRootNumber < secondRootNumber);
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

Node* Node::copy()
{
    if (this == nullptr)
    {
        return nullptr;
    }

    return new Node(data, left->copy(), right->copy());
}

void Tree::eraseNode(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        eraseNode(node->left);
        eraseNode(node->right);
        delete node;
    }
}

Tree::Tree(const pair<char, int>& data, Tree left, Tree right)
{
    root = new Node(data);
    swap(root->left, left.root);
    swap(root->right, right.root);
}

Tree& Tree::operator=(Tree other)
{
    swap(root, other.root);
    return *this;
}

Tree::~Tree()
{
    eraseNode(root);
}

Tree Tree::getLeftSubtree() const
{
    return Tree(root->left);
}

Tree Tree::getRightSubtree() const
{
    return Tree(root->right);
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

bool Tree::isEmpty()const
{
    return root == nullptr;
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

Tree*& Tree::findTreeWithMinRootNumber(list<Tree*>& nodes)
{
    nodes.sort(sortBySecond);
    return nodes.front();
}
list<Tree*> Tree::createForestFromFrequencyTable(FrequencyTable& frequencyTable) const
{
    list<Tree*> forest;

    for(const pair<char,int> p : frequencyTable.getData())
    {
        forest.push_front(new Tree(p, Tree(), Tree()));
    }

    return forest;
}

Tree Tree::createFromFrequencyTable(FrequencyTable& frequencyTable)
{
    if(frequencyTable.isEmpty())
    {
        cerr<<"Empty frequency table\n";
        exit(1);
    }

    else
    {
        list<Tree*> forest = createForestFromFrequencyTable(frequencyTable);

        while(forest.size() > 1)
        {
            Tree* first = findTreeWithMinRootNumber(forest);
            forest.pop_front();
            Tree* second = findTreeWithMinRootNumber(forest);
            forest.pop_front();
            Tree* firstAndSecondCombined = new Tree(make_pair(' ',first->getRootNumber() + second->getRootNumber()), *first, *second);//������ ���� ����� � ���������� 2�� ���-����� ������
            forest.push_front(firstAndSecondCombined);
        }

        Tree resultTree = *(forest.front());
        forest.pop_front();
        return resultTree;
    }
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

void Tree::saveInFile(string outputFileName) const
{
    ofstream fout;
    fout.open(outputFileName, ios::out);
    print(fout,0);
    fout.close();
}
