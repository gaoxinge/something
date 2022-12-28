pub fn f(a: &[i32], b: &[i32], c: &mut [i32]) {
  for ((a, b), c) in a.iter().zip(b).zip(c.iter_mut()) {
    *c = *a + *b;
  }
}
