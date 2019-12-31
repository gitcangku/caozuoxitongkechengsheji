#include<iostream>
#include<map>
#include<vector>
#include<string>

using namespace std;

int calc(const vector<int>& vec) {
    map<int, int> page_pos;  //页面对应的位置
    map<int, int> pos_page;  //位置对应的页面
    int len = vec.size();
    int time = 1;
    for (int i = 0; i < len; ++i) {
        if (page_pos.find(vec[i]) == page_pos.end()) {
            if (time < 4) {
                page_pos[vec[i]] = time;
                pos_page[time] = vec[i];
            }
            else {
                page_pos.erase(pos_page[1]);
                int page_2 = pos_page[2];
                int page_3 = pos_page[3];
                page_pos[page_2] = 1;
                page_pos[page_3] = 2;
                pos_page[1] = page_2;
                pos_page[2] = page_3;
                page_pos[vec[i]] = 3;
                pos_page[3] = vec[i];
            }
            cout << "第" << time++ << "次缺页：" << vec[i] << endl;
        }
        else {
            int page = page_pos.find(vec[i])->first;
            int pos = page_pos.find(vec[i])->second;
            switch (pos) {
            case 1:
            {
                int page_2 = pos_page[2];
                int page_3 = pos_page[3];
                page_pos[page_2] = 1;
                page_pos[page_3] = 2;
                pos_page[1] = page_2;
                pos_page[2] = page_3;
                page_pos[page] = 3;
                pos_page[3] = page; 
            }
                break;
            case 2:
            {
                int page3 = pos_page[3];
                page_pos[page3] = 2;
                page_pos[page] = 3;
                pos_page[2] = page3;
                pos_page[3] = page;
            }
                break;
            case 3:
                break;
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
