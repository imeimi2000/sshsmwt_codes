struct Disjoint_Set {
    static const int N = 100005;
    int par[100005];
    int sz[100005];
    vector<int> op;
    void clear() {
        for (int i = 0; i < N; ++i) {
            par[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x) {
        if (par[x] != x) return find(par[x]);
        return x;
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return 0;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        op.push_back(y);
        return 1;
    }
    int version() {
        return op.size();
    }
    void restore() {
        int y = op.back();
        op.pop_back();
        int x = par[y];
        par[y] = y;
        sz[x] -= sz[y];
    }
};

//offline dynamic minimum spanning tree
struct Dynamic_MST {
    static const int N = 100005;
    struct edge {
        int x, y, c, s, e;
        bool operator<(const edge &p) const {
            return c < p.c;
        }
    };
    vector<edge> es;
    Disjoint_Set u;
    //edge x-y alive [s, e]
    void add_edge(int x, int y, int c, int s, int e) {
        es.push_back({ x, y, c, s, e });
    }
    void solve(int s, int e, vector<edge> maybe_mst, ll cost) {
        vector<edge> included;
        for (auto i : maybe_mst) {
            if (e < i.s || i.e < s) continue;
            included.push_back(i);
        }
        swap(included, maybe_mst);
        maybe_mst.clear();
        int t = u.version(), m = included.size();
        vector<int> check(m, 0);
        for (int i = 0; i < m; ++i) {
            if (included[i].s <= s && e <= included[i].e) continue;
            u.merge(included[i].x, included[i].y);
        }
        for (int i = 0; i < m; ++i) {
            if (included[i].s <= e && e <= included[i].e) {
                if (u.merge(included[i].x, included[i].y)) {
                    check[i] = 1;
                }
            }
        }
        while (t != u.version()) u.restore();
        for (int i = 0; i < m; ++i) {
            if (included[i].s <= e && e <= included[i].e) {
                if (!u.merge(included[i].x, included[i].y)) {
                    check[i] = 2;
                }
            }
        }
        while (t != u.version()) u.restore();
        for (int i = 0; i < m; ++i) {
            if (check[i] == 0) maybe_mst.push_back(included[i]);
            if (check[i] == 1) {
                u.merge(included[i].x, included[i].y);
                cost += included[i].c;
            }
        }
        if (s == e) {
            //TODO somthing
        }
        else {
            int m = s + e >> 1;
            solve(s, m, maybe_mst, cost);
            solve(m + 1, e, maybe_mst, cost);
        }
        while (t != u.version()) u.restore();
    }
    void solve(int t) {
        u.clear();
        sort(es.begin(), es.end());
        solve(1, t, es, 0);
    }
};