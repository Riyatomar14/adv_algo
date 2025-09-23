#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class BTreeNode {
public:
    int order;   // maximum children per node
    int minKeys; // minimum keys per node = ceil(order/2) - 1
    bool isLeaf;
    vector<int> keys;
    vector<BTreeNode*> children;

    BTreeNode(int _order, bool _isLeaf)
        : order(_order), isLeaf(_isLeaf)
    {
        minKeys = (int)ceil(order / 2.0) - 1;
    }

    // insertion helpers you already have
    void insertNonFull(int key);
    void splitChild(int i);
    void traverse();

    // deletion helpers
    void remove(int key);
    int findKey(int key);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

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

    void insert(int key);
    void remove(int key);
    void traverse() {
        if (root) root->traverse();
    }

    ~BTree() {
        delete root;
    }
};

/////////////////// Implementation ///////////////////

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf)
            children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!isLeaf)
        children[i]->traverse();
}

void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(order, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == order - 1) {
            BTreeNode* s = new BTreeNode(order, false);
            s->children.push_back(root);
            s->splitChild(0);

            int i = 0;
            if (s->keys[0] < key)
                i++;
            s->children[i]->insertNonFull(key);

            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}

// Deletion from tree
void BTree::remove(int key) {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }

    root->remove(key);

    // If root has 0 keys now, adjust root
    if (root->keys.size() == 0) {
        BTreeNode* old = root;
        if (root->isLeaf) {
            // tree becomes empty
            root = nullptr;
        } else {
            // promote first child
            root = root->children[0];
        }
        delete old;
    }
}

int BTreeNode::findKey(int key) {
    // returns index of first key >= key
    int idx = 0;
    while (idx < keys.size() && keys[idx] < key)
        ++idx;
    return idx;
}

void BTreeNode::remove(int key) {
    int idx = findKey(key);

    if (idx < keys.size() && keys[idx] == key) {
        // key is present in this node
        if (isLeaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        // key not present here
        if (isLeaf) {
            // not found
            cout << "Key " << key << " not found in the tree\n";
            return;
        }

        bool flag = (idx == keys.size());  // true if key should be in last child

        // If the child where key would exist has only minKeys keys, fill it
        if (children[idx]->keys.size() <= minKeys) {
            // Try to borrow or merge
            if (idx > 0 && children[idx - 1]->keys.size() > minKeys) {
                borrowFromPrev(idx);
            }
            else if (idx < keys.size() && children[idx + 1]->keys.size() > minKeys) {
                borrowFromNext(idx);
            }
            else {
                if (idx < keys.size())
                    merge(idx);
                else
                    merge(idx - 1);
            }
        }
        // After ensuring, descend
        if (flag && idx > keys.size())  // this check is safe but usually idx == keys.size() only
            children[idx - 1]->remove(key);
        else
            children[idx]->remove(key);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    // Simply erase the key
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];

    // If preceding child has > minKeys keys, find predecessor
    if (children[idx]->keys.size() > minKeys) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    // Else if next child has > minKeys keys, find successor
    else if (children[idx + 1]->keys.size() > minKeys) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    // Else both children have minKeys, merge them
    else {
        merge(idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->isLeaf) {
        cur = cur->children.back();
    }
    return cur->keys.back();
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->isLeaf) {
        cur = cur->children.front();
    }
    return cur->keys.front();
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    // Move key from parent down to child
    child->keys.insert(child->keys.begin(), keys[idx - 1]);

    if (!child->isLeaf) {
        // Move sibling's last child as first child of child
        child->children.insert(child->children.begin(),
                               sibling->children.back());
        sibling->children.pop_back();
    }

    // Move sibling's last key up to parent
    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    // Move key from parent down to child
    child->keys.push_back(keys[idx]);

    if (!child->isLeaf) {
        // Move sibling's first child as last child of child
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }

    // Move sibling's first key up to parent
    keys[idx] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    // Pull down a key from parent
    child->keys.push_back(keys[idx]);

    // Append sibling's keys and children
    for (int i = 0; i < sibling->keys.size(); i++)
        child->keys.push_back(sibling->keys[i]);

    if (!child->isLeaf) {
        for (int i = 0; i < sibling->children.size(); i++)
            child->children.push_back(sibling->children[i]);
    }

    // Remove the key from parent
    keys.erase(keys.begin() + idx);
    // Remove sibling from children list
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

////////////////////////////////////////////////

// insertNonFull and splitChild remain as you had them

void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.insert(upper_bound(keys.begin(), keys.end(), key), key);
    } else {
        while (i >= 0 && key < keys[i])
            i--;
        i++;

        if (children[i]->keys.size() == order - 1) {
            splitChild(i);
            if (key > keys[i])
                i++;
        }
        children[i]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int i) {
    BTreeNode* y = children[i];
    BTreeNode* z = new BTreeNode(order, y->isLeaf);

    int mid = order / 2;

    // Move keys after mid to z
    z->keys.assign(y->keys.begin() + mid + 1, y->keys.end());
    y->keys.erase(y->keys.begin() + mid + 1, y->keys.end());

    // Move children if not leaf
    if (!y->isLeaf) {
        z->children.assign(y->children.begin() + mid + 1, y->children.end());
        y->children.erase(y->children.begin() + mid + 1, y->children.end());
    }

    // Insert new child into children
    children.insert(children.begin() + i + 1, z);
    // Move middle key up
    keys.insert(keys.begin() + i, y->keys[mid]);
    // Remove median from y
    y->keys.erase(y->keys.begin() + mid);
}

/////////////////////////////////////////////////////

int main() {
    int order = 5; // you can change order
    BTree t(order);

    vector<int> vals = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int v : vals)
        t.insert(v);

    cout << "Traversal before deletion: ";
    t.traverse();
    cout << "\n";

    // Test deletions
    t.remove(6);
    cout << "After removing 6: ";
    t.traverse();
    cout << "\n";

    t.remove(13);
    cout << "After removing 13 (not present): ";
    t.traverse();
    cout << "\n";

    t.remove(7);
    cout << "After removing 7: ";
    t.traverse();
    cout << "\n";

    return 0;
}
