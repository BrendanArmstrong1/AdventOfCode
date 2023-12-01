use std::fs;
use std::io::{BufRead, BufReader};

fn main() {
  let file = fs::File::open("input.txt").unwrap();
  part1(file);
  // let file = fs::File::open("input.txt").unwrap();
}

fn part1(f: fs::File) {
  let reader = BufReader::new(f);
  let mut nums: Vec<u32> = Vec::new();
  for line in reader.lines() {
    let mut numbers: Vec<char> = Vec::with_capacity(20);
    for char in line.unwrap().chars() {
      if char.is_numeric() {
        numbers.push(char);
      }
    }
    nums.push(format!("{}{}",numbers[0], numbers[numbers.len() - 1]).parse().unwrap())
  }
  println!("{}", nums.iter().sum::<u32>());
}
