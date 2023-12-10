use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
  let file = File::open("input.txt").unwrap();
  part1(file);
}

fn part1(_: File) {
  let matrix: Vec<&str> = vec![
    "467.$114..",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.#",
  ];
  let mut char_vec: Vec<Vec<char>> = Vec::new();
  for row in matrix {
    char_vec.push(row.chars().collect());
  }
  let temp_row = vec!['.';10];

  for (idy, row) in char_vec.iter().enumerate() {
    for (idx, char) in row.iter().enumerate() {
      if !char.is_numeric() && char != &'.' {
        // flood fill
        for y in idy..=idy + 2 {
          for x in idx..=idx + 2 {
            let value = char_vec
              .get((y as isize -1) as usize)
              .unwrap_or(&temp_row)
              .get((x as isize -1) as usize)
              .unwrap_or(&'.');
            print!("{}", value);
          }
          println!();
        }
        println!();
      }
    }
  }
}
