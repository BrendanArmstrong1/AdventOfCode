# Day Fourteen of Advent of code

## Part 1

I saw quickly that I had to think about this problem in a more efficient way. I started
drawing out the transformations and noticed that there were loops of activity.
I then noticed that every bi-graph split into two different bi-graphs on each step.
This meant a binomial tree.

I created a structure for each bi-graph, with elements to point to the left
and right transformed bi-graphs. On each step the amount of original bi-graphs
gets added to the transformed bi-graphs. I then reset the relevant amounts
after each step and counted the inserted letters as I went.

## Part 2

Part two was basically already solved, just had to change integers to
unsigned longs in order to contain the size of the number.
