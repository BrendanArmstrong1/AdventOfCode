use std::collections::HashMap;
use std::fs;
use std::io::{BufRead, BufReader};

fn main() {
  let file = fs::File::open("input.txt").unwrap();
  part1(file);
  let file = fs::File::open("input.txt").unwrap();
  part2(file);
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
    nums.push(
      format!("{}{}", numbers[0], numbers[numbers.len() - 1])
        .parse()
        .unwrap(),
    );
  }
  println!("{}", nums.iter().sum::<u32>());
}

fn part2(f: fs::File) {
  let reader = BufReader::new(f);
  let mut nums: Vec<u32> = Vec::new();
  let numbers_map: HashMap<&str, char> = HashMap::from([
    ("zero", '0'),
    ("one", '1'),
    ("two", '2'),
    ("three", '3'),
    ("four", '4'),
    ("five", '5'),
    ("six", '6'),
    ("seven", '7'),
    ("eight", '8'),
    ("nine", '9'),
  ]);
  for line in reader.lines() {
    let line = line.unwrap();
    let mut found_text: Vec<(char, usize)> = Vec::new();
    for (key, val) in numbers_map.iter() {
      let pairs: Vec<_> = line.match_indices(key).collect();
      for (idx, _) in pairs {
        found_text.push((*val, idx));
      }
    }
    for (idx, char) in line.chars().enumerate() {
      if char.is_numeric() {
        found_text.push((char, idx));
      }
    }
    found_text.sort_by(|a, b| a.1.cmp(&b.1));
    let value: u32 = format!("{}{}", found_text[0].0, found_text[found_text.len() - 1].0)
      .parse()
      .unwrap();
    nums.push(value);
  }

  println!("{}", nums.iter().sum::<u32>());
}
