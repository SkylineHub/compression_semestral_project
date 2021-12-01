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
    bool isLast = false;
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

Node *newNode(char key, Node *parent, bool isLast)
{
    Node *temp = new Node;
    temp->key = key;
    temp->parent = parent;
    temp->isLast = isLast;
    return temp;
}

Node* addValue(Node *root, char x) {
    int i;
    for (i = 0; i < root->child.size(); i++) {
        if (root->child[i]->key == x) {
            root->child[i]->freq += 1;
            return root->child[i];
        }
    }
    (root->child).push_back(newNode(x, root));
    return root->child[i];
}

Node* addValue(Node *root, char x, bool isLast) {
    int i;
    for (i = 0; i < root->child.size(); i++) {
        if (root->child[i]->key == x) {
            root->child[i]->freq += 1;
            root->child[i]->isLast = true;
            return root->child[i];
        }
    }
    (root->child).push_back(newNode(x, root, isLast));
    return root->child[i];
}

void setTree(Node *root, char a) {
    addValue(root, a, true);
}

void setTree(Node *root, char a, char b) {
    Node* i = addValue(root, a);
    addValue(i, b, true);
}

void setTree(Node *root, char a, char b, char c) {
    Node* i = addValue(root, a);
    Node* j = addValue(i, b);
    addValue(j, c, true);
}

void setTree(Node *root, char a, char b, char c, char d) {
    Node* i = addValue(root, a);
    Node* j = addValue(i, b);
    Node* l = addValue(j, c);
    addValue(l, d, true);
}

void setTree(Node *root, char a, char b, char c, char d, char e) {
    Node* i = addValue(root, a);
    Node* j = addValue(i, b);
    Node* l = addValue(j, c);
    Node* p = addValue(l, d);
    addValue(p, e, true);
}

void setTree(Node *root, char a, char b, char c, char d, char e, char f) {
    Node* i = addValue(root, a);
    Node* j = addValue(i, b);
    Node* l = addValue(j, c);
    Node* p = addValue(l, d);
    Node* q = addValue(p, e);
    addValue(q, f, true);
}

void setTree(Node *root, char a, char b, char c, char d, char e, char f, char g) {
    Node* i = addValue(root, a);
    Node* j = addValue(i, b);
    Node* l = addValue(j, c);
    Node* p = addValue(l, d);
    Node* q = addValue(p, e);
    Node* m = addValue(q, f);
    addValue(m, g);
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
            cout << p->key << "(" << (p->freq) << ")" << "(" << (p->isLast) << ")"; //<< " -> " << p->parent << " | ";

            for (int i=0; i<p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }
        cout << endl;
    }
}

void getEntropy(Node * root, int k, double *entropy, long *counts, long *sizes){
    for (int j = 0; j < root->child.size(); j++) {
        sizes[k] += root->child[j]->freq;
        if (root->child[j]->freq != root->freq) {
            counts[k] += root->child[j]->freq;
            double x;
            if (root->isLast) {
                x = (double) root->child[j]->freq / ((double) root->freq - 1.0);
            } else {
                x = (double) root->child[j]->freq / (double) root->freq;
            }
            entropy[k] -= x * log2(x);
        }
        if(k+1 != 7){
            getEntropy(root->child[j], k+1, entropy, counts, sizes);
        }
    }
}

float getEntropyKth(Node * root, int k) {
    if(k < 1 || k > 7) {
        cout << "Mimo rozsah!" << endl;
        return 0;
    }
    k = k - 1;
    int newK = 0;

    double entropy[7];
    long counts[7];
    long sizes[7];

    for (int i = 0; i < 7; i++) {
        sizes[i] = 0;
        counts[i] = 0;
        entropy[i] = 0;
    }

    for (int i = 0; i < root->child.size(); i++) {
        getEntropy(root->child[i], newK, ref(entropy), ref(counts), ref(sizes));
    }

    for (int i = 0; i < 7; i++) {
        cout << "K: " << i + 1 << endl;
        cout << "Velikost: " << sizes[i] << endl;
        cout << "Počet: " << counts[i] << endl;
        cout << "Entropy: " << entropy[i] << endl;
        if(sizes[i] != 0) {
            cout << "Výsledek: " << ((double)counts[i] / (double)sizes[i]) * entropy[i] << endl;
        }
    }

    return ((double)counts[k] / (double)sizes[k]) * entropy[k];
}

float getZeroOrderEntropy(Node * root, int size) {
    float entropy = 0;
    for (int i = 0; i < root->child.size(); i++) {
        float x = (float)root->child[i]->freq/(float)size;
        entropy -= x * log2(x);
    }

    return entropy;
}

int main()
{
    ifstream file("data.txt", std::ios::binary | std::ios::ate);
    //GM24385.bnx
    //data.txt
    streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size];

    Node *root = newNode('|');

    if(file.read(buffer, size)) {
        int i = 0;
        for (i = 0; i < size; i++) {
            /*
            cout <<"I: " << i << endl;
            if (buffer[i] == '\n' && buffer[i+1] != '#') {
                cout << "Done" << endl;
                break;
            }
            cout << buffer[i] << endl;
            */
            if (i < size - 6) {
                setTree(root, buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4], buffer[i+5], buffer[i+6]);
            }
            if (i == size - 6) {
                setTree(root, buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4], buffer[i+5]);
            }
            if (i == size - 5) {
                setTree(root, buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4]);
            }
            if (i == size - 4) {
                setTree(root, buffer[i], buffer[i+1], buffer[i+2], buffer[i+3]);
            }
            if (i == size - 3) {
                setTree(root, buffer[i], buffer[i+1], buffer[i+2]);
            }
            if (i == size - 2) {
                setTree(root, buffer[i], buffer[i+1]);
            }
            if (i == size - 1) {
                setTree(root, buffer[i]);
            }
        }

        /*
        int x = 0;
        for (int j = i; j < i + 20000; j++) {
            cout << buffer[j];
            if(buffer[j] == '\t') {
                cout << endl;
                x++;
                cout << x << ": ";
            }
            if(buffer[j] == '\n') {
                cout << endl;
                cout << "New line" << endl;
                cout << endl;
                x = 0;
            }
        }
         */
    }
    cout << "Tree completed." << endl;
    //LevelOrderTraversal(root);
    int k = 3;
    float entropy = getEntropyKth(root, k);
    cout << "Kth entropy comepleted." << endl;
    cout << "Zero order entropy: " << getZeroOrderEntropy(root, size) << endl;
    cout << k << "th order entropy: " << entropy << endl;
    return 0;
}
