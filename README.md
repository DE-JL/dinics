# Dinic's Algorithm $O(|V|^2 |E|)$
This is short implementation of Dinic's algorithm for computing maximum flows in integer-capacity directed graphs. Edges are stored in a small data structure:
```cpp
struct edge {
    int u; // departure vertex
    int v; // destination vertex
    int c; // capacity
    int f; // assigned flow
};
```
Edges are stored in an array and have a unique `id`. An adjacency list `adj` is used to store lists of IDs of edges outgoing from each vertex.

## $O(|V||E|)$ Blocking Flow
Computes a blocking flow by incrementally calling depth-first-search from the source. If no more paths can be augmented, a breadth-first-search is called to determine whether the sink $t$ has been disconnected from the source $s$.

### $O(|V| + |E|)$ BFS
Computes the shortest distances in the residual graph $G_f$ after the previous iteration of blocking flow. We keep an array `lvl` of size $|V|$ so that `lvl[v]` stores the distance from $s$ to $v$ in the residual graph.

### $O(|V| + k)$ DFS
Where $k$ is the number of edges marked dead in attempts to find augmenting paths. An array `ptr` of size $|V|$ is used: `ptr[v]` stores the ID of the next edge outgoing from $v$ to be considered in any DFS path. The pointer is incremented if no augmenting path is found, otherwise we immediately break and return the amount of flow we augmented by.

## $O(|V|)$ Blocking Flows
For every iteration of computing a blocking flow, we start a BFS and then repeatedly call DFS up to $|E|$ times. This process is repeated until $t$ is finally disconnected from $s$ in the residual graph. This can go for at most $O(|V|)$ iterations due to Dinic's lemma.
