//S[0..Z[i]-1] == S[i..i+Z[i]-1]
vector<int> Z_array(vector<int> S) {
    int n = S.size();
    int L = 0, R = 0;
    vector<int> Z(n, 0);
    for (int i = 1; i < n; ++i) {
        if (i > R) L = R = i;
        else {
            if (Z[i - L] < R - i + 1) {
                Z[i] = Z[i - L];
                continue;
            }
            L = i;
        }
        while (R < n && S[R - L] == S[R]) ++R;
        Z[i] = (R--) - L;
    }
    return Z;
}