use std::fs;

fn main() {
    let file = fs::read_to_string("../input.txt").unwrap();
    // _part1(&file);
    part2(&file);
}

fn _part1(file: &str) {
    let mut total: u32 = 0;
    for line in file.lines() {
        let dim: Vec<&str> = line.split('x').collect();
        let len = dim[0].parse::<u32>().unwrap();
        let wid = dim[1].parse::<u32>().unwrap();
        let hig = dim[2].parse::<u32>().unwrap();
        let s1 = len * wid;
        let s2 = hig * wid;
        let s3 = len * hig;
        let small = vec![s1, s2, s3];
        total += 2 * s1 + 2 * s2 + 2 * s3 + small.iter().min().unwrap();
    }
    println!("{}", total);
}

fn part2(file: &str) {
    let mut total: u32 = 0;
    for line in file.lines() {
        let mut length: u32 = 0;
        let dim: Vec<&str> = line.split('x').collect();
        let len = dim[0].parse::<u32>().unwrap();
        let wid = dim[1].parse::<u32>().unwrap();
        let hig = dim[2].parse::<u32>().unwrap();
        length += len * wid * hig;
        let collection = vec![len, wid, hig];
        let biggest = collection.iter().max().unwrap();
        let mut added: u8 = 0;
        for size in collection.iter() {
            if size < biggest {
                added += 1;
                length += 2 * size;
            }
        }
        while added < 2 {
            length += 2 * biggest;
            added += 1;
        }
        total += length;
    }
    println!("{}", total);
}
