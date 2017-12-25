#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <chrono>
using namespace std;

const int MAX_PROGRAMS = 1500;
const int MAX_CHILDREN = 10;
const int MAX_LINE_LENGTH = 1000;
const int MAX_PROGRAM_LENGTH = 10;
const char FILENAME[] = "input.txt";

int parseNum(const char* s)
{
    size_t len = strlen(s);
    int num = 0;
    for (size_t i = 0; i < len; i++)
    {
        num += (s[i] - '0') * static_cast<int>(pow(10, len - 1 - i));
    }
    return num;
}

int getProgramByName(const char programs[][MAX_PROGRAM_LENGTH], const int nPrograms, const char name[])
{
    for (int i = 0; i < nPrograms; i++)
        if (strcmp(programs[i], name) == 0)
            return i;
    return -1;
}

class Tree;

struct Node
{
    Node(Tree*, char*, int);
    char name[MAX_PROGRAM_LENGTH];
    int weight;
    void addChild(Node*);
    Tree* tree;
    Node* children[MAX_CHILDREN];
    int nChildren;
    bool hasParent;
};

Node::Node(Tree* tr, char* nm, int wt)
{
    tree = tr;
    strcpy(name, nm);
    weight = wt;
    nChildren = 0;
    hasParent = false;
}

void Node::addChild(Node* ptr)
{
    children[nChildren] = ptr;
    nChildren++;
}

class Tree
{
public:
    Tree();
    ~Tree();
    void display();
    Node* addNode(char*, int);
    Node* node(int);
    Node* node(char*);
    Node* root();
private:
    Node* m_programs[MAX_PROGRAMS];
    int m_nPrograms;
};

Tree::Tree()
{
    m_nPrograms = 0;
}

Tree::~Tree()
{
    for (int i = 0; i < m_nPrograms; i++)
        delete m_programs[i];
}

Node* Tree::addNode(char* nm, int wt = 0)
{
    Node* ptr = new Node(this, nm, wt);
    m_programs[m_nPrograms] = ptr;
    m_nPrograms++;
    return ptr;
}

Node* Tree::node(int key)
{
    if (key < m_nPrograms)
        return m_programs[key];
    return nullptr;
}

Node* Tree::node(char* nm)
{
    for (int i = 0; i < m_nPrograms; i++)
        if (strcmp(m_programs[i]->name, nm) == 0)
            return m_programs[i];
    return nullptr;
}

Node* Tree::root()
{
    for (int i = 0; i < m_nPrograms; i++)
        if (!m_programs[i]->hasParent)
            return m_programs[i];
    return nullptr;
}

void Tree::display()
{
    for (int i = 0; i < m_nPrograms; i++)
    {
        cout << m_programs[i]->name << ": " << m_programs[i]->weight << endl;
        if (m_programs[i]->nChildren)
        {
            for (int j = 0; j < m_programs[i]->nChildren; j++)
                cout << '\t' << m_programs[i]->children[j]->name << endl;
        }
    }
}

int totalWeight(Node* node, int weight = 0)
{
    weight += node->weight;
    if (node->nChildren)
        for (int i = 0; i < node->nChildren; i++)
            weight += totalWeight(node->children[i]);
    return weight;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    Tree* tree = new Tree;

    fstream stream;
    stream.open(FILENAME);
    if (stream.fail())
    {
        cout << "Couldn't open file" << endl;
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char* token;
    const char delimiters[] = " ()->,";
    int tokenCount;
    int programCount = 0;

    // add all the nodes
    while (stream.getline(line, MAX_LINE_LENGTH))
    {
        tokenCount = 0;
        token = strtok(line, delimiters);
        while (token != nullptr)
        {
            if (tokenCount == 0)
                tree->addNode(token);
            else if (tokenCount == 1)
                tree->node(programCount)->weight = parseNum(token);
            else
                break;

            token = strtok(nullptr, delimiters);
            tokenCount++;
        }
        programCount++;
    }

    stream.clear();
    stream.seekg(0, ios::beg);

    programCount = 0;

    // add children to nodes
    while (stream.getline(line, MAX_LINE_LENGTH))
    {
        tokenCount = 0;
        token = strtok(line, delimiters);
        while (token != nullptr)
        {
            if (tokenCount > 1)
            {
                Node* child = tree->node(token);
                tree->node(programCount)->addChild(child);
                child->hasParent = true;
            }

            token = strtok(nullptr, delimiters);
            tokenCount++;
        }
        programCount++;
    }

    stream.close();

    cout << tree->root()->name << endl;
    cout << totalWeight(tree->node("tknk")) << endl;

    delete tree;

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << elapsed.count() << endl;
}