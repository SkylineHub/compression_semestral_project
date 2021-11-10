#include <ostream>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cmath>

using namespace std;

struct Node
{
    char key;
    int freq = 1;
    Node *parent = NULL;
    vector<Node *>child;
};

Node *newNode(char key)
{
    Node *temp = new Node;
    temp->key = key;
    return temp;
}

Node *newNode(char key, Node *parent)
{
    Node *temp = new Node;
    temp->key = key;
    temp->parent = parent;
    return temp;
}

void addValue(Node *root, char x) {
    bool firstLayer = true;
    int i;
    for (i = 0; i < root->child.size(); i++) {
        if (root->child[i]->key == x) {
            root->child[i]->freq += 1;
            firstLayer = false;
            break;
        }
    }
    if (firstLayer == true) {
        (root->child).push_back(newNode(x, root));
    }
}

void addValue(Node *root, char x, char y) {
    bool firstLayer = true;
    bool secondLayer = true;
    int i;
    int j;
    for (i = 0; i < root->child.size(); i++) {
        if (root->child[i]->key == x) {
            root->child[i]->freq += 1;
            firstLayer = false;
            break;
        }
    }
    if (firstLayer == true) {
        cout << x << endl;
        (root->child).push_back(newNode(x, root));
    }

    for (int j = 0; j < root->child[i]->child.size(); j++) {
        if (root->child[i]->child[j]->key == y) {
            root->child[i]->child[j]->freq += 1;
            secondLayer = false;
        }
    }
    if (secondLayer == true) {
        cout << y << endl;
        (root->child[i]->child).push_back(newNode(y, root->child[i]));
    }
}
void addValue(Node *root, char x, char y, char z) {
    bool firstLayer = true;
    bool secondLayer = true;
    bool thirdLayer = true;
    int i;
    int j;
    for (i = 0; i < root->child.size(); i++) {
        if (root->child[i]->key == x) {
            root->child[i]->freq += 1;
            firstLayer = false;
            break;
        }
    }
    if (firstLayer == true) {
        (root->child).push_back(newNode(x, root));
    }

    for (j = 0; j < root->child[i]->child.size(); j++) {
        if (root->child[i]->child[j]->key == y) {
            root->child[i]->child[j]->freq += 1;
            secondLayer = false;
            break;
        }
    }
    if (secondLayer == true) {
        (root->child[i]->child).push_back(newNode(y, root->child[i]));
    }

    for (int l = 0; l < root->child[i]->child[j]->child.size(); l++) {
        if(root->child[i]->child[j]->child[l]->key == z) {
            root->child[i]->child[j]->child[l]->freq += 1;
            thirdLayer = false;
            break;
        }
    }
    if(thirdLayer == true) {
        (root->child[i]->child[j]->child).push_back(newNode(z, root->child[i]->child[j]));
    }
}

void LevelOrderTraversal(Node * root)
{
    if (root==NULL)
        return;

    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();

        while (n > 0)
        {
            Node * p = q.front();
            q.pop();
            cout << p->key << "(" << (p->freq) << ")"; //<< " -> " << p->parent << " | ";

            for (int i=0; i<p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
        cout << endl;
    }
}

float getEntropy(Node * root) {
    float n = 0;
    float entropy = 0;
    float size = 0;
    for (int i = 0; i < root->child.size(); i++) {
        for (int j = 0; j < root->child[i]->child.size(); j++) {
            int parentFreq = root->child[i]->child[j]->freq;
            size += parentFreq;
            for (int l = 0; l < root->child[i]->child[j]->child.size(); l++) {
                float x = (float)root->child[i]->child[j]->child[l]->freq / (float)parentFreq;
                if (x == 1) {
                    continue;
                } else {
                    n += (float)root->child[i]->child[j]->child[l]->freq;
                    entropy -= x * log2(x);
                }

            }
        }
    }

    return (n/size) * entropy;
}

float getZeroOrderEntropy(Node * root, int size) {
    float entropy = 0;
    for (int i = 0; i < root->child.size(); i++) {
        float x = (float)root->child[i]->freq/(float)size;
        cout << x << endl;
        entropy -= x * log2(x);
    }

    return entropy;
}

int main()
{
    ifstream file("data.txt", std::ios::binary | std::ios::ate);
    streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size];

    Node *test = newNode('|');

    if(file.read(buffer, size)) {
        for (int i = 0; i < size; i++) {
            if (i < size - 2) {
                addValue(test, buffer[i], buffer[i+1], buffer[i+2]);
            }
            if (i == size - 2) {
                //addValue(test, buffer[i], buffer[i+1]);
            }
            if (i == size - 1) {
                //addValue(test, buffer[i]);
            }
        }
    }

    LevelOrderTraversal(test);

    cout << getEntropy(test) << endl;
    cout << getZeroOrderEntropy(test, size) << endl;

    return 0;
}
