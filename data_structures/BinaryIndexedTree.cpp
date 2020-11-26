// 1-indexed
template<class T> 
struct BinaryIndexedTree {
    int N,power = 1;
    vector<T> bit;

    BinaryIndexedTree(int N = 0): N(N){
        bit.assign(N + 1,0);
        while (power <= N) power <<= 1; //power > N
    }
    void build(const vector<T> &A) {
        for (int i = 1;i <= N; ++i) add(i,A[i - 1]);
    }
    // add x to a[i]
    void add(int i,T x) {
        for (int idx = i; idx <= N; idx += (idx & -idx)) {
            bit[idx] += x;
        }
    }
    // return a[1] + a[2] + a[3] + .. + a[k]
    T sum(int k) {
        T ret = 0;
        for (int idx = k; idx > 0; idx -= (idx & -idx)) {
            ret += bit[idx];
        }
        return ret;
    }
    // return a[l] + a[l + 1] + a[l + 2] + .. + a[r - 1]
    T sum(int l,int r) {
        return sum(r - 1) - sum(l - 1);
    }
    // return min index s.t. a[1] + a[2] + a[3] + .. + a[x] >= w
    int lower_bound(T w) {
        if (w <= 0) return 0;
        int x = 0;
        for (int r = power; r > 0; r >>= 1) {
            if (x + r <= N && bit[x + r] < w) {
                w -= bit[x + r];
                x += r;
            }
        } 
        return x + 1;
    }
};

//1-indexed
template<class T>
struct BinaryIndexedTree2D {
    int H,W;
    vector<vector<T>> bit;
    BinaryIndexedTree2D(int H = 0,int W = 0):H(H),W(W){
        bit.assign(H + 1,vector<T>(W + 1,0));
    }
    // add x to a[h][w]
    void add(int h,int w,T x) {
        for (int i = h; i <= H; i += (i & -i)) {
            for (int j = w; j <= W; j += (j & -j)) {
                bit[i][j] += x;
            }
        }
    }
    // return sum of a[i][j] s.t. (1 <= i <= h and 1 <= j <= w)
    T sum(int h,int w) {
        T ret = 0;
        for (int i = h; i > 0; i -= (i & -i)) {
            for (int j = w; j > 0; j -= (j & -j)) {
                ret += bit[i][j];
            }
        }
        return ret;
    }
    // return sum of a[i][j] s.t. (h1 <= i < h2 and w1 <= j < w2)
    T query(int h1,int h2,int w1,int w2) {
        return sum(h2 - 1,w2 - 1) - sum(h2 - 1,w1 - 1) - sum(h1 - 1,w2 - 1) + sum(h1 - 1,w1 - 1);
    }
};