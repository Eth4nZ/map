#include "readsql.h"

using namespace std;
using namespace mysqlpp;

eSQL::eSQL(){
}

bool eSQL::readGraph(Graph &g, int &nodes, int &edges){
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT COUNT(*) AS Station_count FROM Station;";
        ares = query.store();
        nodes = ares[0]["Station_count"];
        Graph g0(nodes);

        query << "SELECT * FROM Link;";
        ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++){
            edges++;
            g0.connect(ares[i]["sfrom"], ares[i]["sto"], ares[i]["cost"]);
        }
        g = g0;
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readStation(int id, string &name){
    name = "";
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();
        query << "SELECT * FROM Station where id = " << id << ";";
        StoreQueryResult ares = query.store();
        name.append(ares[0]["name"]);
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readLink(int sfrom, int sto, string &routeID, string lastRouteID, int &cost){
    StoreQueryResult ares;
    int cost_temp;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();
        query << "SELECT * FROM Link where sfrom = " << sfrom << " and sto = " << sto <<  ";";
        StoreQueryResult ares = query.store();
        if(ares.num_rows() > 1){
            int mincost = ares[0]["cost"];
            routeID = "";
            routeID.append(ares[0]["routeID"]);
            for (size_t i = 0; i < ares.num_rows(); i++){
                if(ares[i]["routeID"] == lastRouteID){
                    routeID = "";
                    routeID.append(ares[i]["routeID"]);
                    cost = ares[i]["cost"];
                }
                else{
                    cost_temp = ares[i]["cost"];
                    if(cost_temp < mincost){
                        mincost = ares[i]["cost"];
                        routeID = "";
                        routeID.append(ares[i]["routeID"]);
                    }
                }
            }
        }
        else{
            routeID = "";
            routeID.append(ares[0]["routeID"]);
            cost = ares[0]["cost"];
        }
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

