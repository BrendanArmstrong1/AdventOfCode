use std::{fs, time::Instant};

fn main() {
    let file = fs::read_to_string("../input.txt").unwrap();
    // part1(&file);
    part2(&file);
}

fn _part1(file: &str) {
    let now = Instant::now();
    let mut hashed = 0;
    let file = file.trim();
    // let file = "abcdef";
    let mut count = 0;
    while hashed == 0 {
        let ctx = format!("{}{}", file, count);
        let digest = md5::compute(&ctx);
        let five = &digest[0..2];
        if five.iter().all(|&x| x == 0_u8) {
            if digest[2] < 16 {
                hashed += 1;
                println!("{}  {:?}", ctx, digest);
            } else {
                count += 1;
            }
        } else {
            count += 1;
        }
    }

    println!("{} after {}", count, now.elapsed().as_millis());
}

fn part2(file: &str) {
    let now = Instant::now();
    let mut hashed = 0;
    let file = file.trim();
    // let file = "abcdef";
    let mut count = 0;
    while hashed == 0 {
        let ctx = format!("{}{}", file, count);
        let digest = md5::compute(&ctx);
        let five = &digest[0..3];
        if five.iter().all(|&x| x == 0_u8) {
            hashed += 1;
            println!("{}  {:?}", ctx, digest);
        } else {
            count += 1;
        }
    }

    println!("{} after {}", count, now.elapsed().as_millis());
}
