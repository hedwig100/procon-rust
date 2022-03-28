// This io package is useful when proconio cannot be used.
pub fn input_intvec() -> Vec<usize> {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    input
        .trim()
        .split(' ')
        .map(|x| x.parse::<usize>().unwrap())
        .collect()
}

pub fn input_int2() -> (usize, usize) {
    let v = input_intvec();
    (v[0], v[1])
}

pub fn input_int() -> usize {
    input_intvec()[0]
}
