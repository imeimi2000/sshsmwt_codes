vector<int> get_failure(vector<int> B) {
    int n = B.size();
    vector<int> R(n, 0);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && B[i] != B[j]) j = R[j - 1];
        if (B[i] == B[j]) R[i] = ++j;
    }
    return R;
}

vector<int> kmp(vector<int> A, vector<int> B) {
    vector<int> P = get_failure(B), R;
    int n = A.size(), m = B.size();
    for (int i = 0, j = 0; i < n; ++i) {
        while (j && A[i] != B[j]) j = P[j - 1];
        if (A[i] == B[j]) {
            if (j + 1 == m) R.push_back(i - j), j = P[j];
            else ++j;
        }
    }
    return R;
}