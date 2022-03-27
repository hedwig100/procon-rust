// Verify
// https://atcoder.jp/contests/practice2/submissions/30505118
pub struct StronglyConnectedComponents {
    pub n: usize,
    pub graph: Vec<Vec<usize>>,

    // for executing algorithm
    graph_reversed: Vec<Vec<usize>>,
    order: Vec<usize>,
    which_group: Vec<i32>,

    // for keeping scc information
    pub n_scc: usize,
    pub group: Vec<Vec<usize>>,
    pub graph_scc: Vec<Vec<usize>>,

    // for togological sort
    pub top_order: Vec<usize>,
}

impl StronglyConnectedComponents {
    pub fn new(n: usize) -> StronglyConnectedComponents {
        StronglyConnectedComponents {
            n,
            graph: vec![Vec::new(); n],
            graph_reversed: vec![Vec::new(); n],
            order: Vec::new(),
            which_group: vec![1; n],
            n_scc: 0,
            group: Vec::new(),
            graph_scc: Vec::new(),
            top_order: Vec::new(),
        }
    }

    pub fn add_edge(&mut self, a: usize, b: usize) {
        self.graph[a].push(b);
        self.graph_reversed[b].push(a);
    }

    fn dfs(&mut self, v: usize) {
        self.which_group[v] = -1;
        for i in 0..self.graph[v].len() {
            let u = self.graph[v][i];
            if self.which_group[u] > 0 {
                self.dfs(u);
            }
        }
        self.order.push(v);
    }

    fn rdfs(&mut self, v: usize, group_id: usize) {
        self.which_group[v] = group_id as i32;
        self.group[group_id].push(v);
        for i in 0..self.graph_reversed[v].len() {
            let u = self.graph_reversed[v][i];
            if self.which_group[u] < 0 {
                self.rdfs(u, group_id);
            }
        }
    }

    pub fn build(&mut self) {
        for i in 0..self.n {
            if self.which_group[i] > 0 {
                self.dfs(i);
            }
        }

        self.n_scc = 0;
        self.order.reverse();
        for i in 0..self.order.len() {
            let v = self.order[i];
            if self.which_group[v] < 0 {
                self.group.push(Vec::new());
                self.rdfs(v, self.n_scc);
                self.n_scc += 1;
            }
        }
    }

    pub fn which_group(&self, u: usize) -> i32 {
        self.which_group[u]
    }
}
