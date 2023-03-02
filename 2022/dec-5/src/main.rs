use std::{
    fs,
    io::{BufRead, BufReader},
};

fn main() {
    let file = fs::File::open("input.txt").unwrap();
    part1(file);
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

    let mut crates_iter = crates.into_iter().rev();
    let mut stacks: Vec<String> = vec![String::new(); 9];

    let indexes = crates_iter
        .next()
        .unwrap()
        .chars()
        .enumerate()
        .filter(|(x, v)| v.to_string().ne(" "))
        .map(|(x, v)| (x, v.to_string().parse::<usize>().unwrap()))
        .collect::<Vec<(usize, usize)>>();
    println!("{:?}", indexes);

    for line in crates_iter {
        for i in &indexes {
            let l: char = line.chars().nth(i.0).unwrap();
            if l.to_string().eq(" ") {
                continue;
            }
            print!("{}", l);
            stacks[i.1 - 1].push(l);
        }
        println!("");
    }
    println!("{:?}", stacks);
}
