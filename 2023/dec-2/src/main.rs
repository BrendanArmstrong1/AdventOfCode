use std::fs;
use std::io::{BufRead, BufReader};

fn main() {
  let file = fs::File::open("input.txt").unwrap();
  part1(file);
  let file = fs::File::open("input.txt").unwrap();
  part2(file);
}

#[derive(Debug)]
pub struct Game {
  pub id: i8,
  pub gmax: i32,
  pub rmax: i32,
  pub bmax: i32,
}

impl From<String> for Game {
  fn from(s: String) -> Self {
    if let Some((init, remainder)) = s.split_once(':') {
      let (_, id) = init.split_once(' ').unwrap();

      let mut gmax: i32 = 0;
      let mut rmax: i32 = 0;
      let mut bmax: i32 = 0;
      for round in remainder.split(';') {
        round
          .split(',')
          .map(|g| g.strip_prefix(' ').unwrap())
          .for_each(|g| {
            match g
              .split_once(' ')
              .map(|(num, color)| (num.parse().unwrap(), color))
            {
              Some((x, "blue")) => {
                if x > bmax {
                  bmax = x;
                }
              }
              Some((x, "green")) => {
                if x > gmax {
                  gmax = x;
                }
              }
              Some((x, "red")) => {
                if x > rmax {
                  rmax = x;
                }
              }
              _ => (),
            }
          })
      }

      Game {
        id: id.parse().unwrap(),
        gmax,
        rmax,
        bmax,
      }
    } else {
      Game {
        id: 0,
        gmax: 0,
        rmax: 0,
        bmax: 0,
      }
    }
  }
}

fn part1(f: fs::File) {
  let reader = BufReader::new(f);
  let mut valid_games: Vec<Game> = Vec::new();
  for line in reader.lines() {
    let game = Game::from(line.unwrap());
    if game.bmax <= 14 && game.rmax <= 12 && game.gmax <= 13 {
      valid_games.push(game);
    }
  }
  let mut id_sum: i32 = 0;
  for game in valid_games.iter() {
    id_sum += game.id as i32;
  }
  println!("{:?}", id_sum);
}

fn part2(f: fs::File) {
  let reader = BufReader::new(f);
  let mut squared_sum = 0;
  for line in reader.lines() {
    let game = Game::from(line.unwrap());
    squared_sum += game.rmax * game.bmax * game.gmax;
  }
  println!("{:?}", squared_sum);
}
