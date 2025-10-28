#include <bits/stdc++.h>
using namespace std;

class SuffixTrie {
private:
    struct Node {
        unordered_map<char, Node*> next;
        vector<int> indices;

        ~Node() {
            for (auto& p : next) {
                delete p.second;
            }
        }
    };

    Node* root;
    string text;

public:
    // Constructor
    explicit SuffixTrie(const string& s)
        : root(new Node()), text(s) {}

    // Destructor
    ~SuffixTrie() {
        delete root;
    }

    // Build the suffix trie (brute-force: insert all suffixes)
    void build() {
        for (int i = 0; i < static_cast<int>(text.size()); ++i) {
            insertSuffix(i);
        }
    }

    // Search for a pattern in the trie
    // Return a vector of starting indices where the pattern appears
    vector<int> search(const string& pattern) const {
        const Node* cur = root;
        for (char c : pattern) {
            auto it = cur->next.find(c);
            if (it == cur->next.end()) {
                return {}; // pattern not found
            }
            cur = it->second;
        }
        // Return all indices stored in the node corresponding to the pattern
        return cur->indices;
    }

    // Print all stored paths and indices (for debugging)
    void printAllPaths() const {
        string path;
        printDFS(root, path);
    }

private:
    // Insert a suffix starting from index `start`
    void insertSuffix(int start) {
        Node* cur = root;
        for (int i = start; i < static_cast<int>(text.size()); ++i) {
            char c = text[i];
            if (cur->next.find(c) == cur->next.end()) {
                cur->next[c] = new Node();
            }
            cur = cur->next[c];
            cur->indices.push_back(start);
        }
    }

    // Helper: recursively print trie contents
    void printDFS(const Node* node, string& path) const {
        if (!node) return;

        if (!path.empty()) {
            cout << "\"" << path << "\" -> positions: ";
            for (size_t i = 0; i < node->indices.size(); ++i) {
                if (i) cout << ", ";
                cout << node->indices[i];
            }
            cout << '\n';
        }

        for (const auto& p : node->next) {
            path.push_back(p.first);
            printDFS(p.second, path);
            path.pop_back();
        }
    }
};

// Example usage
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string text = "banana";
    SuffixTrie trie(text);
    trie.build();

    cout << "Built suffix trie for \"" << text << "\"\n\n";

    cout << "All paths stored in the trie:\n";
    trie.printAllPaths();
    cout << '\n';

    const vector<string> patterns = {"ana", "nan", "ban", "a", "n", "xyz"};
    for (const string& pat : patterns) {
        vector<int> occ = trie.search(pat);
        cout << "Pattern \"" << pat << "\": ";
        if (occ.empty()) {
            cout << "not found\n";
        } else {
            cout << "found at positions [";
            for (size_t i = 0; i < occ.size(); ++i) {
                if (i) cout << ", ";
                cout << occ[i];
            }
            cout << "]\n";
}
