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

    let answer: usize = reader
        .lines()
        .map(|v| {
            let line = v.unwrap();
            let Some((first, second)) = line.split_once(",") else {panic!("line wouldn't split")};
            let Some((bf, ef)) = first.split_once("-") else {panic!("first didnt split")};
            let Some((bs, es)) = second.split_once("-") else {panic!("second didnt split")};

            let bf: usize = bf.parse().unwrap();
            let ef: usize = ef.parse().unwrap();
            let bs: usize = bs.parse().unwrap();
            let es: usize = es.parse().unwrap();

            if bf == bs || es == ef {
                1
            } else if bf > bs {
                if ef > es {
                    0
                } else {
                    1
                }
            } else {
                if ef > es {
                    1
                } else {
                    0
                }
            }
        })
        .sum();
    println!("{}", answer);
}
fn part2(f: fs::File) {
    let reader = BufReader::new(f);

    let answer: usize = reader
        .lines()
        .map(|v| {
            let line = v.unwrap();
            let Some((first, second)) = line.split_once(",") else {panic!("line wouldn't split")};
            let Some((bf, ef)) = first.split_once("-") else {panic!("first didnt split")};
            let Some((bs, es)) = second.split_once("-") else {panic!("second didnt split")};

            let bf: usize = bf.parse().unwrap();
            let ef: usize = ef.parse().unwrap();
            let bs: usize = bs.parse().unwrap();
            let es: usize = es.parse().unwrap();

            if bf == bs || es == ef {
                1
            } else if bf > bs {
                if es < bf {
                    0
                } else {
                    1
                }
            } else {
                if ef < bs {
                    0
                } else {
                    1
                }
            }
        })
        .sum();
    println!("{}", answer);
}
