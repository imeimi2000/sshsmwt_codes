struct MCMF {
    static const int N = 105;
    struct _edge {
        int pos, cap, rev;
        ll cost;
    };
    vector<_edge> edge[N];
    void clear() {
        for (int i = 0; i < N; ++i) edge[i].clear();
    }
    void add_edge(int s, int e, int c, ll v) {
        edge[s].push_back({e, c, (int)edge[e].size(), v});
        edge[e].push_back({s, 0, (int)edge[s].size() - 1, -v});
    }
    ll dis[N];
    int pav[N], pae[N];
    bool in[N];
    bool spfa(int src, int sink) {
        memset(dis, 0x3f, sizeof(dis));
        memset(in, 0, sizeof(in));
        queue<int> q;
        dis[src] = 0;
        in[src] = 1;
        q.push(src);
        bool ret = 0;
        while (!q.empty()) {
            int x = q.front(); in[x] = false;
            q.pop();
            if (x == sink) ret = 1;
            for (int it = 0; it < (int)edge[x].size(); ++it) {
                auto i = edge[x][it];
                if (i.cap > 0 && dis[x] + i.cost < dis[i.pos]) {
                    dis[i.pos] = dis[x] + i.cost;
                    pav[i.pos] = x;
                    pae[i.pos] = it;
                    if (!in[i.pos]) {
                        in[i.pos] = 1;
                        q.push(i.pos);
                    }
                }
            }
        }
        return ret;
    }
    ll get_cost(int src, int sink) {
        ll ret = 0;
        while (spfa(src, sink)) {
            int cap = 1e9;
            for (int pos = sink; pos != src; pos = pav[pos]) {
                cap = min(cap, edge[pav[pos]][pae[pos]].cap);
            }
            ret += dis[sink] * cap;
            for (int pos = sink; pos != src; pos = pav[pos]) {
                int rev = edge[pav[pos]][pae[pos]].rev;
                edge[pav[pos]][pae[pos]].cap -= cap;
                edge[pos][rev].cap += cap;
            }
        }
        return ret;
    }
};
