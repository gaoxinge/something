use arrow::array::{Int32Array, StringArray};
use arrow::compute::add;

fn main() {
    let array = Int32Array::from(vec![Some(1), None, Some(3)]);
    for item in array.iter() {
        if let Some(value) = item {
            print!("{} ", value);
        } else {
            print!("NONE ");
        }
    }
    println!();

    let array = Int32Array::from(vec![Some(1), None, Some(3)]);
    for value in array.values() {
        print!("{} ", value);
    }
    println!();

    let array0 = Int32Array::from(vec![Some(1), None, Some(3)]);
    let array1 = Int32Array::from(vec![Some(1), None, Some(3)]);
    let added = add(&array0, &array1);
    println!("{:?}", added);
}
