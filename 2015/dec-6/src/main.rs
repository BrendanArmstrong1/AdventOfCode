use std::{fs, usize};

fn main() {
    let file = fs::read_to_string("./input.txt").expect("Bad File, you dum dum.");
    // part1(&file);
    part2(&file);
}

fn _part1(file: &str) {
    let mut state = vec![vec![0; 1000]; 1000];

    for line in file.lines() {
        let mut iter = line.split_whitespace();
        let func: u8 = match iter.next() {
            Some(word) => {
                if word == "toggle" {
                    0
                } else {
                    match iter.next() {
                        Some(state) => {
                            if state == "on" {
                                1
                            } else {
                                2
                            }
                        }
                        None => panic!("ummm..."),
                    }
                }
            }
            None => panic!("what the heck!?"),
        };
        let p1: Vec<&str> = iter.next().unwrap().split(',').collect();
        iter.next();
        let p2: Vec<&str> = iter.next().unwrap().split(',').collect();

        _toggle1(
            &mut state,
            (
                p1[0].parse::<usize>().unwrap(),
                p1[1].parse::<usize>().unwrap(),
            ),
            (
                p2[0].parse::<usize>().unwrap(),
                p2[1].parse::<usize>().unwrap(),
            ),
            func,
        );
    }
    let on: i32 = state.iter().flatten().sum();
    println!("{}", on);
}

fn part2(file: &str) {
    let mut state = vec![vec![0; 1000]; 1000];

    for line in file.lines() {
        let mut iter = line.split_whitespace();
        let func: i32 = match iter.next() {
            Some(word) => {
                if word == "toggle" {
                    2
                } else {
                    match iter.next() {
                        Some(state) => {
                            if state == "on" {
                                1
                            } else {
                                -1
                            }
                        }
                        None => panic!("ummm..."),
                    }
                }
            }
            None => panic!("what the heck!?"),
        };
        let p1: Vec<&str> = iter.next().unwrap().split(',').collect();
        iter.next();
        let p2: Vec<&str> = iter.next().unwrap().split(',').collect();

        toggle2(
            &mut state,
            (
                p1[0].parse::<usize>().unwrap(),
                p1[1].parse::<usize>().unwrap(),
            ),
            (
                p2[0].parse::<usize>().unwrap(),
                p2[1].parse::<usize>().unwrap(),
            ),
            func,
        );
    }
    let on: i32 = state.iter().flatten().sum();
    println!("{}", on);
}

fn toggle2(map: &mut Vec<Vec<i32>>, p1: (usize, usize), p2: (usize, usize), func: i32) {
    for row in map.iter_mut().take(p2.1 + 1).skip(p1.1) {
        for col in row.iter_mut().take(p2.0 + 1).skip(p1.0) {
            *col += func;
            if *col < 0 {
                *col = 0;
            }
        }
    }
}

fn _toggle1(map: &mut Vec<Vec<i32>>, p1: (usize, usize), p2: (usize, usize), func: u8) {
    for row in map.iter_mut().take(p2.1 + 1).skip(p1.1) {
        for col in row.iter_mut().take(p2.0 + 1).skip(p1.0) {
            if func == 0 {
                if *col == 0 {
                    *col = 1;
                } else {
                    *col = 0;
                }
            } else if func == 1 {
                *col = 1;
            } else {
                *col = 0;
            }
        }
    }
}
