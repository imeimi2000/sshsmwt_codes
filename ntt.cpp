const int mod = 998244353;
const int proot = 3;

ll pw(ll x, ll p) {
    ll r = 1;
    while (p) {
        if (p & 1) r = r * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return r;
}

void ntt(vector<int> &P, bool rev) {
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
    ll a = pw(proot, (mod - 1) / n);
    if (rev) a = pw(a, mod - 2);
    vector<ll> R(n >> 1, 1);
    for (int i = 1; i + i < n; ++i) {
        R[i] = R[i - 1] * a % mod;
    }
    for (int i = 1, d = n >> 1; i < n; i <<= 1, d >>= 1) {
        for (int j = 0; j < n; j += i + i) {
            for (int k = 0; k < i; ++k) {
                base u = P[j + k], v = P[i + j + k] * R[d * k] % mod;
                P[j + k] = (u + v) % mod;
                P[i + j + k] = (u + mod - v) % mod;
            }
        }
    }
    if (rev) {
        ll r = pw(n, mod - 2);
        for (int i = 0; i < n; ++i) P[i] = P[i] * r % mod;
    }
}