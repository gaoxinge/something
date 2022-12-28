pub fn sum_iter(points: &[f32]) -> f32 {
    points.iter().map(|x| x*x).sum()
}
