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

//---------------- dijkstra --------------

vector<ll> dijkstra(int n, vector<vector<PL>> &G,int s) {
    vector<ll> dist(n,HINF);
    dist[s] = 0;

    priority_queue<PL,vector<PL>,greater<P>> q;
    q.push({0,s});

    while (!q.empty()) {
        PL p = q.top(); q.pop();
        ll d = p.first;
        int v = p.second;
        if (dist[v] < d) continue;
        for (PL p: G[v]) {
            int e = p.first;
            ll cost = p.second;
            if (dist[e] > dist[v] + cost) {
                dist[e] = dist[v] + cost;
                q.push({dist[e],e});
            }
        }  
    }
    return dist;
}

//---------------------- beruman ford -----------------------

struct edge {
    int a,b; ll c;
    edge() {}
    edge(int a,int b,ll c) :a(a),b(b),c(c) {}
};
bool find_negative = false;
vector<ll> beruman(int N,vector<edge> &edges,int s = 0) {
    vector<ll> dist(N,HINF);
    dist[s] = 0;

    for (int i = 0;i < N; ++i) {
        bool update = false;
        for (edge &e: edges) {
            if (dist[e.a] != HINF && dist[e.b] > dist[e.a] + e.c) {
                dist[e.b] = dist[e.a] + e.c;
                update = true;
            }
        }
        if (!update) break;
        if (i == N - 1) find_negative = true;
    }
    return dist;
}

