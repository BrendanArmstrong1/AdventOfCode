# Day Eight of Advent of code

## Part 1

Haven't done AoC for a few days as I was helping a friend move. Part 1 was a good reintroduction into
coding. I though I would need regex when I first saw the input. It turns out all I needed was strtok
and then I had to count the letters. Now on to part 2.

## Part 2

Goodness this took a long time. I first tried for a few hours to get regular expressions
working in the C library. This did not work but it was a good journey. I read
the man pages multiple times and learned a lot about regex manipulation in the
C posix library.

I then got the idea to measure the frequecy of usage for each of the seven segment
lights that displays the number. each segment was characterized by the frequency with
which it is used. This means that there are two lights used 8 times and two lights
used 7 times but the other three lights are used 6, 4, and 9 times. This was a solid
foundation from which to decrypt these numbers.

The next thing I did was to add up the total number of frequencies used by each number.
This came out to each number having a unique identifying sum that I then scanned though
in my code. If you look at my part 2 code you will see a lot of magic numbers in the
output tokenized string. Those numbers are the characteristic signature of the displayed
numbers. Using this strategy I could find the value, convert it to a number, then add
it to the total. This was a tough one.
