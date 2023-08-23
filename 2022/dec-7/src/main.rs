use std::{
    fs,
    io::{BufRead, BufReader},
};

fn main() {
    let file: fs::File = fs::File::open("input.txt").unwrap();
    part1(file);
}

/// this is a rustDoc string
/// this is a continuatiol of the RustDoc string
#[derive(Debug)]
struct Directory<'a> {
    name: String,
    subdir: Box<Vec<Directory>>,
    parent: &'a Directory,
    file_size: usize,
}

impl Directory {
    fn new() -> Self {
        Directory {
            name: "/".to_string(),
            subdir: Box::new(vec![]),
            file_size: 0,
        }
    }
}

fn part1(f: fs::File) {
    let reader = BufReader::new(f);
    let mut file_iter = reader.lines().map(Result::unwrap);

    let mut structure: Directory;
    let current_dir: String;
    while let Some(line) = file_iter.next() {
        if line.contains("$ cd") {
            let next = line.split(" ").nth(2).unwrap();
            if next.eq("..") {
                // structure.up_one();
            }
        }
    }
}
