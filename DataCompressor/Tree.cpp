#include<tree.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<list>
#include<set>
using namespace std;
bool sortBySecond(const Tree* a,const Tree* b)
{
    return (a->getRootData().second < b->getRootData().second);
}

Node* Tree::copy(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return new Node(node->data, copy(node->left), copy(node->right));
}

void Tree::erase(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    erase(node->left);
    erase(node->right);
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
    erase(root);
}
bool Tree::empty()const
{
    return root == nullptr;
}
Tree Tree::left() const
{
    return Tree(root->left);
}

Tree Tree::right() const
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
    //стъпка 2 от построяване на дърво на Хъфман от описанието
    //създаваме n дървета от по един възел, който съдържа наредена двойка и ги записваме в списък,
    //като той е сортиран във низходяш
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
        Tree* fst = findMinNode(nodes);
        nodes.pop_front();//премахваме fst от списъка
        Tree* snd = findMinNode(nodes);
        nodes.pop_front();//премахваме snd от списъка
        Tree* res = new Tree(make_pair(' ',fst->getRootData().second + snd->getRootData().second), *fst, *snd);//строим ново дърво с поддървета 2те най-малки досега
        nodes.push_front(res);
    }
    //има само 1 възел в списъка и това е нашият корен

    Tree resultTree = *(nodes.front());
    nodes.pop_front();
    return resultTree;
}

void Tree::prettyPrint(ostream& out, int currentHeight) const
{
    if(empty())
        return;
    right().prettyPrint(out, currentHeight + 1);
    out<<setw(5*currentHeight)<<root->data.first<<root->data.second<<endl;
    left().prettyPrint(out, currentHeight + 1);
}
pair<char,int> Tree::enterPair(istream& in) const
{
    char c;
    int i;
    cout<<"\nsymbol: ";
    in>>c;
    if(c == '*')
        c = ' ';
    cout<<"\nsymbol frequency: ";
    in>>i;
    return make_pair(c,i);
}
void Tree::enterHelp(istream& in, Node*& curr)
{
    int answer;
    cout<<"stop 0/1 ";
    cin>>answer;
    if(answer == 1)
        return;
    pair<char,int> p = enterPair(in);
    cout<<p.first<<":"<<p.second<<"\n";
    curr = new Node(p);
    cout<<"\nleft of "<<curr->data.first<<curr->data.second<<" -> \n";
    enterHelp(in, curr->left);
    cout<<"\nright of "<<curr->data.first<<curr->data.second<<" -> \n";
    enterHelp(in, curr->right);
}
void Tree::enter(istream& in)
{
    cout<<"for nodes without symbols, set * as their symbol\n";
    enterHelp(in, root);
}
bool Tree::isMember(const char c) const
{
    if(empty())
        return false;
    if(root->data.first == c)
        return true;
    return left().isMember(c) || right().isMember(c);
}
pair<char, int> Tree::getRootData() const
{
    return root->data;
}

void Tree::save(string fname) const
{
    ofstream fout;
    fout.open(fname, ios::out);//изтрива всичко друго, което е имало преди във файла
    prettyPrint(fout,0);
    fout.close();
}

void Tree::getLeaves(list<char>& leaves) const
{
    if(root == nullptr)
    {
        return;
    }
    else if(root->left == nullptr && root->right == nullptr)
    {
        leaves.push_back(root->data.first);
        cout<<"leaves size"<<leaves.size();
        return;
    }
    left().getLeaves(leaves);
    right().getLeaves(leaves);
}
