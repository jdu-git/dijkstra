# This is a Dijkstra graph algorithm project written in C++ from my Arizona State University course.

The command line arguments consist of ./executable <inputfile> <"DirectedGraph" or "UndirectedGraph"> <flag = 0 or 1>

DirectedGraph/UndirectedGraph determines whether the edges connecting can only go in one direction

A flag of 0 inserts new node at head and a flag of 1 inserts new nodes at the tail

The inputfile must be a text file consisting of numbers 2 numbers at the start representing the number of vertices and number of nodes

For subsequent rows needs 4 numbers:
First = edge index number
Second = source vertex u 
Third = destination vertex v
Fourth = weight w

Example data:

8 14
1 1 2 10
2 1 4 5
3 2 3 1
4 2 4 2
5 3 5 4
6 4 2 3
7 4 3 9
8 4 5 2
9 5 1 7
10 5 3 6
11 6 3 7
12 6 7 5
13 7 8 3
14 8 6 1

Once program is running, the user is able to enter these commands:
"STOP", "PrintADJ", "SinglePair", "SingleSource", "PrintLength", and "PrintPath"
