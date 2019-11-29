vector<int> manacher_array(vector<int> _S) {
    int n = _S.size();
    vector<int> S(n + n - 1, -1);
    for (int i = 0; i < n; ++i) {
        S[i + i] = _S[i];
    }
    n = S.size();
    int p = 0, R = 0;
    vector<int> A(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i <= R) A[i] = min(A[p + p - i], R - i);
        while (i - A[i] > 0 && i + A[i] + 1 < n && S[i - A[i] - 1] == S[i + A[i] + 1]) ++A[i];
        if (R < i + A[i]) {
            R = i + A[i];
            p = i;
        }
    }
    return A;
}