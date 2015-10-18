#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    int n;
    string id;
    string s[100];
    int cost[100];

    cin >> id;
    cin >> n;
    cin >> s[0];
    for(int i = 1; i < n; i++){
        cin >> cost[i];
        cin >> s[i];
    }

    cout << id << " " << n << endl;
    cout << s[n-1];
    for(int i = n-2; i >= 0; i--){
        cout << " " << cost[i+1] << " " << s[i];
    }
    cout << endl;
}
