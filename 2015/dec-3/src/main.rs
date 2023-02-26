use std::{collections::HashMap, fs};

fn main() {
    let file = fs::read_to_string("../input.txt").unwrap();
    // part1(&file);
    part2(&file);
}

fn _part1(file: &str) {
    let mut houses = HashMap::new();
    let mut x = 0;
    let mut y = 0;
    for i in file.chars() {
        let key = format!("{},{}", x, y);
        let counter = houses.entry(key).or_insert(0);
        *counter += 1;
        if i == '^' {
            y += 1; 
        }
        if i == '>' {
            x += 1;    
        }
        if i == '<' {
            x -= 1;    
        }
        if i == 'v' {
            y -= 1; 
        }
    }
    let key = format!("{},{}", x, y);
    let counter = houses.entry(key).or_insert(0);
    *counter += 1;
    println!("{}", houses.len())
}

fn part2(file: &str) {
    let mut houses: HashMap<_, i32> = HashMap::new();
    let mut x1 = 0;
    let mut y1 = 0;
    let mut x2 = 0;
    let mut y2 = 0;
    let mut x;
    let mut y;
    let mut actor = 0;
    for i in file.chars() {
        if actor == 0 {
            x = &mut x1;
            y = &mut y1;
        }else {
            x = &mut x2;
            y = &mut y2;
        }
        let key = format!("{},{}", *x, *y);
        let counter = houses.entry(key).or_insert(0);
        *counter += 1;
        if i == '^' {
            *y += 1; 
        }
        if i == '>' {
            *x += 1;    
        }
        if i == '<' {
            *x -= 1;    
        }
        if i == 'v' {
            *y -= 1; 
        }
        if actor == 0 {
           actor = 1; 
        }else {
            actor = 0;
        }
    }
    let key = format!("{},{}", x1, y1);
    let counter = houses.entry(key).or_insert(0);
    *counter += 1;
    let key = format!("{},{}", x2, y2);
    let counter = houses.entry(key).or_insert(0);
    *counter += 1;
    println!("{}", houses.len())
}
