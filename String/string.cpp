#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); i ++)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PL;
typedef pair<int,int> P;
const int INF = 1e9;
const ll MOD = 1e9 + 7;

//Zalgorithum 最長共通接頭辞の長さ O(|S|)
vector<int> Z(string s) {
    int l = s.size();
    vector<int> Z(l);
    Z[0] = l;
    int i = 1,j = 0;
    while (i < l) {
        while (i + j < l && s[j] == s[i + j]) j ++;
        Z[i] = j;

        if (j == 0) {
            i ++;
            continue;
        }
        int k = 1;
        while (k < j && k + Z[k] < j) {
            Z[i + k] = Z[k];
            k ++;
        }
        i += k;
        j -= k;
    }

    return Z;
}

//KMP S[:i]の接頭辞と接尾辞が何文字一致するか　O(|S|)
vector<int> KMP(string s) {
    int l = s.size();
    vector<int> mp(l + 1,-1);
    int j = -1;
    for (int i = 0; i < l; i ++) {
        while (j >= 0 && s[i] != s[j]) j = mp[j];
        j ++;
        if (s[i + 1] == s[j]) mp[i + 1] = mp[j];
        else mp[i + 1] = j;
    }
}