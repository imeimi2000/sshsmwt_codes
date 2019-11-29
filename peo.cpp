//1-based
struct PEO {
    static const int N = 100005;
    vector<int> edge[N];
    struct in_list {
        list<int> L;
        int vis;
    };
    list<in_list> all;
    list<in_list>::iterator out_pos[N];
    list<int>::iterator in_pos[N];
    unordered_set<int> adj[N];
    int ans[N], ord[N];
    bool vis[N];
    void clear() {
        for (int i = 0; i < N; ++i) {
            edge[i].clear();
            adj[i].clear();
        }
    }
    void add_edge(int x, int y) {
        edge[x].push_back(y);
        edge[y].push_back(x);
        adj[x].insert(y);
        adj[y].insert(x);
    }
    bool solve(int n) {
        memset(vis, 0, sizeof(vis));
        {
            list<int> l;
            for (int i = 1; i <= n; ++i) l.push_back(i);
            all.push_back({ l, 0 });
        }
        for (int i = 1; i <= n; ++i) out_pos[i] = all.begin();
        for (auto i = all.front().L.begin(); i != all.front().L.end(); ++i) in_pos[*i] = i;
        int cnt = 0;
        while (!all.empty()) {
            auto f = all.begin();
            if (f->L.empty()) {
                all.erase(f);
                continue;
            }
            int x = f->L.front();
            f->L.pop_front();
            ans[ord[x] = ++cnt] = x;
            vis[x] = 1;
            for (int i : edge[x]) {
                if (vis[i]) continue;
                auto it = out_pos[i];
                if (it->vis != cnt) {
                    list<int> add;
                    add.push_back(i);
                    all.insert(it, { add, 0 });
                    it->L.erase(in_pos[i]);
                    it->vis = cnt;
                    in_pos[i] = (--out_pos[i])->L.begin();
                }
                else {
                    it->L.erase(in_pos[i]);
                    (--out_pos[i])->L.push_back(i);
                    in_pos[i] = prev(out_pos[i]->L.end());
                }
            }
        }
        for (int x = 1; x <= n; ++x) {
            int mx = -1;
            for (int i : edge[x]) {
                if (ord[i] < ord[x]) mx = max(mx, ord[i]);
            }
            if (mx == -1) continue;
            int p = ans[mx];
            for (int i : edge[x]) {
                if (i != p && ord[i] < ord[x] && !adj[p].count(i)) return 0;
            }
        }
        return 1;
    }
};