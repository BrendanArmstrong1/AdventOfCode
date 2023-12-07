use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
  let file = File::open("input.txt").unwrap();
  part1(file);
}

fn part1(f: File) {
  let reader = BufReader::new(f);
  let mut matrix: Vec<Vec<char>> = Vec::new();

  matrix.push(Vec::new());
  for line in reader.lines() {
    let mut temp_vec: Vec<char> = Vec::new();
    let new_line: Vec<char> = line.unwrap().chars().collect();
    temp_vec.push('.');
    temp_vec.extend(new_line);
    temp_vec.push('.');
    matrix.push(temp_vec);
  }
  for _ in 0..matrix[2].len() {
    matrix.get_mut(0).unwrap().push('.');
  }
  matrix.push(vec!['.'; matrix[1].len()]);
  // now that the matrix is padded, I can find the
  let mut part_number_record: Vec<Vec<char>> = Vec::new();
  for y in 1..(matrix.len() - 2) {
    let mut cols = matrix.get(y).unwrap().iter().enumerate();

    while let Some((l, value)) = cols.next() {
      if matrix[y][l].is_numeric() {
        let mut new_part: Vec<char> = Vec::new();
        new_part.push(*value);
        let mut r: usize = l;

        while let Some((right, value)) = cols.next() {
          if value.is_numeric() {
            new_part.push(*value);
          } else {
            r = right;
            break;
          }
        } // now I have the whole number, and the l and r side of it

        for yy in (y - 1)..=(y + 1) {
          for xx in l - 1..=r {
            if !matrix[yy][xx].is_numeric() && matrix[yy][xx] != '.' {
              new_part.push(matrix[yy][xx])
            }
          }
        }
        part_number_record.push(new_part);
      }
    }
  }
  let mut orphaned_parts: Vec<&Vec<char>> = Vec::new();
  for part in part_number_record.iter() {
    let mut symbol_found: bool = false;
    for value in part.iter() {
      if !value.is_ascii_digit() {
        symbol_found = true;
      }
    }
    if symbol_found {
      orphaned_parts.push(part);
    }
  }

  let mut  summation: i32 = 0;
  for part in orphaned_parts.iter() {
    let concatenated = part.iter().filter(|v| v.is_numeric()).map(|x| x.to_string()).collect::<Vec<_>>().join("");
    summation += concatenated.parse().unwrap_or(0);
  }
  println!("{:?}", summation);
}
