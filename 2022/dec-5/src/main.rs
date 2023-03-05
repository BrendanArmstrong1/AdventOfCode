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

#[allow(unused_variables)]
fn part1(f: fs::File) {
    let reader = BufReader::new(f);
    let mut lines = reader.lines().map(Result::unwrap);

    let mut crates: Vec<String> = Vec::new();
    'inner: while let Some(val) = lines.next() {
        if val.eq("") {
            break 'inner;
        } else {
            crates.push(val);
        }
    }
    let instructions: Vec<String> = lines.collect();

    let crates_iter = crates.iter().rev();
    let mut stacks: Vec<String> = parse_stacks(crates_iter);

    let mut holder: String = String::new();
    for line in instructions {
        let mut split = line.split(" ").filter_map(|x| x.parse::<usize>().ok());
        if let Some(amount) = split.next() {
            let bounds: Vec<usize> = split.collect::<Vec<usize>>();
            for _ in 0..amount {
                holder.push(stacks[bounds[0] - 1].pop().unwrap());
                stacks[bounds[1] - 1].push(holder.pop().unwrap());
            }
        };
    }
    for st in &stacks {
        println!("{}", st);
    }
    println!("");
}

fn part2(f: fs::File) {
    let reader = BufReader::new(f);
    let mut lines = reader.lines().map(Result::unwrap);

    let mut crates: Vec<String> = Vec::new();
    'inner: while let Some(val) = lines.next() {
        if val.eq("") {
            break 'inner;
        } else {
            crates.push(val);
        }
    }
    let instructions: Vec<String> = lines.collect();

    let crates_iter = crates.iter().rev();
    let mut stacks: Vec<String> = parse_stacks(crates_iter);

    let mut holder: String = String::new();
    for line in instructions {
        let mut split = line.split(" ").filter_map(|x| x.parse::<usize>().ok());
        if let Some(amount) = split.next() {
            let bounds: Vec<usize> = split.collect::<Vec<usize>>();
            for _ in 0..amount {
                holder.push(stacks[bounds[0] - 1].pop().unwrap());
            }
            for _ in 0..amount {
                stacks[bounds[1] - 1].push(holder.pop().unwrap());
            }
        };
    }
    for st in &stacks {
        println!("{}", st);
    }
    println!("");
}

fn parse_stacks<'a, T>(mut crates_iter: T) -> Vec<String>
where
    T: Iterator<Item = &'a String>,
{
    let mut ret_val = vec![String::new(); 9];

    let indexes = crates_iter
        .next()
        .unwrap()
        .chars()
        .enumerate()
        .filter(|(_x, v)| v.to_string().ne(" "))
        .map(|(x, v)| (x, v.to_string().parse::<usize>().unwrap()))
        .collect::<Vec<(usize, usize)>>();

    for line in crates_iter {
        for i in &indexes {
            let l: char = line.chars().nth(i.0).unwrap();
            if l.to_string().eq(" ") {
                continue;
            }
            ret_val[i.1 - 1].push(l);
        }
    }
    ret_val
}
