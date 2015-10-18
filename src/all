#include <vector>
#include <iostream>
#include <stdexcept>
#include "FloydWarshall.h"

using namespace std;

Graph::Graph(int nodes){
    this->nodes = nodes;

    for(int i = 0; i < nodes; i++){
        vector<int> row;
        for(int j = 0; j < nodes; j++){
            if(i == j){
            row.push_back(0); // Always costs 0 to go from a to a
            }
            else{
            row.push_back(999999999); // Unconnected paths are 999
            }
        }
        this->adjacency_matrix.push_back(row);
    }
}

void Graph::connect(int from, int to, int cost){
    // Account for 0 indexing
    from--;
    to--;
    this->adjacency_matrix[from][to] = cost;
}

vector<int> Graph::findShortestPath(int from, int to){
    if(from == to){
        vector<int> path;
        path.push_back(0);
        path.push_back(from);
        path.push_back(to);
        return path;
    }

    // Account for 0 indexing
    from--;
    to--;

    // Copy adjacency matrix to prevent side effects
    vector<vector<int> > adjacency_matrix_copy = this->adjacency_matrix;
    vector<vector<int> > next;

    // Initialize our path vector

    for(int i = 0; i < this->nodes; i++){
        vector<int> row;
        for(int j = 0; j < this->nodes; j++){
            row.push_back(j);
        }
        next.push_back(row);
    }

    for(int i = 0; i < this->nodes; i++){
        for(int j = 0; j < this->nodes; j++){
            for(int k = 0; k < this->nodes; k++){
                if(adjacency_matrix_copy[j][k] >
                        adjacency_matrix_copy[j][i]
                        + adjacency_matrix_copy[i][k]){
                    adjacency_matrix_copy[j][k] =
                        adjacency_matrix_copy[j][i]
                        + adjacency_matrix_copy[i][k];
                    next[j][k] = next[j][i];
                }
            }
        }
    }

    if(next[from][to] == 0){
        throw logic_error("NO PATH"); // Fix this exception
    }

    vector<int> path;

    path.push_back(adjacency_matrix_copy[from][to]);
    path.push_back(from + 1);
    while(from != to){
        from = next[from][to];
        path.push_back(from + 1);
    }

    return path;
}

