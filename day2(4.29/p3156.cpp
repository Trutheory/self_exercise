#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
     // 用 vector 代替变长数组，标准 C++ 支持
    vector<int> coming_std(n);
    for (int i = 0; i < n; ++i) {
        cin >> coming_std[i];
    }
    for (int j = 0; j < m; ++j) {
        int pos;
        cin >> pos;
        // 第 pos 个同学，数组索引是 pos-1，直接访问
        cout << coming_std[pos - 1] << '\n';
    }

    return 0;
}
// 这段代码使用了 vector 来存储同学的到来时间，避免了变长数组的问题，并且直接通过索引访问同学的到来时间，效率更高。
//同时最后不能用endl，因为数据量大，endl会频繁刷新输出缓冲区，使用'\n'更高效。 