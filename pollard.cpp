//#include <bits/stdc++.h>
//using namespace std;
namespace PRIME{
    using ll = long long;
    ll mpow(ll x, ll n, ll mod){
        ll ret = 1, pv = x % mod;
        for(;n;n>>=1){
            if(n & 1) ret = __int128(ret) * x % mod;
            x = __int128(x) * x % mod;
        }
        return ret;
    }
    const vector<ll> P({2,3,5,7,11,13,17,19,23,29,31,37});
    bool isprime(ll x){
        for(ll u : P) if(x == u) return true;
        if(x == 1 || !(x & 1)) return false;
        ll d = x-1, s = 0, pv;
        for(;~d&1;++s) d>>=1;
        for(ll u : P){
            pv = mpow(u, d, x);
            if(pv == 1 || pv == x-1) goto avoid;
            for(int i = 0; i < s-1; i++){
                pv = __int128(pv) * pv % x;
                if(pv == x-1) goto avoid;
            }
            return false;
            avoid: continue;
        }
        return true;
    }
    __int128 g1(__int128 x){
        return x*x+1;
    }
    __int128 g2(__int128 x){
        return x*x+2;
    }
    __int128 g3(__int128 x){
        return x*x+x-1;
    }
    function<__int128(__int128)> f[3] = {g1,g2,g3};
    vector<ll> pollard_rho(ll X){ //obtains all prime divisors of X removing multiplicity.
        vector<ll> ret;
        if(!(X & 1)){
            ret.push_back(2);
            while(!(X&1)) X >>= 1;
        }
        if(X == 1) return ret;
        if(isprime(X)){
            ret.push_back(X);
            return ret;
        }

        for(int i = 0; i < 3; i++){
            ll x = 2, y = 2, g = 1;
            while(g == 1){
                x = f[i](x) % X;
                y = f[i](f[i](y) % X) % X;
                g = gcd(abs(x-y), X);
            }
            if(g < X){
                vector<ll> d1 = pollard_rho(g);
                vector<ll> d2 = pollard_rho(X/g);
                copy(d1.begin(),d1.end(), back_inserter(ret));
                copy(d2.begin(),d2.end(), back_inserter(ret));
                break;
            }
        }
        sort(ret.begin(),ret.end()); ret.erase(unique(ret.begin(),ret.end()), ret.end());
        return ret;
    }
    vector<ll> pollard_rho_full(ll X){ //obtains all prime divisors of X with full multiplicity
        vector<ll> ret;
        for(;!(X&1);X >>= 1){
            ret.push_back(2);
        }
        if(X == 1) return ret;
        if(isprime(X)){
            ret.push_back(X);
            return ret;
        }

        for(int i = 0; i < 3; i++){
            ll x = 2, y = 2, g = 1;
            while(g == 1){
                x = f[i](x) % X;
                y = f[i](f[i](y) % X) % X;
                g = gcd(abs(x-y), X);
            }
            if(g < X){
                vector<ll> d1 = pollard_rho(g);
                vector<ll> d2 = pollard_rho(X/g);
                copy(d1.begin(),d1.end(), back_inserter(ret));
                copy(d2.begin(),d2.end(), back_inserter(ret));
                break;
            }
        }
        sort(ret.begin(),ret.end());
        return ret;
    }
}