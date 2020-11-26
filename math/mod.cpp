#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); i ++)
using namespace std;
using ll = long long;
using PL = pair<ll,ll>;
using P = pair<int,int>;
constexpr int INF = 1000000000;
constexpr long long HINF = 1000000000000000;
constexpr long long MOD = 1000000007;// = 998244353;
constexpr double EPS = 1e-4;
constexpr double PI = 3.14159265358979;


template<int Modulus> 
struct ModInt {
    long long x;
    ModInt(long long x = 0) :x((x%Modulus + Modulus)%Modulus) {}
    constexpr ModInt &operator+=(const ModInt a) {if ((x += a.x) >= Modulus) x -= Modulus; return *this;}
    constexpr ModInt &operator-=(const ModInt a) {if ((x += Modulus - a.x) >= Modulus) x -= Modulus; return *this;}
    constexpr ModInt &operator*=(const ModInt a) {(x *= a.x) %= Modulus; return *this;}
    constexpr ModInt &operator/=(const ModInt a) {return *this *= a.inverse();}

    constexpr ModInt operator+(const ModInt a) const {return ModInt(*this) += a.x;}
    constexpr ModInt operator-(const ModInt a) const {return ModInt(*this) -= a.x;}
    constexpr ModInt operator*(const ModInt a) const {return ModInt(*this) *= a.x;}
    constexpr ModInt operator/(const ModInt a) const {return ModInt(*this) /= a.x;}
    
    friend constexpr ostream& operator<<(ostream& os,const ModInt<Modulus>& a) {return os << a.x;}
    friend constexpr istream& operator>>(istream& is,ModInt<Modulus>& a) {return is >> a.x;}
    
    ModInt inverse() const {// x ^ (-1) 
        long long a = x,b = Modulus,p = 1,q = 0;
        while (b) {long long d = a/b; a -= d*b; swap(a,b); p -= d*q; swap(p,q);}
        return ModInt(p);
    }
    ModInt pow(long long N) {// x ^ N 
        ModInt a = 1;
        while (N) {
            if (N&1) a *= *this;
            *this *= *this;
            N >>= 1;
        }
        return a;
    }
};

using mint = ModInt<1000000007>;
//using mint = ModInt<998244353>;
struct Combination {
    int N;
    //using mint = ModInt<1000000007>;
    //using mint = ModInt<998244353>;
    vector<mint> fact,ifact,invs;
    Combination(int N): N(N) {
        fact.resize(N + 1); ifact.resize(N + 1);
        fact[0] = fact[1] = 1;
        ifact[0] = ifact[1] = 1;
        for (int i = 2;i < N + 1;++i) {fact[i] = fact[i - 1] * i;}
        ifact[N] = fact[N].inverse();
        for (int i = N;i >= 1;--i) {ifact[i - 1] = ifact[i] * i;}
    }
    void invs_build() {
        invs.resize(N + 1);
        invs[1] = 1;
        for (int i = 2;i < N + 1;++i) invs[i] = fact[i] * ifact[i - 1];
    }
    mint operator()(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n]*ifact[k]*ifact[n - k];
    }
    mint npk(int n,int k) {
        if (k < 0 || k > n) return 0;
        return fact[n]*ifact[n - k];
    }
};

mint nck_nbig(long long n,int k) {
    mint ans = 1;
    for (int i = 0;i < k;++i) ans *= mint(n - i);
    for (int i = 1;i < k + 1;++i) ans *= mint(i).inverse();
    return ans;
}

long long modpow(long long N,long long K,long long mod = MOD) {
    long long ret = 1;
    while (K > 0) {
        if (K&1) {
            ret *= N;
            ret %= mod;
        }
        K >>= 1;
        N *= N;
        N %= mod;
    }
    return ret;
}

long long inverse(long long N,long long mod = MOD) {
    long long a = N,b = mod,p = 1,q = 0;
    while (b) {long long d = a/b; a -= d*b; swap(a,b); p -= d*q; swap(p,q);}
    return p;
}