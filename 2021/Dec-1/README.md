# Day one of Advent of code

## Part 1

Part 1 was simple. Reading in a file, converting to integers then tracking increases in value.
nothing interesting to note here.

## Part 2

Sum of a sliding window of summations. Adding more integers to store previous values with a cycle to
get rid of old values and replace them with new ones.

Oh boy i don't feel good about that one. My strategy was to just compare the uncommon values between them
instead of taking the full sum. I would read in the values and create this cycle of values. Something went
wrong in my cycle so I instead just read all of the values into a definite array of length 2000 (size of data list)
and then looped through the array starting at index 3 and comparing to index-3 for the difference in sum.

my initial method would have resulted in one loop through the data but something was causing me to add one additional
number to the count. With my successful method I had to loop through the values two times which means O(n**2).
