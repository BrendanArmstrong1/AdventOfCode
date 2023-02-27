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
    let values: Vec<_> = reader
        .lines()
        .map(Result::unwrap)
        .map(|l| {
            let (left, right) = l.split_at(l.len() / 2);
            left.chars()
                .filter(|&c| right.contains(c))
                .take(1)
                .next()
                .unwrap()
        })
        .collect();

    let sum = values.iter().fold(0, |acc, val| {
        if val.is_lowercase() {
            acc + (*val as u32 - 'a' as u32 + 1)
        } else {
            acc + (*val as u32 - 'A' as u32 + 27)
        }
    });

    println!("{}", sum);
}

fn part2(f: fs::File) {
    let reader = BufReader::new(f);

    let mut values = reader.lines().map(Result::unwrap);

    let mut sum: u32 = 0;
    while let Some(first) = values.next() {
        let second = values.next().unwrap();
        let third = values.next().unwrap();
        let letter = first
            .chars()
            .filter(|&c| second.contains(c) && third.contains(c))
            .take(1)
            .next()
            .unwrap();

        if letter.is_lowercase() {
            sum += letter as u32 - 'a' as u32 + 1
        } else {
            sum += letter as u32 - 'A' as u32 + 27
        };
    }
    println!("{}", sum);
}
