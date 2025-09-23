#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class BTreeNode {
public:
    int order;                  // Max children per node
    int minKeys;                // Minimum keys = ceil(order/2) - 1
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;

    BTreeNode(int _order, bool _leaf) : order(_order), leaf(_leaf) {
        minKeys = (int)ceil(order / 2.0) - 1;
    }

    void insertNonFull(int k);
    void splitChild(int i);
    void traverse();

    ~BTreeNode() {
        for (auto c : children)
            delete c;
    }
};

class BTree {
public:
    BTreeNode* root;
    int order;

    BTree(int _order) : root(nullptr), order(_order) {}

    void insert(int k);
    void traverse() {
        if (root) root->traverse();
    }

    ~BTree() {
        delete root;
    }
};

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < (int)keys.size(); i++) {
        if (!leaf)
            children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!leaf)
        children[i]->traverse();
}

void BTreeNode::insertNonFull(int k) {
    int i = (int)keys.size() - 1;

    if (leaf) {
        keys.insert(std::upper_bound(keys.begin(), keys.end(), k), k);
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        i++;

        if ((int)children[i]->keys.size() == order - 1) {
            splitChild(i);
            if (keys[i] < k)
                i++;
        }
        children[i]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i) {
    BTreeNode* y = children[i];
    BTreeNode* z = new BTreeNode(order, y->leaf);

    int midIndex = order / 2;  // Middle key index

    // Move keys after midIndex to z
    z->keys.assign(y->keys.begin() + midIndex + 1, y->keys.end());
    y->keys.erase(y->keys.begin() + midIndex, y->keys.end());

    // Move children if not leaf
    if (!y->leaf) {
        z->children.assign(y->children.begin() + midIndex + 1, y->children.end());
        y->children.erase(y->children.begin() + midIndex + 1, y->children.end());
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[midIndex]);
    y->keys.erase(y->keys.begin() + midIndex);
}

void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(order, true);
        root->keys.push_back(k);
    } else {
        if ((int)root->keys.size() == order - 1) {
            BTreeNode* s = new BTreeNode(order, false);
            s->children.push_back(root);
            s->splitChild(0);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

int main() {
    int order = 5; // Example order of B-tree
    BTree t(order);

    vector<int> vals = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int v : vals) {
        t.insert(v);
    }

    cout << "Traversal of B-tree: ";
    t.traverse();
    cout << endl;

    return 0;
}
