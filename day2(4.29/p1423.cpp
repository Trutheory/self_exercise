#include<iostream>
using namespace std;

int main(){
    double s;
    double s1 = 0;
    double current = 2.0;
    int step = 0;

    cin >> s;
    while(s1 < s){
        s1 += current;
        step++;
        current *= 0.98;
    }
    cout << step << endl;
    return 0;
}