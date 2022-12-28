pub fn f(a: Vec<i32>, b: Vec<i32>) -> Vec<i32> {
    a.iter().zip(b.iter()).map(|(l, r)| *l + *r).collect::<Vec<i32>>()
}
