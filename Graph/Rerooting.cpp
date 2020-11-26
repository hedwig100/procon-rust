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

struct DP {
    int dp;
    DP(int dp = 1):dp(dp) {}
    DP operator+(const DP &a) const { // merge function
        return DP(dp + a.dp);
    }
    DP addroot() const { // g = g(f(dp_0,dp_1,...,dp_N),v) : add root
        return DP(dp + 1);
    }
};
DP unit = DP(); // unit

template<class T>
struct Rerooting {
    int N;
    vector<int> parents;
    vector<vector<int>> G;
    vector<vector<T>> dp;
    vector<T> ans;
    Rerooting(int N,const vector<vector<int>> &G):N(N),G(G) {
        parents.assign(N,-1);
        dp.resize(N);
        ans.resize(N);
        dfs(0); 
        bfs(0);
    }
    T dfs(int v,int p = -1) {
        T ret = unit;
        dp[v] = vector<T>(G[v].size());
        for (int i = 0;i < (int)G[v].size(); ++i) {
            if (p == G[v][i]) {
                parents[v] = i;
                continue;
            }
            dp[v][i] = dfs(G[v][i],v);
            ret = ret + dp[v][i];
        }
        return ret.addroot();
    } 
    void bfs(int v,const T &res_p = unit,int p = -1) {
        if (p != -1) dp[v][parents[v]] = res_p;
        int deg = G[v].size();
        vector<T> dpl(deg + 1),dpr(deg + 1);
        dpl[0] = unit; dpr[deg] = unit;
        for (int i = 0;i < deg; ++i) dpl[i + 1] = dpl[i] + dp[v][i];
        for (int i = deg - 1; i >= 0; --i) dpr[i] = dpr[i + 1] + dp[v][i];
        ans[v] = dpr[0].addroot();
        for (int i = 0;i < deg; ++i) {
            if (parents[v] == i) continue;
            T d = dpl[i] + dpr[i + 1];
            bfs(G[v][i],d.addroot(),v);
        }
    }
    T operator[](int k) {
        return ans[k];
    }
};