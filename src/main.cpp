#include <vector>
#include <iostream>
#include <stdexcept>
#include "FloydWarshall.h"

using namespace std;

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
            for(int i = 1; i < path.size()-1; i++){
                cout << path[i] << "-";
            }
            cout << path.back() << endl;
        }catch(logic_error& e){
        cout << e.what() << endl;
        }
    }
    return 0;
}
