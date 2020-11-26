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

struct edge {
    int to,rev;
    int cap;
    edge() {}
    edge(int to,int cap,int rev):to(to),cap(cap),rev(rev) {}
};

struct Dinic{
    int N;
    vector<vector<edge>> G;
    vector<int> level; // min distance from s
    vector<int> iter;

    Dinic(int _N):N(_N) {
        G.resize(N),level.resize(N), iter.resize(N);
    }

    void add_edge(int a,int b,int c){
        // only directed edge
        G[a].push_back((edge){b,c,(int)G[b].size()});
        G[b].push_back((edge){a,0,(int)G[a].size() - 1});
    }

    void _bfs(int s){
        fill(level.begin(),level.end(),-1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()){
            int v = q.front(); q.pop();
            for (int i = 0;i < (int)G[v].size(); ++i){
                edge &e = G[v][i];
                if (e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    
    int _dfs(int v,int t,int f){
        if (v == t) return f;
        for (int &i = iter[v];i < G[v].size(); ++i) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] > level[v]){
                int d = _dfs(e.to,t,min(f,e.cap));
                if (d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int flow(int s,int t){
        int flow = 0;
        for (;;){
            _bfs(s);
            if (level[t] < 0) return flow; // no augmenting path
            fill(iter.begin(),iter.end(),0);
            int f;
            while ((f = _dfs(s,t,INF)) > 0) flow += f;
        }
    }
};