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


// Beruman Ford 
struct MinCostFlow {
    struct edge{int to,cap,cost,rev;};
    int N;
    vector<vector<edge>> G;
    vector<long long> dist;
    vector<int> prevv,preve;
    MinCostFlow(int N):N(N) {
        G.resize(N);
        dist.resize(N);
        prevv.resize(N);
        preve.resize(N);
    }
    void add_edge(int from,int to,int cap,int cost) {
        G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
        G[to].push_back((edge){from,0,-cost,(int)G[from].size() - 1});
    }
    long long flow(int s,int t,int f) {
        long long res = 0;
        while (f > 0) {
            fill(dist.begin(),dist.end(),INF);
            dist[s] = 0;
            bool update = true;
            while (update) {
                update = false;
                for (int v = 0;v < N; ++v) {
                    if (dist[v] == INF) continue;
                    for (int i = 0;i < (int)G[v].size(); ++i) {
                        edge &e = G[v][i];
                        if (e.cap > 0 && dist[v] + e.cost < dist[e.to]) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            update = true;
                        }
                    }
                }
            }
            // f の　flow　はそもそも存在しない
            if (dist[t] == INF) return -1;
            int d = f;
            for (int v = t; v != s; v = prevv[v]) {
                d = min(d,G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += (long long)d*dist[t];
            for (int v = t;v != s;v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};


// Potential and Dijkstra 
// 負辺に対応していない
struct MinCostFlow {
    struct edge{int to,rev; long long cap,cost;};
    int N;
    vector<vector<edge>> G;
    vector<long long> h,dist;
    vector<int> prevv,preve;
    MinCostFlow(int N) {
        G.resize(N);
        h.assign(N,0);
        dist.assign(N,HINF);
        prevv.resize(N);
        preve.resize(N);
    }

    void add_edge(int from,int to,long long cap,long long cost) {
        G[from].push_back(edge{to,cap,cost,(int)G[to].size()});
        G[to].push_back(edge{from,0,-cost,(int)G[from].size()-1});
    }

    long long flow(int s,int t,long long f) {
        long long res = 0;
        while (f > 0) {
            priority_queue<PL,vector<PL>,greater<PL>> q;
            fill(dist.begin(),dist.end(),HINF);
            dist[s] = 0;
            q.push(PL{0,s});
            while (!q.empty()) {
                PL p = q.top(); q.pop();
                int v = p.second;
                if (dist[v] < p.first) continue;
                for (int i = 0; i < (int)G[v].size();++i) {
                    edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        q.push(P{dist[e.to],e.to});
                    }
                }
            }
            if (dist[t] == HINF) return -1;
            for (int v = 0;v < N; ++v) h[v] += dist[v];
            long long d = f;
            for (int v = t;v != s;v = prevv[v]) {
                d = min(d,G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d*h[t];
            for (int v = t;v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};



