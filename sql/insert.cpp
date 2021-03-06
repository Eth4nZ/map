#include <iostream>
#include <mysql++.h>
#include <unistd.h>

using namespace std;
using namespace mysqlpp;

bool insertRoute(string routeID){
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT * FROM Route where id = '" << routeID << "';";
        StoreQueryResult ares = query.store();
        if(ares.num_rows() > 0){
            cerr << "exist duplicated route: " << routeID << endl;
        }
        else{
            query << "insert into Route" << "(id) values" << "(" << "'" << routeID << "');";
            query.execute();
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

bool insertStation(string name, string routeID, int &st){
    StoreQueryResult ares;

    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT COUNT(*) AS Station_count FROM Station;";
        ares = query.store();
        query << "ALTER TABLE Station AUTO_INCREMENT = " << ares[0]["Station_count"]+1 << ";";
        query.execute();

        query << "SELECT * FROM Station where name = '" << name << "';";
        ares = query.store();
        if(ares.num_rows() > 0){    //if we have the duplicate staton;
            st = ares[0]["id"];
            //cerr << "exist duplicate station: "<< name << endl;
        }
        else{
            query << "insert into Station " << "(name, routeID) values" << "(" << "'" << name << "', '" << routeID << "');";
            query.execute();
            query << "SELECT * FROM Station where name = '" << name << "';";
            ares = query.store();
            st = ares[0]["id"];
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

bool insertLink(int sfrom, int sto, string routeID, int cost){
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "insert into Link" << "(sfrom, sto, routeID, cost) values" << "(" << sfrom << ", " << sto <<  ", '" << routeID << "', " << cost << ");";
        query.execute();
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
int main() {
    string name1, name2;
    string routeID;
    int st1, st2;
    int route_count, station_count, cost;
    cin >> route_count;
    for(int t = 0; t < route_count; t++){
        cin >> routeID >> station_count;
        insertRoute(routeID);
        cin >> name1;
        insertStation(name1, routeID, st1);
//        station_count = 4;
        if(routeID == "foot"){
            cin >> cost;
            cin >> name2;
            insertStation(name2, routeID, st2);
            insertLink(st1, st2, routeID, cost);
            insertLink(st2, st1, routeID, cost);
        }
        else{
            for(int i = 1; i < station_count; i++){
                cin >> cost;
                cin >> name2;
                insertStation(name2, routeID, st2);
                insertLink(st1, st2, routeID, cost);
                st1 = st2;
            }
            cout << "completed: " << routeID << endl;
        }
    }
}


