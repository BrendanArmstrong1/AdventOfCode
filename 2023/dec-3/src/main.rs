use std::fs::File;
use std::io::{BufRead, BufReader};
use std::thread;
use std::time::Duration;

fn main() {
  let file = File::open("input.txt").unwrap();
  part1(file);
}

fn part1(_: File) {
  let matrix: Vec<&str> = vec![
    "467..114*.",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.&",
  ];
  let m = matrix.len();
  let n = matrix[0].len();
  let mut char_vec: Vec<Vec<char>> = Vec::new();
  for row in matrix {
    char_vec.push(row.chars().collect());
  }
  let test_num: usize = 1;
  println!("{:?}", test_num.overflowing_sub(5));
  println!();
  for (idy, row) in char_vec.iter().enumerate() {
    for (idx, char) in row.iter().enumerate() {
      if !char.is_numeric() && char != &'.' {
        // find initial number for flood fill
        for y in idy..=idy + 2 {
          for x in idx..=idx + 2 {
            if 0 < (y as isize) && y <= m && 0 < (x as isize) && x <= n && char_vec[y-1][x-1].is_numeric() {
              // start by filling left
              println!("{}", char_vec.get(y.saturating_sub(1)).unwrap().get(x.saturating_sub(1)).unwrap());
            }
          }
        }
      }
    }
  }
}
