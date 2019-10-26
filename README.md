# Building-Metagraph-Algorithm
Graphs represented in the form of adjacency lists.
Algorithm finds strongly connected components (SCC) and prints them out.
Then goes meta-graph building and printing it in the form of adjacency lists

## Complexity
Average complexity is **O(|V| + |E|)**, where **|V|** - number of vertices, **|E|** - number of edges

## Input Data
* *verticesCount* - number of vertices in the graph
* *adjacency lists* of graph ending with '-1' after every list

## Example
### Input
```
6 // number of vertices

// adjacency lists
0 1 -1
1 2 3 -1
2 0 3 -1
3 4 -1
4 3 -1
5 5 -1
```
![alt text](https://graphonline.ru/tmp/saved/IT/ITZbEqLsFfcoqxCD.png)
### Output
```
SCC 0: 5 
SCC 1: 4 3 
SCC 2: 2 1 0 

Meta-graph:
0   
1   
2   1 
```
![alt text](https://graphonline.ru/tmp/saved/lv/lvnlLUghGDYxKsUt.png)
