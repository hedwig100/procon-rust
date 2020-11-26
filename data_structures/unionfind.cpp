#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n) ; i ++)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PL;
typedef pair<int,int> P;
const ll INF = 1e8;
const ll MOD = 1e9 + 7;

struct UnionFind {
    int N;
    vector<int> parents;

    UnionFind(int _N) : N(_N){
        parents.assign(N,-1);
    }

    int find(int x) { //xの親を返す
        if (parents[x] < 0) return x;
        return parents[x] = find(parents[x]);
    }
    
    void unite(int x, int y) {  //xとyの含むグループを併合
        int px = find(x);
        int py = find(y);
        if (parents[px] > parents[py]) swap(px,py); 
        if (px != py) {
            parents[px] += parents[py];
            parents[py] = px;
        }     
    }

    bool same(int x, int y) { //x,yが同じグループにいるか判定
        return find(x) == find(y);
    }

    int size(int x) { //xと同じグループのメンバーの個数
        return -parents[find(x)];
    }
    
    vector<int> root() {//ufの根を列挙
        vector<int> res;
        for (int i = 0; i < N; i ++) {
            if (parents[i] < 0) res.push_back(i);
        }
        return res;
    }

    int group_count() { //ufのグループの数を数える
        int cnt = 0;
        for (int i = 0; i < N; i ++) {
            if (parents[i] < 0) cnt ++;
        }
        return cnt;
    }
};









template<class Abel> struct WeightedUnionFind {
    int N;
    vector<int> parents;
    vector<Abel> diff_weight;

    WeightedUnionFind(int _N,Abel unit = 0) :N(_N){
        parents.assign(N,-1);
        diff_weight.assign(N,unit);
    }

    int find(int x) {
        if (parents[x] < 0) return x;
        else {
            int p = find(parents[x]);
            diff_weight[x] += diff_weight[parents[x]];
            return parents[x] = p;
        }
    }

    Abel weight(int x) {
        find(x);
        return diff_weight[x];
    }

    Abel diff(int x,int y) {//xとyが同じグループであることを確認してから呼ぶ
        return weight(y) - weight(x);
    }

    bool unite(int x, int y,Abel w) {
        w += weight(x);
        w -= weight(y);

        x = find(x);
        y = find(y);
        if (x == y) {
            if (diff(x,y) == w) return true;
            else return false;
        }

        if (parents[x] > parents[y]) {
            swap(x,y);
            w *= -1;
        }

        parents[x] += parents[y];
        parents[y] = x;
        diff_weight[y] = w;
        return true;
    }

    bool same(int x,int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return -parents[find(x)];
    }
};