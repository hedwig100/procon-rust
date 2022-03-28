pub trait Monoid {
    fn e() -> Self;
    fn op(lhs: &Self, rhs: &Self) -> Self;
}

// Verify
// https://onlinejudge.u-aizu.ac.jp/status/users/hedwig/submissions/1/DSL_2_A/judge/6438617/Rust
pub struct SegmentTree<T> {
    pub n: usize,
    pub tree: Vec<T>,
}

impl<T> SegmentTree<T>
where
    T: Monoid + std::clone::Clone,
{
    pub fn new(n: usize) -> Self {
        SegmentTree {
            n,
            tree: vec![T::e(); 2 * n],
        }
    }

    pub fn build(data: &[T]) -> Self {
        let n = data.len();
        let mut st = SegmentTree {
            n,
            tree: vec![T::e(); 2 * n],
        };
        st.tree[n..(2 * n)].clone_from_slice(&data[..(2 * n - n)]);
        for i in (0..n).rev() {
            st.tree[i] = T::op(&st.tree[i << 1], &st.tree[i << 1 | 1])
        }
        st
    }

    pub fn update(&mut self, k: usize, x: T) {
        let mut k = k + self.n;
        self.tree[k] = x;
        while k > 1 {
            k >>= 1;
            self.tree[k] = T::op(&self.tree[k << 1], &self.tree[k << 1 | 1]);
        }
    }

    pub fn query(&self, l: usize, r: usize) -> T {
        let mut l = l + self.n;
        let mut r = r + self.n;
        let mut val_l = T::e();
        let mut val_r = T::e();
        while l < r {
            if l & 1 == 1 {
                val_l = T::op(&val_l, &self.tree[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                val_r = T::op(&self.tree[r], &val_r);
            }
            l >>= 1;
            r >>= 1;
        }
        T::op(&val_l, &val_r)
    }
}

// Example Monoid
#[derive(Clone)]
struct Min(usize);

impl Monoid for Min {
    fn e() -> Min {
        Min((1 << 31) - 1)
    }
    fn op(lhs: &Min, rhs: &Min) -> Min {
        Min(std::cmp::min(lhs.0, rhs.0))
    }
}
