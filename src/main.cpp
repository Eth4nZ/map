#include <vector>
#include <iostream>
#include <stdexcept>
#include "FloydWarshall.h"
#include "readsql.h"

using namespace std;

int main(){
    int nodes, edges, queries;
    int from, to;
    string curRouteID, lastRouteID;
    string fromName, toName;
    int cost;

    edges = 0;
    nodes = 71;
    Graph g = Graph(nodes);
    eSQL e = eSQL();
    e.readGraph(g, nodes, edges);

    cout << "please input queries: ";
    cin >> queries;


    vector<int> path;
    for(int i = 0; i < queries; i++){
        cin >> from;
        cin >> to;
        try{
            path = g.findShortestPath(from, to);
            e.readStation(path[1], fromName);
            if(path[0] < 9999999){
                cout << "cost = " << path[0] << endl;
                cout << fromName;
                for(int i = 2; i < path.size(); i++){
                    e.readLink(path[i-1], path[i], curRouteID, lastRouteID, cost);
                    e.readStation(path[i], toName);
                    cout << "--" << curRouteID << "/" << cost << "m--" << toName;
                }
                cout << endl;
            }
            else
                cout << "NO PATH" << endl;
        }catch(logic_error& e){
        cout << e.what() << endl;
        }
    }
    return 0;
}
