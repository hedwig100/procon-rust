#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); i ++)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PL;
typedef pair<int,int> P;
const int INF = 1e9;
const ll MOD = 1e9 + 7;

//a,bの最大公約数を求める
template<class T> T gcd(T a,T b) {return (b ? gcd(b,a%b): a);}

//aのk乗根を求める
long long root_int(long long a,int k) {
    if (k == 0) return 0;
    long long x = pow(a,(double)1.0/k);
    while (pow(x,k) > a) x --;
    while (pow(x + 1,k) <= a) x ++;
    return x;
}

//ax + by = gcd(a,b)を満たすx,yを求める
long long x,y;
long long extGCD(long long a,long long b,long long &x,long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b,a%b,y,x);
    y -= a/b * x;
    return d;
}

// inverse 
long long modinv(long long a,long long MOD = MOD) {
    long long x,y;
    long long g = extGCD(a,MOD,x,y);
    if (g != 1) return -1;
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

// garner 
long long garner(vector<long long> &R,vector<long long> &M) {
    long long x = R[0]%M[0];
    long long prod = M[0];
    for (int i = 1;i < R.size();i ++) {
        long long t = ((R[i] - x) * modinv(prod,M[i])) % M[i];
        if (t < 0) t += M[i];
        x += t * prod;
        prod *= M[i];
    }
    return x;
}

// sieve
vector<int> sieve(int n) {
    vector<bool> prime(n + 1,true);
    prime[0] = false;
    prime[1] = false;
    for (int i = 3; i * i <= n; i += 2) {
        if (prime[i]) {
            int j = 2;
            while (i * j <= n) {
                prime[i * j] = false;
                j ++;
            }
        }
    }
    vector<int> ans = {2};
    for (int i = 3; i < n + 1; i += 2) {
        if (prime[i]) ans.push_back(i);
    }
    return ans; 
}

vector<pair<int,int>> factorization(long long N,vector<int>& primes) {
    vector<pair<int,int>> ret;
    for (int p:primes) {
        int power = 0;
        while (N%p == 0) {
            power ++;
            N /= p;
        }
        if (power > 0) ret.emplace_back(p,power);
    }
    if (N > 1) ret.emplace_back(N,1);
    return ret;
}

// osa_k
struct Sieve {
    int N;
    vector<int> min_factor;
    Sieve(int _N):N(_N) {
        min_factor.assign(N + 1,-1);
        int i = 2;
        for (; i*i <= N; ++i) {
            if (min_factor[i] < 0) {
                min_factor[i] = i;
                for (int p = i*i; p <= N; p += i) {
                    if (min_factor[p] < 0) min_factor[p] = i;
                }
            }
        }
        for (int j = i; j <= N; ++j) {
            if (min_factor[j] < 0) min_factor[j] = j;
        }
    }
    // M > 1 
    vector<pair<int,int>> factorization(int M) {
        vector<pair<int,int>> ret;
        while (M > 1) {
            int p = min_factor[M],e = 1;
            M /= p;
            while (p == min_factor[M]) {
                ++e;
                M /= p;
            }
            ret.emplace_back(p,e);
        }
        return ret;
    }
    int count_factor(int M) {
        int ans = 1;
        while (M > 1) {
            int p = min_factor[M],e = 1;
            M /= p;
            while (p == min_factor[M]) {
                ++e;
                M /= p;
            }
            ans *= (e + 1);
        }
        return ans;
    }
};