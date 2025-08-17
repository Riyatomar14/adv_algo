#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent, sz;

void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]); // Path compression
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    parent.resize(n + 1);
    sz.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        make_set(i);

    vector< pair<int, pair<int, int>> > edges;

    cout << "Enter each edge as: u v w\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        // Optional: Validate node range
        if (u < 1 || u > n || v < 1 || v > n) {
            cout << "Invalid node number in edge " << u << " " << v << ". Skipping.\n";
            continue;
        }

        edges.push_back({w, {u, v}});
    }

    sort(edges.begin(), edges.end());

    int cost = 0;
    vector<pair<int, int>> mst;

    for (auto &edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (find_set(u) != find_set(v)) {
            mst.push_back({u, v});
            cost += w;
            union_sets(u, v);
        }
    }

    cout << "\nEdges in MST:\n";
    for (auto &e : mst)
        cout << e.first << " - " << e.second << "\n";

    cout << "Total cost: " << cost << "\n";
    return 0;
}
