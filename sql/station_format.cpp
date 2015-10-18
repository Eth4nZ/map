#include <iostream>
#include <string>

using namespace std;

int main(){
    int n, cost;
    string id, s;

    cin >> id;
    cin >> n;
    cin >> cost;
    cost = cost*1000/n;
    cin >> s;
    cout << id << " " << n << endl;
    cout << s;
    for(int i = 1; i < n; i++){
        cin >> s;
        cout << " " << cost << " " << s;
    }
    cout << endl;
}
