# Spanning Tree and Minimum Spanning Tree

## Spanning Tree

A **spanning tree** of a graph is a subset of edges that connects all
the vertices together without forming any cycle.\
If a graph has **V vertices**, then every spanning tree will have
exactly **V - 1 edges**.

------------------------------------------------------------------------

## Minimum Spanning Tree (MST)

A **Minimum Spanning Tree (MST)** is a spanning tree with the minimum
possible total edge weight.\
It is widely used in network design, clustering, and approximation
algorithms.

### Popular Algorithms to find MST:

1.  **Kruskal's Algorithm**
2.  **Prim's Algorithm**

------------------------------------------------------------------------

## Kruskal's Algorithm -- Pseudocode

1.  Sort the edges in increasing order of their weights.
2.  Iterate through the sorted edges:
    -   If inclusion of the current edge creates a cycle, skip it.
    -   Otherwise, include the edge in the MST.

------------------------------------------------------------------------

## Complexity Analysis

-   **Time Complexity**: O(E log V)
-   **Space Complexity**: O(E + V)

------------------------------------------------------------------------

### Example Applications

-   Network design (telephone, electrical, water supply)
-   Approximation algorithms for NP-hard problems
-   Clustering in Machine Learning
