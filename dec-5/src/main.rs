use std::fs;
use fancy_regex::Regex;

fn main() {
    let file = fs::read_to_string("../input.txt").unwrap();
    // part1(&file);
    part2(&file);
}

fn _part1(file: &str) {
    let re1 = Regex::new(r"([a-z])\1").unwrap(); // same character
    let re2 = Regex::new(r"ab|cd|pq|xy").unwrap();
    let mut good = 0;

    for line in file.lines() {
        if re2.is_match(line).unwrap() {
            continue;
        }
        if !re1.is_match(line).unwrap() {
            continue;
        }
        let vowels = "aeiou".to_string();
        let mut count = 0;
        for ch in line.chars() {
            if vowels.contains(ch) {
                // vowels = vowels.replace(ch, "");
                count += 1;
            }
            if count == 3 {
                break;
            }
        }
        if count == 3 {
            println!("{} a good string", line);
            good += 1;
            continue;
        }
    }
    println!("{}", good);
}

fn part2(file: &str) {
    let re1 = Regex::new(r"([a-z]{2}).*\1").unwrap();
    let re2 = Regex::new(r"([a-z]).\1").unwrap();
    let mut good = 0;

    for line in file.lines() {
        if !re2.is_match(line).unwrap() {
            continue;
        }
        if !re1.is_match(line).unwrap() {
            continue;
        }
        good += 1;
    }
    println!("{}", good);
}
