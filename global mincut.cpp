//1-based
struct Stoer_Wagner {
    static const int N = 505;
    ll edge[N][N], dist[N], ans;
    bool vis[N];
    void clear() {
        memset(edge, 0, sizeof(edge));
    }
    void add_edge(int s, int e, ll c) {
        edge[s][e] = edge[e][s] = c;
    }
    pair<int, int> minimum_cut_phase(int n) {
        memset(dist, 0, sizeof(dist));
        ll ret = 1e18;
        int s, e;
        while (1) {
            int x = 0;
            ll val = -1e18;
            for (int i = 1; i <= n; ++i) {
                if (vis[i]) continue;
                if (val < dist[i]) {
                    val = dist[i];
                    x = i;
                }
            }
            if (x == 0) break;
            s = e;
            e = x;
            ret = val;
            vis[x] = 1;
            for (int i = 1; i <= n; ++i) {
                if (vis[i]) continue;
                dist[i] += edge[x][i];
            }
        }
        ans = min(ans, ret);
        return pair<int, int>(s, e);
    }
    ll minimum_cut(int n) {
        if (n <= 1) return 0;
        memset(vis, 0, sizeof(vis));
        ans = 1e18;
        for (int i = 1; i < n; ++i) {
            int s, e;
            tie(s, e) = minimum_cut_phase(n);
            vis[e] = 1;
            for (int j = 1; j <= n; j++) {
                if (vis[j]) continue;
                edge[s][j] += edge[e][j];
                edge[j][s] += edge[j][e];
            }
            edge[s][s] = 0;
        }
        return ans;
    }
};