//1-based
struct Tarjan {
    static const int N = 100005;
    int dfn[N], scc[N], ord, cnt;
    vector<int> st, edge[N];
    void clear() {
        for (int i = 0; i < N; ++i) edge[i].clear();
    }
    void add_edge(int x, int y) {
        edge[x].push_back(y);
    }
    int dfs(int x) {
        dfn[x] = ++ord;
        int ret = ord;
        st.push_back(x);
        for (int i : edge[x]) {
            if (dfn[i] == 0) ret = min(ret, dfs(i));
            else if (scc[i] == 0) ret = min(ret, dfn[i]);
        }
        if (ret == dfn[x]) {
            ++cnt;
            while (1) {
                int i = st.back();
                st.pop_back();
                scc[i] = cnt;
                if (i == x) break;
            }
        }
        return ret;
    }
    int solve(int n) {
        memset(dfn, 0, sizeof(dfn));
        memset(scc, 0, sizeof(scc));
        ord = cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (dfn[i]) continue;
            dfs(i);
        }
        return cnt;
    }
};