vector<int> suffix_array(vector<int> S, int m) {
    int n = S.size(); // 1 <= S[i] <= m
    for (int i = 0; i < 3; ++i) S.push_back(0);
    if (n <= 2) {
        //TODO naive algorithm
    }
    vector<int> sa3;
    {
        vector<int> b3;
        for (int i = 0; i <= n; ++i) b3.push_back(i);
        for (int it = 3; it--; ) {
            vector<int> tp(n + 1, 0), cnt(m + 1, 0);
            for (int i : b3) ++cnt[S[i + it]];
            for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (int i = n + 1; i--; ) tp[--cnt[S[b3[i] + it]]] = b3[i];
            for (int i = 0; i <= n; ++i) b3[i] = tp[i];
        }
        vector<int> pord(n + 1);
        pord[b3[0]] = 1;
        for (int i = 1; i <= n; ++i) {
            int p = 0;
            for (int j = 0; j < 3; ++j) {
                int ac = S[b3[i - 1] + j], bc = S[b3[i] + j];
                if (ac != bc) {
                    p = 1;
                    break;
                }
            }
            pord[b3[i]] = pord[b3[i - 1]] + p;
        }
        vector<int> pstr;
        for (int i = 1; i <= n; i += 3) pstr.push_back(pord[i]);
        int sz3 = pstr.size();
        for (int i = 2; i <= n; i += 3) pstr.push_back(pord[i]);
        b3 = suffix_array(pstr, pord[b3[n]]);
        for (int i : b3) {
            int v = i < sz3 ? i * 3 + 1 : (i - sz3) * 3 + 2;
            if (v < n) sa3.push_back(v);
        }
    }
    vector<int> sa0;
    vector<int> ord3(n + 1, 0);
    for (int i = 0; i < (int)sa3.size(); ++i) ord3[sa3[i]] = i + 1;
    for (int i = 0; i < n; i += 3) sa0.push_back(i);
    {
        vector<int> cnt(n + 1, 0), tp(sa0.size());
        for (int i : sa0) ++cnt[ord3[i + 1]];
        for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
        for (int i = sa0.size(); i--; ) tp[--cnt[ord3[sa0[i] + 1]]] = sa0[i];
        cnt = vector<int>(m + 1, 0);
        for (int i : tp) ++cnt[S[i]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = sa0.size(); i--; ) sa0[--cnt[S[tp[i]]]] = tp[i];
    }
    vector<int> sa;
    for (int i = 0, j = 0; i < (int)sa3.size() || j < (int)sa0.size(); ) {
        bool B;
        if (i == (int)sa3.size()) B = 0;
        else if (j == (int)sa0.size()) B = 1;
        else {
            int a = sa3[i], b = sa0[j];
            B = a > b;
            for (int it = 0; max(a, b) + it < n; ++it) {
                if ((a + it) % 3 && (b + it) % 3) {
                    B = ord3[a + it] < ord3[b + it];
                    break;
                }
                if (S[a + it] != S[b + it]) {
                    B = S[a + it] < S[b + it];
                    break;
                }
            }
        }
        sa.push_back(B ? sa3[i++] : sa0[j++]);
    }
    return sa;
}

vector<int> lcp_array(vector<int> S, vector<int> sa) {
    int n = S.size();
    vector<int> ord(n), lcp(n);
    for (int i = 0; i < n; ++i) ord[sa[i]] = i;
    for (int i = 0, k = 0; i < n; ++i, k = max(k - 1, 0)) {
        int j = ord[i];
        if (!j) continue;
        int a, b;
        while (max(a = sa[j - 1] + k, b = sa[j] + k) < n && S[a] == S[b]) ++k;
        lcp[j] = k;
    }
    return lcp;
}