#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_
void debug_out() {cerr << endl;}
template<typename Head,typename... Tail> void debug_out(Head H,Tail... T){cerr << ' ' << H; debug_out(T...);}
#define debug(...) cerr << 'L' << __LINE__ << " [" << #__VA_ARGS__ << "]:",debug_out(__VA_ARGS__)
#define dump(x) cerr << 'L' << __LINE__ << " " << #x << " = " << (x) << endl;
#else
#define debug(...) (void(0))
#define dump(x) (void(0))
#endif
#define rep(i,n) for (int i = 0; i < (int)(n); i ++)
#define irep(i,n) for (int i = (int)(n) - 1;i >= 0;--i)
using ll = long long;
using PL = pair<ll,ll>;
using P = pair<int,int>;
constexpr int INF = 1000000000;
constexpr long long HINF = 100000'00000'00000;
constexpr long long MOD = 1000000007;// = 998244353;
constexpr double EPS = 1e-4;
constexpr double PI = 3.14159265358979;

#pragma region Macros
template<typename T1,typename T2> ostream &operator<<(ostream &os,const pair<T1,T2> &p) {
    os << '(' << p.first << ',' << p.second << ')'; return os;
}
template<typename T> ostream &operator<<(ostream &os,const vector<T> &v) {
    os << '[';
    for (auto &e:v) {os << e << ',';}
    os << ']'; return os;
}
// grid searh
const int dy[8] = {-1,0,1,0,-1,-1,1,1};
const int dx[8] = {0,1,0,-1,-1,1,-1,1};
bool IN(int y,int x,int H,int W) {return (0 <= y)&&(y < H)&&(0 <= x)&&(x < W);}
#pragma endregion


map<ll,int> compress(vector<ll> A) {
    sort(A.begin(),A.end());
    A.erase(unique(A.begin(),A.end()),A.end());
    map<ll,int> mp;
    for (int i = 0;i < (int)A.size();++i) {
        mp[A[i]] = i;
    }
    return mp;
}
