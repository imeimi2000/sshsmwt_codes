//1-based
struct Hopcroft_Karp {
    static const int N = 100005, M = 100005;
    vector<int> edge[N];
    int dis[N], mat[N], rev[M], vis[N];
    void clear() {
        for (int i = 0; i < N; ++i) edge[i].clear();
    }
    void add_edge(int x, int y) {
        edge[x].push_back(y);
    }
    bool bfs(int n) {
        queue<int> q;
        memset(dis, -1, sizeof(dis));
        for (int i = 1; i <= n; ++i) {
            if (mat[i] == -1 && dis[i] == -1) {
                q.push(i);
                dis[i] = 0;
            }
        }
        bool ret = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i : edge[x]) {
                if (rev[i] == -1) ret = 1;
                else if (dis[rev[i]] == -1) {
                    dis[rev[i]] = dis[x] + 1;
                    q.push(rev[i]);
                }
            }
        }
        return ret;
    }
    int dfs(int x) {
        vis[x] = 1;
        for (int i : edge[x]) {
            if (rev[i] == -1 || !vis[rev[i]] && dis[rev[i]] == dis[x] + 1 && dfs(rev[i])) {
                mat[x] = i;
                rev[i] = x;
                return 1;
            }
        }
        return 0;
    }
    int max_matching(int n, int m) {
        memset(mat, -1, sizeof(mat));
        memset(rev, -1, sizeof(rev));
        int ret = 0;
        while (bfs(n)) {
            memset(vis, 0, sizeof(vis));
            for (int i = 1; i <= n; ++i) {
                if (mat[i] == -1) ret += dfs(i);
            }
        }
        return ret;
    }
    bool ch[N + M];
    void rdfs(int x, int n) {
        ch[x] = 1;
        for (int i : edge[x]) {
            ch[i + n] = 1;
            if (!ch[rev[i]]) rdfs(rev[i], n);
        }
    }
    vector<int> min_cover(int n, int m) {
        max_matching(n, m);
        memset(ch, 0, sizeof(ch));
        for (int i = 1; i <= n; ++i) if (mat[i] == -1 && !ch[i])
            rdfs(i, n);
        vector<int> ret;
        for (int i = 1; i <= n + m; ++i) if ((i <= n) != ch[i])
            ret.push_back(i);
        return ret;
    }
};
