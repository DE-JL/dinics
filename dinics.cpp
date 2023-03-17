#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v;
    int c, f;
};

struct Dinics {
    int n, m;
    int s, t;

    vector<vector<int>> adj;
    vector<edge> edges;
    vector<int> ptr, lvl;

    Dinics(int N, int M, int s, int t) : n(N), m(0), s(s), t(t) {
        adj.resize(N);
        ptr.resize(N);
        lvl.assign(N, 0);
        edges.resize(M);
    }

    void add_edge(int u, int v, int c) {
        adj[u].push_back(m);
        edges[m++] = {u, v, c, 0};

        adj[v].push_back(m);
        edges[m++] = {v, u, 0, 0};
    }

    void bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        lvl[s] = 0;

        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                int v = edges[id].v;
                int res = edges[id].c - edges[id].f;
                if (lvl[v] != -1 || !res) continue;
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
    }

    int dfs(int u, int pushed) {
        if (!pushed) return 0;
        if (u == t) return pushed;

        for (; ptr[u] < adj[u].size(); ++ptr[u]) {
            int id = adj[u][ptr[u]];
            int v = edges[id].v;
            int res = edges[id].c - edges[id].f;

            if (lvl[v] != lvl[u]+1 || !res) continue;

            int f = dfs(v, min(pushed, res));
            if (f) {
                edges[id].f += f;
                edges[id^1].f -= f;
                return f;
            }
        }
        return 0;
    }

    int max_flow() {
        int f = 0;
        while (lvl[t] != -1) {
            bfs();
            fill(ptr.begin(), ptr.end(), 0);
            while (int augmented = dfs(s, INT_MAX)) f += augmented;
        }
        return f;
    }
};


int main() {
    int V, E, s, t;
    cin >> V >> E >> s >> t;
    Dinics dinics(V, E, s, t);
    
    int u, v, c;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> c;
        dinics.add_edge(u, v, c);
    }
    
    cout << dinics.max_flow() << "\n";
}
