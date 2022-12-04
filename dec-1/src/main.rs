use std::{fs, collections};

fn main() {
    part1();
    part2();
}

fn part1(){
    let input = fs::read_to_string("input.txt").unwrap();
    
    let mut most = 0;

    let mut count = 0;
    for line in input.lines(){
        if line.is_empty() {
            if count > most {
                most = count;
            }
            count = 0;
            continue;
        }
        count += line.parse::<i32>().unwrap();
    }
    println!("{}", most);
}

fn part2(){
    let input = fs::read_to_string("input.txt").unwrap();

    let mut que = Vec::new();


    let mut count = 0;
    for line in input.lines(){
        if line.is_empty() {
            que.push(count);
            count = 0;
            continue;
        }
        count += line.parse::<i32>().unwrap();
    }
    que.sort();
    let sum = que.pop().unwrap() + que.pop().unwrap() + que.pop().unwrap();
    println!("{:?}", sum);
}

