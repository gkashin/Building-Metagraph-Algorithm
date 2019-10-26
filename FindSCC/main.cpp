//
//  main.cpp
//  BuildingMetagraph
//
//  Created by Георгий Кашин on 16.10.2019.
//  Copyright © 2019 Georgii Kashin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

class BuildingMetagraph {
    
public:
    
    BuildingMetagraph(int n) {
        // Initializing
        sourceGraph = vector<list<int>>(n);
        reversedGraph = vector<list<int>>(n);
        visited = vector<bool>(n, false);
        preValues = vector<int>(n, 0);
        postValues = vector<int>(n, 0);
        sccNumbers = vector<int>(n, 0);
        postIncreaseOrder = vector<int>(n);
        
        // Graph input (represented by adjacency lists)
        int vertex;
        int next;
        for (int i = 0; i < n; ++i) {
            // entering of vertex
            cin >> vertex;
            // entering of next vertex adjacent to first one
            cin >> next;
            while (next != -1) {
                sourceGraph[vertex].push_back(next);
                reversedGraph[next].push_back(vertex);
                cin >> next;
            }
        }
    }
    
    /// Metagraph building
    /// Complexity O(|V| + |E|)
    void build() {
        // Depth first search for reversedGraph
        dfs();
        // Depth first search for vertices by decrease post-values
        dfsForPostDecreaseValuesVertices();
        metagraph = vector<unordered_set<int>>(sccCount);
        
        for (int vertex = 0; vertex < sourceGraph.size(); ++vertex) {
            for (int neighbor : sourceGraph[vertex]) {
                if (sccNumbers[vertex] != sccNumbers[neighbor]) {
                    metagraph[sccNumbers[vertex] - 1].insert(sccNumbers[neighbor] - 1);
                }
            }
        }
    }
    
    /// Output SCCs and metagraph as adjacency lists
    void output() {
        // Output SCCs
        int size = static_cast<int>(sccNumbers.size());
        for (int vertex = size - 1; vertex >= 0; --vertex) {
            int vertexComponentNumber = sccNumbers[vertex];
            if (vertexComponentNumber != -1) {
                cout << endl << "SCC " << vertexComponentNumber - 1 << ": " << vertex << " ";
                for (int neighbor = vertex - 1; neighbor >= 0; --neighbor) {
                    int* neighborComponentNumber = &sccNumbers[neighbor];
                    if (*neighborComponentNumber == vertexComponentNumber) {
                        cout << neighbor << " ";
                        *neighborComponentNumber = -1;
                    }
                }
            }
        }
        cout << endl << endl;
        // Output metagraph
        outputMetagraph();
    }

private:
    
    /// Setup pre-value of vertex when visited
    /// @param vertex visited vertex
    void preVisit(int vertex) {
        preValues[vertex] = clock_++;
        sccNumbers[vertex] = sccCount;
    }
    
    /// Setup post-value of vertex when exiting
    /// @param vertex exiting vertex
    void postVisit(int vertex) {
        postValues[vertex] = clock_++;
    }
    
    /// Explore neighbor vertex if not visited
    /// @param graph explored graph
    /// @param vertex source vertex
    void explore(const vector<list<int>>& graph, int vertex) {
        visited[vertex] = true;
        preVisit(vertex);
        for (int neighborVertex : graph[vertex]) {
            if (!visited[neighborVertex]) { explore(graph, neighborVertex); }
        }
        postIncreaseOrder.push_back(vertex);
        postVisit(vertex);
    }
    
    /// Depth first search for reversedGraph
    void dfs() {
        resetVisitedToFalse();
        for (int vertex = 0; vertex < reversedGraph.size(); ++vertex) {
            if (!visited[vertex]) { explore(reversedGraph, vertex); }
        }
    }
    
    /// Depth first search for vertices by decrease post-values
    void dfsForPostDecreaseValuesVertices() {
        sccCount = 0;
        resetVisitedToFalse();
        int size = static_cast<int>(postIncreaseOrder.size());
        for (int i = size - 1; i >= 0; --i) {
            int vertex = postIncreaseOrder[i];
            if (!visited[vertex]) {
                sccCount++;
                explore(sourceGraph, vertex);
            }
        }
    }
    
    /// Setup false values for each element of visited array
    void resetVisitedToFalse() {
        for (int v = 0; v < visited.size(); ++v) { visited[v] = false; }
    }
    
    /// Output metagraph as adjacency lists
    void outputMetagraph() {
        cout << "Meta-graph:" << endl;
        for (int metaVertex = 0; metaVertex < metagraph.size(); ++metaVertex) {
            cout << metaVertex << "   ";
            for (int neighborMetaVertex : metagraph[metaVertex]) { cout << neighborMetaVertex << " "; }
            cout << endl;
        }
    }
    
    // Stored properties
    int clock_ = 1;
    int sccCount = 0;
    vector<list<int>> sourceGraph, reversedGraph;
    vector<unordered_set<int>> metagraph;
    vector<bool> visited;
    vector<int> preValues;
    vector<int> postValues;
    vector<int> sccNumbers;
    vector<int> postIncreaseOrder;
};

int main(int argc, const char * argv[]) {
    int verticesCount;
    cin >> verticesCount;
    
    // Examples of input data:
    // 6 - number of vertices
    // 0 1 -1 1 2 3 -1 2 0 3 -1 3 4 -1 4 3 -1 5 5 -1 - adjacency lists of graph ending with '-1' after every list
    // 12
    // 0 1 -1 1 2 3 4 -1 2 5 -1 3 -1 4 1 5 6 -1 5 2 7 -1 6 7 9 -1 7 10 -1 8 6 -1 9 8 -1 10 11 -1 11 9 -1
    BuildingMetagraph builder(verticesCount);
    
    builder.build();
    builder.output();
    
    return 0;
}

