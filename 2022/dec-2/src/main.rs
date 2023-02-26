use std::{
    fs,
    io::{BufRead, BufReader},
};

fn main() {
    let file = fs::File::open("input.txt").unwrap();
    part1(file);
    let file = fs::File::open("input.txt").unwrap();
    part2(file);
}

fn part1(f: fs::File) {
    let reader = BufReader::new(f);
    let win = 6;
    let lose = 0;
    let draw = 3;

    let score = reader.lines().map(Result::unwrap).fold(0, |acc, str| {
        acc + {
            match str.split_once(" ") {
                Some((opp, me)) => match opp {
                    // rock
                    "A" => match me {
                        "X" => 1 + draw,
                        "Y" => 2 + win,
                        "Z" => 3 + lose,
                        _ => 0,
                    },
                    // paper
                    "B" => match me {
                        "X" => 1 + lose,
                        "Y" => 2 + draw,
                        "Z" => 3 + win,
                        _ => 0,
                    },
                    // scissors
                    "C" => match me {
                        "X" => 1 + win,
                        "Y" => 2 + lose,
                        "Z" => 3 + draw,
                        _ => 0,
                    },
                    _ => 0,
                },
                None => 0,
            }
        }
    });
    println!("part1: {}", score);
}

fn part2(f: fs::File) {
    let reader = BufReader::new(f);
    let win = 6;
    let lose = 0;
    let draw = 3;
    let rock = 1;
    let paper = 2;
    let scis = 3;

    let score = reader.lines().map(Result::unwrap).fold(0, |acc, str| {
        acc + {
            match str.split_once(" ") {
                Some((opp, me)) => match opp {
                    // rock
                    "A" => match me {
                        // lose
                        "X" => scis + lose,
                        // draw
                        "Y" => rock + draw,
                        // win
                        "Z" => paper + win,
                        _ => 0,
                    },
                    // paper
                    "B" => match me {
                        // lose
                        "X" => rock + lose,
                        // draw
                        "Y" => paper + draw,
                        // win
                        "Z" => scis + win,
                        _ => 0,
                    },
                    // scissors
                    "C" => match me {
                        // lose
                        "X" => paper + lose,
                        // draw
                        "Y" => scis + draw,
                        // win
                        "Z" => rock + win,
                        _ => 0,
                    },
                    _ => 0,
                },
                None => 0,
            }
        }
    });
    println!("part2: {}", score);
}
