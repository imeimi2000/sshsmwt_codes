using base = complex<double>;

void xor_conv(vector<base> &P, bool rev) {
    int n = P.size();
    auto bit_rev = [=](int x) {
        int ret = 0, bit = n;
        while (bit >>= 1) {
            ret = ret << 1 | (x & 1);
            x >>= 1;
        }
        return ret;
    };
    for (int i = 0; i < n; ++i) {
        int j = bit_rev(i);
        if (i < j) swap(P[i], P[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i + i) {
            for (int k = 0; k < i; ++k) {
                base u = P[j + k], v = P[i + j + k];
                P[j + k] = u + v;
                P[i + j + k] = u - v;
            }
        }
    }
    if (rev) {
        for (int i = 0; i < n; ++i) P[i] /= n;
    }
}