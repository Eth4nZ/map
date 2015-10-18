#ifndef READ_SQL_H_
#define READ_SQL_H_

#include <mysql++.h>
#include "FloydWarshall.h"
#include "readsql.h"

using namespace std;
using namespace mysqlpp;

class eSQL{
public:
    eSQL();

    bool readGraph(Graph&, int&, int&);
    bool readStation(int, string&);
    bool readLink(int, int, string&, string, int&);
};

#endif  //READ_SQL_H_
