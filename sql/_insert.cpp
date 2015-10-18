#include <iostream>
#include <mysql++.h>
#include <unistd.h>

using namespace std;
using namespace mysqlpp;

class Msql{
private:
    Query query;
    Connection conn;
public:
    Msql();
    ~Msql();
    bool insertRoute(string routeID);
    bool insertStation(string name, string routeID, int &st);
    bool insertStation(string name, string routeID, int &st);
};

Msql::Msql(){
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
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

bool Msql::insertRoute(string routeID){
    Query query;
    query = conn.query();

    query << "SELECT * FROM Route where id = '" << routeID << "';";
    StoreQueryResult ares = query.store();
    if(ares.num_rows() > 0){
        cerr << "exist duplicated route: " << routeID << endl;
    }
    else{
        query << "insert into Route" << "(id) values" << "(" << "'" << routeID << "');";
        query.execute();
    }
}

bool Msql::insertStation(string name, string routeID, int &st){
    Query query;
    StoreQueryResult ares;

    query = conn.query();

    cout << "SELECT COUNT(*) AS Station_count FROM Station;";
    query << "SELECT COUNT(*) AS Station_count FROM Station;";
    ares = query.store();
    cout << "ae: " << ares[0]["Station_count"] << endl;
    query << "ALTER TABLE Station AUTO_INCREMENT = " << ares[0]["Station_count"]+1 << ";";
    query.execute();

    query << "SELECT * FROM Station where name = '" << name << "';";
    ares = query.store();
    cout << "name: " << name << " routeID: " << routeID << " " << ares.num_rows() << endl;
    if(ares.num_rows() > 0){    //if we have the duplicate staton;
        st = ares[0]["id"];
        cerr << "exist duplicate station: "<< name << endl;
    }
    else{
        query << "insert into Station " << "(name, routeID) values" << "(" << "'" << name << "', '" << routeID << "');";
        query.execute();
        query << "SELECT * FROM Station where name = '" << name << "';";
        ares = query.store();
        st = ares[0]["id"];
    }
}

bool Msql::insertLink(int sfrom, int sto, string routeID, int cost){
    Query query;
    query = conn.query();

    query << "insert into Link" << "(sfrom, sto, routeID, cost) values" << "(" << sfrom << ", " << sto <<  ", '" << routeID << "', " << cost << ");";
    query.execute();
}

int main() {
    string name1, name2;
    string routeID;
    int st1, st2;
    int route_count, station_count, cost;
    Msql msql();

    cin >> route_count;
    for(int t = 0; t < route_count; t++){
        cin >> routeID >> station_count;
        msql.insertRoute(routeID);
        cin >> name1;
        msql.insertStation(name1, routeID, st1);
//        station_count = 4;
        for(int i = 1; i < station_count; i++){
            cin >> cost;
            cin >> name2;
            msql.insertStation(name2, routeID, st2);
            cout << st1 << " " << st2 << endl;
            msql.insertLink(st1, st2, routeID, cost);
            st1 = st2;
        }
    }
}


