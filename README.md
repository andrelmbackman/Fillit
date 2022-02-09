Fillit is a space optimization algorithm that finds the smallest square in which it can place a number (1-26) of given tetrominos.
Since this algorithm is based on Tetris, these will be called tetriminos from now on.

A tetrimino is a geometric shape consisting of 4 squares connected by the edges. There are 7 different shapes and
19 permutations if you count their rotated forms. These will be described with dots '.', indicating empty space,
and pound signs '#', indicating a square. Each tetrimino will be represented in a 4x4 format, for instance:

##..  #...  .#..  #...  .#..  .##.  ##..
##..  #...  ###.  #...  .#..  ##..  .##.
....  #...  ....  ##..  ##..  ....  ....
....  #...  ....  ....  ....  ....  ....

This program is given a file as an argument. The file must contain between 1-26 valid tetriminos, all followed by a
newline character '\n', otherwise it will exit and display an error message. Given a valid file, it will find the
smallest possible square to place these pieces without rotating them, using a recursive backtracking algorithm.
The output will consist of dots for empty space, and each tetrimino will be represented with a capital letter,
assigned in the order the pieces are presented in the file.

A file describing valid tetriminos might look like this:
....
.##.
.##.
....

..##
.##.
....
....

...#
...#
..##
....

...#
...#
...#
...#

....
####
....
....

....
..##
..#.
..#.


And if we ran ./fillit [file name], we would get the output:

DEEEE
DAAFF
DAAFC
DBBFC
BB.CC

In this case, all pieces fit inside a 5x5 square with only one extra empty space.
