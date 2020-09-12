Simulating a Train Traffic and Signalling Systems:

to run:
make
./runsim ./tracks.txt ./trains.txt

to clean directory:
make -clean

ps: must be entered in that order arg1 tracks file and arg2 trains file

Assumptions:
- all trains are moving in the same direction
- all trains are moving as the same speed
- all segments are the same length
- each train is a segment long and all trains are of the same length (todo: improve to train length > 1 segment; design to accommodate improvement)
- junctions limited to max of two forks moving unidirectional (implied from Q but design to allow 3 and bidirectional tracks)

Constraints:


Input file makeup:

# FILE 1: tracks.txt

this file provides all the possible paths in the system
- line 1: number of segments (tracks)
- line 2..n: paths from start to finish (segment connections)

example:

train tracks:
(0)----(1)----(2)----(3)----(4)
               |
               |
              (5)----(6)----(7)
               |      |
               |      |
              (10)   (8)----(9)

tracks.txt
10
0 1 2 3 4
0 1 2 5 6 7
0 1 2 5 6 8 9
0 1 2 5 10

todo: [Optimize] to below, minimize user input and remove number of nodes line.
0 1 2 3 4
2 5 6 7
5 6 8 9
5 10

Guide to adding to file (to add checks in code; track integrity):
- paths should be always be from 0 to n (n = number of segments)
- new tracks are built into the system via text file eg: 0 1 2 3 10 11


# FILE 2: trains.txt

Start and end stations of the trains. Number of lines equals number of trains to be put in system.

trains.txt
0 4
1 7
2 9