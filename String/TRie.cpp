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

template<int char_size,int base>
struct Trie {
    struct Node {
        vector<int> child,accept;
        int c,common;
        Node(int c):c(c),common(0) {
            child.assign(char_size,-1);
        }
    };
    vector<Node> tree;
    int root;
    Trie(): root(0) {
        tree.push_back(Node(root));
    }
    void insert(const string &s,int id) {
        int node_id = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            int c = (int)(s[i] - base);
            int &next_id = tree[node_id].child[c];
            if (next_id < 0) {
                next_id = (int)tree.size();
                tree.push_back(Node(c));
            }
            ++tree[node_id].common;
            node_id = next_id;
        }
        ++tree[node_id].common;
        tree[node_id].accept.push_back(id);
    }
    // insert s to Trie
    void insert(const string &s) {
        insert(s,tree[0].common);
    }
    // return the number of s in Trie
    int search(const string &s,bool prefix = false) {
        int node_id = 0;
        for (int i = 0;i < (int)s.size(); ++i) {
            int c = (int)(s[i] - base);
            int &next_id = tree[node_id].child[c];
            if (next_id < 0) return 0;
            node_id = next_id;
        }
        return prefix ? 1:(int)tree[node_id].accept.size();
    }
    // if prefix of s in Trie
    bool prefix(const string &s) {
        return search(s,true) > 0;
    }
};

//Trie<26,'a'> tr