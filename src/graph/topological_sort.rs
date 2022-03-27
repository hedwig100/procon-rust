use std::collections::VecDeque;

// Verified
// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B
pub fn top_sort(graph: Vec<Vec<usize>>) -> Result<Vec<usize>, &'static str> {
    let n = graph.len();
    let mut indeg = vec![0; n];
    for v in 0..n {
        for &u in graph[v].iter() {
            indeg[u] += 1;
        }
    }

    let mut queue = VecDeque::new();
    let mut visited = vec![false; n];
    for v in 0..n {
        if indeg[v] == 0 {
            visited[v] = true;
            queue.push_back(v);
        }
    }

    let mut now = 0;
    let mut order = vec![0; n];
    while let Some(v) = queue.pop_front() {
        order[v] = now;
        now += 1;
        for &u in graph[v].iter() {
            indeg[u] -= 1;
            if indeg[u] == 0 {
                visited[u] = true;
                queue.push_back(u);
            }
        }
    }

    let is_dag = visited.iter().all(|&a| a);
    if !is_dag {
        return Err("graph isn't DAG.");
    }

    let mut ans = vec![0; n];
    for i in 0..n {
        ans[order[i]] = i;
    }
    return Ok(ans);
}
