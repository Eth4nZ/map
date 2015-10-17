#include<iostream>
#include<mysql++.h>

using namespace std;
using namespace mysqlpp;

int main() {
    try {
        Connection conn(false);
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        /* To insert stuff with escaping */
      /*  query << "INSERT INTO map " <<
                     "VALUES (" <<
                     "'', " << // This is left empty because the column is AUTO_INCREMENT 
                     "\"" << escape << "some_var_that_contains_some_value" << "\"" <<
                     ");";
        query.execute();*/
        /* That's it for INSERT */

        /* Now SELECT */
        query << "SELECT * FROM Station";
        StoreQueryResult ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++)
           cout << "Name: " << ares[i]["id"] << " - Address: " << ares[i]["name"] << endl;

        /* Let's get a count of something */
        query << "SELECT COUNT(*) AS station FROM Station";
        StoreQueryResult bres = query.store();
        cout << "Total rows: " << bres[0]["id"];

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
