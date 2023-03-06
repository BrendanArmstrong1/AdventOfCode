use std::{
    collections::{HashSet, VecDeque},
    fs,
};

fn main() {
    let file = fs::read_to_string("input.txt").unwrap();
    part1(&file);
    part2(&file);
}

#[allow(unused_variables)]
fn part1(f: &String) {
    // find the index of the last character of a four character
    // unique string
    let mut string_iter = f.chars().enumerate();
    let mut marker_string: VecDeque<char> = VecDeque::with_capacity(10);
    let mut marker_set: HashSet<char> = HashSet::with_capacity(10);

    'marker_find: while let Some((i, ch)) = string_iter.next() {
        marker_string.push_back(ch);
        marker_set.insert(ch);

        if marker_string.len() == 4 {
            if marker_set.len() == 4 {
                println!("{},{:?},{:?}", i + 1, marker_set, marker_string);
                break 'marker_find;
            }
            let temp = marker_string.pop_front().unwrap();
            if !marker_string.contains(&temp) {
                marker_set.remove(&temp);
            }
        }
    }
}

fn part2(f: &String) {
    // find the index of the last character of a four character
    // unique string
    let mut string_iter = f.chars().enumerate();
    let mut marker_string: VecDeque<char> = VecDeque::with_capacity(50);
    let mut marker_set: HashSet<char> = HashSet::with_capacity(50);

    'marker_find: while let Some((i, ch)) = string_iter.next() {
        marker_string.push_back(ch);
        marker_set.insert(ch);

        if marker_string.len() == 14 {
            if marker_set.len() == 14 {
                println!("{},{:?},{:?}", i + 1, marker_set, marker_string);
                break 'marker_find;
            }
            let temp = marker_string.pop_front().unwrap();
            if !marker_string.contains(&temp) {
                marker_set.remove(&temp);
            }
        }
    }
}
