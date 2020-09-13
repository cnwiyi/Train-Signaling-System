# Simulating a Train Traffic and Signalling Systems:

### to run:
make
> ./main tracks.txt trains.txt

to clean directory:
> make -clean

ps: must be entered in that order arg1 tracks file and arg2 trains file


## Assumptions:
- All trains in the network are are moving in the same direction. 
- All trains are moving along each segment at the same speed of 1sec/segment. 
- All segments in network are the same length.
- All trains are of the same length and Segments are also the same lengths as trains.
- All junctions are limited to a max of two connecting segments.


## Input file makeup:
### FILE 1: tracks.txt

this file provides all the possible paths in the system
- line 1: number of segments (tracks)
- line 2..n: paths from start to finish (segment connections)

examples:

For train tracks network:
```
(0)----(1)----(2)----(3)----(4)
               |             
               |               
              (5)----(6)----(7)            
               |      |              
               |      |
              (10)   (8)----(9)
```

tracks.txt
```
10
0 1 2 3 4
0 1 2 5 6 7
0 1 2 5 6 8 9
0 1 2 5 10
```
*todo: [Optimize] to below, minimize user input and remove number of nodes line.*
```
0 1 2 3 4
2 5 6 7
5 6 8 9
5 10
```

Guide to adding to file (to add checks in code; track integrity):
- paths should be always be from 0 to n (n = number of segments)
- new tracks are built into the system via text file eg: 0 1 2 3 10 11

### FILE 2: trains.txt
Start and end stations of the trains. Number of lines equals number of trains to be put in system.

trains.txt
```
0 4
1 7
2 9
```

## Improvements and Optimizations:
- trains text file should take in train name, start station, end station, train length and train speed (sec/segment).
