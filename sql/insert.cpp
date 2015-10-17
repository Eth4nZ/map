#include <mysql/mysql.h>
#include <iostream>

using namespace std;

int main(){
    MYSQL mysql;
    mysql_init(&mysql);

    mysql_real_connect(&mysql, "localhost", "root", "dtbs", "map", 3306, NULL, 0);
    const char* sql = "select * from Station;";

    mysql_query(&mysql, sql);

    MYSQL_RES* result = mysql_store_result(&mysql);

    cout << "Station rows: " << mysql_num_fields(result) << endl;

    int i = 0;
    MYSQL_ROW row = mysql_fetch_row(result);
    for(int i = 0; i < mysql_num_fields(result); i++){
        MYSQL_FIELD* field = mysql_fetch_field_direct(result, i);
        cout << field->name << ": " << row[i] << " ";
    }

    mysql_close(&mysql);
    return 1;
}
