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

struct LowestCommonAncestor {
    int N,root,K;
    vector<int> dist;
    vector<vector<int>> G,parents;

    void dfs() {
        dist[root] = 0;
        stack<int> st;
        st.push(root);
        while (!st.empty()) {
            int v = st.top(); st.pop();
            for (int e:G[v]) {
                if (dist[e] >= 0) {
                    parents[v][0] = e;
                    continue;
                }
                dist[e] = dist[v] + 1;
                st.push(e);
            }
        }
    }

    LowestCommonAncestor(int N,const vector<vector<int>> &G,int root = 0)
        :N(N),G(G),root(root) {
        K = 1;
        while ((1<<K) < N) ++K;
        dist.assign(N,-1); dist[root] = 0;
        parents.assign(N,vector<int>(K,-1));

        dfs();
        for (int i = 0;i < K - 1; ++i) {
            for (int j = 0;j < N; ++j) {
                if (parents[j][i] < 0) continue;
                parents[j][i + 1] = parents[parents[j][i]][i];
            }
        }
    }

    int query(int u,int v) {
        if (dist[u] < dist[v]) swap(u,v);
        for (int k = 0;k < K; ++k) {
            if (((dist[u] - dist[v])>>k)&1) u = parents[u][k];
        }
        if (u == v) return u;
        for (int k = K - 1; k >= 0; --k) {
            if (parents[u][k] != parents[v][k]) {
                u = parents[u][k];
                v = parents[v][k];
            }
        }
        return parents[u][0];
    }

    int operator[](int k) {
        return dist[k];
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    
    return 0;
}