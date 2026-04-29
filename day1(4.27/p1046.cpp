#include<iostream>
using namespace std;

int main(){
    int a[10];
    int high;
    int num = 0;
    for(int i = 0; i < 10; i++){
        cin >> a[i];
    }

    cin >> high;
    high = high + 30;

    for(int i = 0; i < 10;i++){
        if(a[i] <= high){
            num++;
        }
    }

    cout << num << endl;
    return 0;
}