use std::fs;

fn main() {
    let file = fs::read_to_string("../input.txt").unwrap();
    part1(&file);
    part2(&file);
}

fn part1(file: &str) {
    let mut floor = 0;
    for char in file.chars() {
        if char == '(' {
            floor += 1;
        }
        if char == ')' {
            floor -= 1;
        }
    }
    println!("{}", floor);
}

fn part2(file: &str) {
    let mut floor = 0;
    let mut position = 0; 
    for char in file.chars() {
        position += 1;
        if char == '(' {
            floor += 1;
        } else {
            floor -= 1;
        }
        if floor < 0 {
            break;
        }
    }
    println!("{}", position);
}

