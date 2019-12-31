#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

int calc(const vector<int>& vec) {
    queue<int> q;  //保存页面次序
    vector<int> v(3); //保存页面
    int len = vec.size();
    int time = 1;
    for (int i = 0; i < len; ++i) {
        if (time < 4) {
            v[i] = vec[i];
            q.push(vec[i]);
            cout << "第" << time++ << "次缺页：" << vec[i] << endl;
        }
        else {
            if (find(v.begin(), v.end(), vec[i]) == v.end()) {
                int page = q.front();
                q.pop();
                q.push(vec[i]);
                *find(v.begin(), v.end(), page) = vec[i];
                cout << "第" << time++ << "次缺页：" << vec[i] << endl;
            }
        }
    }
    return --time;
}

int main(int argc, char *argv[]) {
    int N;  //页面置换总数
    cin >> N;
    vector<int> vec(N);  //页面序列
    int page;
    for (int i = 0; i < N; ++i) {
        cin >> page;
        vec[i] = page;
    }
    int missPage = calc(vec);
    cout << missPage << endl;
    getchar();
    return 0;
}
