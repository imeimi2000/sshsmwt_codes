using ull = unsigned long long;

#define get(A, x) ((A[(x) >> 6] >> ((x) & 63)) & 1)
#define set(A, x) (A[(x) >> 6] |= 1llu << ((x) & 63))
int lcs(string A, string B) {
    int n = A.size(), m = B.size();
    int sz = (m >> 6) + 1; // 64bit
    vector<ull> S[256];
    for (int i = 0; i < 256; ++i) S[i].resize(sz, 0);
    for (int i = 0; i < m; ++i) set(S[B[i]], i);
    vector<ull> R(sz, 0);
    for (int i = 0; i < m; ++i) if (A[0] == B[i]) {
        set(R, i);
        break;
    }
    for (int i = 1; i < n; ++i) {
        ull shl_carry = 1, sub_carry = 0;
        for (int j = 0; j < sz; ++j) {
            ull x = S[A[i]][j] | R[j];
            ull u = (R[j] << 1) | shl_carry;
            shl_carry = R[j] >> 63;
            auto get_carry = [](ull &x, ull y) {
                ull z = x;
                x -= y;
                return z < x;
            };
            ull v = x;
            sub_carry = get_carry(v, sub_carry);
            sub_carry += get_carry(v, u);
            R[j] = x & (x ^ v);
        }
        R[m >> 6] &= (1llu << (m & 63)) - 1llu;
    }
    int ret = 0;
    for (int i = 0; i < m; ++i) if (get(R, i)) ++ret;
    return ret;
}
#undef get
#undef set