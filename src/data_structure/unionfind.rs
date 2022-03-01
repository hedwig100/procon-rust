pub struct UnionFind {
    parent: Vec<i32>,
}

impl UnionFind {
    pub fn new(n: usize) -> UnionFind {
        UnionFind {
            parent: vec![-1; n],
        }
    }

    pub fn find(&mut self, i: usize) -> i32 {
        if self.parent[i] < 0 {
            i as i32
        } else {
            self.parent[i] = self.find(self.parent[i] as usize);
            self.parent[i]
        }
    }

    pub fn unite(&mut self, x: usize, y: usize) {
        let x = self.find(x);
        let y = self.find(y);
        let ix = x as usize;
        let iy = y as usize;

        if x == y {
            return;
        }

        if self.parent[ix] < self.parent[iy] {
            self.parent[ix] += self.parent[iy];
            self.parent[iy] = x;
        } else {
            self.parent[iy] += self.parent[ix];
            self.parent[ix] = y;
        }
    }

    pub fn same(&mut self, x: usize, y: usize) -> bool {
        self.find(x) == self.find(y)
    }

    pub fn root(&self) -> Vec<usize> {
        self.parent
            .iter()
            .enumerate()
            .filter(|(_, p)| **p < 0)
            .map(|(i, _)| i)
            .collect()
    }

    pub fn size(&self) -> usize {
        self.root().len()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn unionfind() {
        let mut uf = UnionFind::new(10);
        uf.unite(0, 1);
        uf.unite(4, 4);
        uf.unite(0, 8);
        uf.unite(2, 7);
        uf.unite(5, 6);
        uf.unite(3, 4);
        uf.unite(0, 9);
        assert!(uf.same(0, 1));
        assert!(uf.same(1, 8));
        assert!(uf.same(8, 9));
        assert!(uf.same(2, 7));
        assert!(uf.same(3, 4));
        assert!(uf.same(5, 6));
    }
}
