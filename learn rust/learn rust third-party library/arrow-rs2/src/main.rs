use arrow2::array::{PrimitiveArray, Utf8Array};
use arrow2::array::ord::total_cmp;
use arrow2::compute::arithmetics::basic::*;

fn main() {
    let array = PrimitiveArray::<i64>::from(&[Some(4), None, Some(6)]);
    for item in array.iter() {
        if let Some(value) = item {
            print!("{} ", value);
        } else {
            print!("NONE ");
        }
    }
    println!();

    let array = PrimitiveArray::<i64>::from(&[Some(4), None, Some(6)]);
    for value in array.values().iter() {
        print!("{} ", value);
    }
    println!();

    let array0 = PrimitiveArray::<i64>::from(&[Some(1), Some(2), Some(3)]);
    let array1 = PrimitiveArray::<i64>::from(&[Some(4), None, Some(6)]);
    let added = add(&array0, &array1);
    println!("{:?}", added);
}
