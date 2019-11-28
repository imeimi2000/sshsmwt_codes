struct Dinic {
    static const int N = 505;
    struct _edge {
        int pos, rev;
        ll cap;
    };
    vector<_edge> edge[N];
    void clear() {
        for (int i = 0; i < N; ++i) edge[i].clear();
    }
    void add_edge(int s, int e, ll c) {
        edge[s].push_back({e, (int)edge[e].size(), c});
        edge[e].push_back({s, (int)edge[s].size() - 1, 0});
    }
    int dis[N], itr[N];
    bool bfs(int src, int sink) {
        memset(dis, -1, sizeof(dis));
        memset(itr, 0, sizeof(itr));
        queue<int> q;
        dis[src] = 0;
        q.push(src);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto i : edge[x]) {
                if (i.cap > 0 && dis[i.pos] == -1) {
                    dis[i.pos] = dis[x] + 1;
                    q.push(i.pos);
                }
            }
        }
        return dis[sink] != -1;
    }
    ll dfs(int x, int sink, ll flow) {
        if (x == sink) return flow;
        for (int &it = itr[x]; it < (int)edge[x].size(); ++it) {
            auto i = edge[x][it];
            if (i.cap > 0 && dis[i.pos] == dis[x] + 1) {
                ll ret = dfs(i.pos, sink, min(flow, i.cap));
                if (ret > 0) {
                    edge[x][it].cap -= ret;
                    edge[i.pos][i.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    ll get_flow(int src, int sink) {
        ll ret = 0;
        while (bfs(src, sink)) {
            ll flow;
            while ((flow = dfs(src, sink, 1e18)) > 0) ret += flow;
        }
        return ret;
    }
};
