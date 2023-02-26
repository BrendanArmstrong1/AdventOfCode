use std::{collections::HashMap, fs};

fn main() {
    let file = fs::read_to_string("./input.txt")
        .unwrap()
        .replace("AND", "&")
        .replace("OR", "|")
        .replace("NOT ", "!")
        .replace("RSHIFT", ">>")
        .replace("LSHIFT", "<<");
    part1(&file);
}

fn part1(file: &str) {
    let mut map: HashMap<&str, &str> = HashMap::new();
    for line in file.lines() {
        let arr: Vec<&str> = line.split(" -> ").collect();
        map.insert(arr[1], arr[0]);
    }
    for (key, val) in map.iter() {
        println!("{} = {}", key, val);
    }
}
