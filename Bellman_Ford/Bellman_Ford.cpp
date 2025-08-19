#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, w;
};

void BellmanFord(int V, int E, vector<Edge> &edges, int src) {
    const int INF = 1000000000;
    vector<int> dist(V, INF);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "Graph contains a negative weight cycle!" << endl;
            return;
        }
    }

    cout << "Vertex   Distance from Source\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            cout << i << "\tINF\n";
        else
            cout << i << "\t\t\t\t" << dist[i] << "\n";
    }
}

int main() {
    int V = 5;
    int E = 8;
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    int src = 0;

    BellmanFord(V, E, edges, src);

    return 0;
}
    // Print result
    cout << "Vertex   Distance from Source\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            cout << i << "\t" << "INF" << endl;
        else
            cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    BellmanFord(V, E, edges, src);

    return 0;
}
