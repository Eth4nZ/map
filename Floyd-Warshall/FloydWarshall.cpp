#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Graph{
private:
    int nodes;
    vector<vector<int> > adjacency_matrix;
public:
    Graph(int nodes);
    vector<int> findShortestPath(int from, int to);
    void connect(int from, int to, int cost);
};

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


// Main

int main(){
    int nodes, edges, queries;
    int from, to, cost;
    cin >> nodes;
    cin >> edges;
    cin >> queries;

    Graph g(nodes);
    for(int i = 0; i < edges; i++){
        cin >> from;
        cin >> to;
        cin >> cost;

        g.connect(from, to, cost);
    }

    vector<int> path;
    for(int i = 0; i < queries; i++){
        cin >> from;
        cin >> to;
        try{
            path = g.findShortestPath(from, to);
            cout << "cost = " << path[0] << endl;
            for(int i = 1; i < path.size() - 1; i++){
                cout << path[i] << "-";
            }
            cout << path.back() << endl;
        }catch(logic_error& e){
        cout << e.what() << endl;
        }
    }
    return 0;
}
