#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); i ++)
using namespace std;
using ll = long long;
using PL = pair<ll,ll>;
using P = pair<int,int>;
constexpr int INF = 1000000000;
constexpr long long HINF = 1000000000000000;
constexpr long long MOD = 1000000007;
constexpr double EPS = 1e-4;
constexpr double PI = 3.14159265358979;

struct LowLink {
    int N;
    vector<vector<int>> G;
    vector<int> low,ord,articulation;
    vector<P> bridge;

    LowLink(int N, vector<vector<int>> &G): N(N),G(G) {
        low.assign(N,-1); ord.assign(N,-1);
    }

    void dfs(int v,int time,int p = -1) {
        ord[v] = low[v] = time;
        ++time;

        bool isArticulation = false;
        int cnt = 0;

        for (int e:G[v]) {
            if (low[e] < 0) {
                ++cnt;
                dfs(e,time,v);
                low[v] = min(low[v],low[e]);
                if (p != -1 && ord[v] <= low[e]) isArticulation = true;
                if (ord[v] < low[e]) bridge.push_back({v,e});
            }
            else if (p != e) {
                low[v] = min(low[v],ord[e]);
            }
        }

        if (p == -1 && cnt >= 2) isArticulation = true;
        if (isArticulation) articulation.push_back(v);
    }

    void build() {
        dfs(0,0);
    }
};