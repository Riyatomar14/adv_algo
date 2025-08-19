#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent, sz;  // renamed size to sz

void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}

int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]); // path compression
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        
    }
}

int main() {
    int n = 4, m = 5;

    // Sample edges: {weight, {u, v}}
    vector< pair<int, pair<int, int>> > edges = {
        {1, {1, 2}},
        {4, {1, 3}},
        {2, {2, 3}},
        {5, {2, 4}},
        {3, {3, 4}}
    };

    parent.resize(n + 1);
    sz.resize(n + 1);

    for (int i = 1; i <= n; ++i)
        make_set(i);

    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end());

    vector<pair<int,int>> mst;
    int total_cost = 0;

    // Step 2 & 3: Build MST using Kruskal's Algorithm
    for (auto &edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (find_set(u) != find_set(v)) {
            union_sets(u, v);
            mst.push_back({u, v});
            total_cost += w;
        }
    }

    // Output MST edges and total cost
    cout << "Edges in MST:\n";
    for (auto &e : mst)
        cout << e.first << " - " << e.second << "\n";

    cout << "Total cost: " << total_cost << "\n";

    return 0;
}
