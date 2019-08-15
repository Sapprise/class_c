/*************************************************************************
	> File Name: jisuanke.cpp
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年08月15日 星期四 15时42分04秒
 ************************************************************************/

#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> PII;
set<PII> p[101];

int main() {
    int t, n, f, s, max = 0, mj, ms;
    cin >> t;
    int data[50005][2][2];
    int nums[t + 1];
    for (int i = 1; i <=t; i++) {
        cin >> n;
        nums[i] = n;
        for (int j = 1; j <= n; j++) {
            cin >> data[i][j][0] >> data[i][j][1];
        }
    }

    for (int i = 1; i <= t; i++) {
        n = nums[i];
        for (int j = 1; j <= n; j++) {
            f = data[i][j][0], s = data[i][j][1];
            p[s].insert(PII(-f, j));
            if (f > max) mj = j, ms = s, max = f;
        }
        cout << "Case #" << i << ":" << endl;
        cout << mj;
        p[ms].erase(p[ms].begin());
        n--;
        int time = 1, l;
        while (time <= n) {
            max = 0, mj = 0, ms = 0;
            for (int k = 1; k <= 100; k++) {
                if (p[k].empty()) continue;
                l = -p[k].begin()->first + k * time;
                if ( l > max) max = l, mj = p[k].begin()->second, ms = k;
            }
            cout << " " << mj;
            p[ms].erase(p[ms].begin());
            time++;
        }
        cout << endl;
    }
    return 0;
}
