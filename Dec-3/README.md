# Day three of Advent of code

## Part 1

Ok this one was messed up. So in part1 I was able to simply count the columns of digits and find the numbers quite easily.
But then came part two...


## Part 2

Part 2 had refactoring and weird indices along with multiple scans through the array. I didn't like this solution as I ended up
retrieving the numbers through an iterative process and using a hand calculator to find the product. 

Things I learned through this exercise:

- When dealing with long numbers, like binary representation, it is easier to use strings rather than bit shifting. The number
itself was so long that it intrinsically was cast as a long int. So bit shifting became a whole process. String manipulation is
easier.
- Indices when running an array must take into account new line chars and null terminations. Also, when converting from a binary
string to decimal, remember to use the correct power of 2 in the right index. a 12 bit number starts with 2<sup>11</sup> and then
eventually gets down to 2<sup>0</sup>.

Hopefully tomorrows challenge won't have pesky binary numbers.
