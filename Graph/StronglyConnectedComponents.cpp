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

struct StronglyConnectedComponents {
    int N;
    vector<vector<int>> G,rG;
    vector<int> group,order;

    StronglyConnectedComponents(int _N): N(_N) {
        G.resize(N); rG.resize(N); group.assign(N,1);
    }
    
    void add_edge(int a,int b) {
        G[a].push_back(b);
        rG[b].push_back(a);
    }

    void dfs(int v) {
        group[v] = -1;
        for (int e: G[v]) {
            if (group[e] > 0) dfs(e);
        }
        order.push_back(v);
    }

    void rdfs(int v,int cnt) {
        group[v] = cnt;
        for (int e: rG[v]) {
            if (group[e] < 0) rdfs(e,cnt);
        }
    }

    void build() {
        for (int i = 0;i < N;i ++) {
            if (group[i] > 0) dfs(i);
        }
        reverse(begin(order),end(order));
        int cnt = 0;
        for (int v: order) {
            if (group[v] < 0) rdfs(v,cnt),cnt++;
        }
    }

    int operator[](int i) {
        return group[i];
    }
};