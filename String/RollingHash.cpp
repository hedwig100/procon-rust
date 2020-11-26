#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (int)(n); i ++)
#define irep(i,n) for (int i = (int)(n) - 1;i >= 0;--i)
using namespace std;
using ll = long long;
using PL = pair<ll,ll>;
using P = pair<int,int>;
constexpr int INF = 1000000000;
constexpr long long HINF = 1000000000000000;
constexpr long long MOD = 1000000007;// = 998244353;
constexpr double EPS = 1e-4;
constexpr double PI = 3.14159265358979;

using u64 = unsigned long long;
constexpr u64 M = 2305843009213693951; // 2^61 - 1
constexpr u64 MASK31 = 2147483647; // 2^31 - 1
constexpr u64 MASK30 = 1073741823; // 2^30 - 1
constexpr u64 POSITIVIZER = 4*M;

u64 CalcMod(u64 x) {
    u64 res = (x >> 61) + (x&M);
    if (res >= M) res -= M;
    return res;
}
u64 mul(u64 x,u64 y) {
    u64 au = (x >> 31),ad = (x&MASK31),bu = (y >> 31),bd = (y&MASK31);
    u64 m = au * bd + ad * bu;
    u64 mu = (m >> 30),md = (m&MASK30);
    u64 ans = ((au*bu)<<1) + mu + (md << 31) + ad*bd;
    return CalcMod(ans);
}

struct RollingHash {
    static u64 B;
    int N;
    vector<u64> hash,power;
    RollingHash(const string &s) {
        N = (int)s.size();
        hash.resize(N + 1,0); power.resize(N + 1,0);
        hash[0] = 0; power[0] = 1;
        for (int i = 0; i < (int)s.size(); ++i) {
            hash[i + 1] = CalcMod(mul(hash[i],B) + s[i]);
            power[i + 1] = mul(power[i],B);
        }
    }
    u64 get() {return hash[N];}
    u64 get(int k) {return hash[k];}
    u64 get(int l,int r) {return CalcMod(hash[r] + POSITIVIZER - mul(hash[l],power[r - l]));}
};

mt19937_64 mt;
uniform_int_distribution<unsigned long long> rng(2,M - 2);
unsigned long long RollingHash::B = rng(mt);










/*

// two 32bit MOD version 
struct RollingHash {
    using u64 = unsigned long long;
    static const u64 M1 = 2147483647,M2 = 1000000007;
    static u64 B1,B2;
    int N;
    vector<u64> hash1,hash2,power1,power2;

    RollingHash(string &s) {
        N = s.size();
        power1.resize(N + 1); power2.resize(N + 1); hash1.resize(N + 1); hash2.resize(N + 1);
        power1[0] = 1;        power2[0] = 1;        hash1[0] = 0;        hash2[0] = 0;
        for (int i = 0;i < N; ++i) {
            power1[i + 1] = power1[i] * B1 % M1;
            power2[i + 1] = power2[i] * B2 % M2;
            hash1[i + 1] = (hash1[i] * B1 + s[i]) % M1;
            hash2[i + 1] = (hash2[i] * B2 + s[i]) % M2;
        }
    }
    // return hash of S
    pair<u64,u64> get() {
        return make_pair(hash1[N],hash2[N]);
    }
    // return hash of S[0,k)
    pair<u64,u64> get(int k) {
        return make_pair(hash1[k],hash2[k]);
    }
    // return hash of S[l,r)
    pair<u64,u64> get(int l,int r) {
        u64 x = (hash1[r] - (hash1[l] * power1[r - l]) % M1 + M1) % M1;
        u64 y = (hash2[r] - (hash2[l] * power2[r - l]) % M2 + M2) % M2;
        return make_pair(x,y);
    }
    //return if S[l1,r1) == S[l2,r2)
    bool equal(int l1,int r1,int l2,int r2) {
        return get(l1,r1) == get(l2,r2);
    }
};

mt19937_64 mt;
uniform_int_distribution<unsigned long long> rand1(2,RollingHash::M1 - 2);
uniform_int_distribution<unsigned long long> rand2(2,RollingHash::M2 - 2);
unsigned long long RollingHash::B1 = rand1(mt);
unsigned long long RollingHash::B2 = rand2(mt);

using u64 = unsigned long long;
using Pu = pair<u64,u64>;

*/