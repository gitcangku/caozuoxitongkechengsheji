#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include <map>
#include <vector>
int N, k;
string s;

void fifo(int A, string opda, int B = 0) {
    vector<char> v;
    int j, pageFaultTime = 0;
    for (int i = 0; i < A; ++i) {
        for (j = 0; j < v.size(); ++j) {
            if (s[i] == v[j]) break;
        }
        if (j == v.size()) { // page fault
            pageFaultTime += 1;
            if (v.size() == N) { //  full
                                 // choose a victim
                vector<char> nv;
                for (j = 1; j < v.size(); ++j) {
                    nv.push_back(v[j]);
                }
                nv.push_back(s[i]);
                v = nv;
            }
            else { // no full
                v.push_back(s[i]);
            }
        }
    }
    if (opda[0] == 's') {
        for (j = 0; j < v.size(); ++j) {
            cout << v[j];
        }
        cout << endl;
    }
    else if (opda[0] == 'p') {
        cout << pageFaultTime << endl;
    }
    else {
        for (j = 0; j < v.size(); ++j) {
            if (v[j] - '0' == B) {
                cout << 1 << endl;
                return;
            }
        }
        cout << 0 << endl;
    }
}


void LRU(int A, string opda, int B = 0) {
    vector < pair<char, int> > v;
    int j, pageFaultTime = 0;
    for (int i = 0; i < A; ++i) {
        for (j = 0; j < v.size(); ++j) {
            if (s[i] == v[j].first) {
                v[j].second = i; // refresh the time stamp
                break;
            }
        }
        if (j == v.size()) { // page fault
            pageFaultTime += 1;
            if (v.size() == N) { //  full
                                 // choose a victim
                int MIN, MINIndex;
                for (j = 0; j < v.size(); ++j) {
                    if (j == 0 || MIN > v[j].second) {
                        MIN = v[j].second;
                        MINIndex = j;
                    }
                }
                v[MINIndex] = make_pair(s[i], i);
            }
            else { // no full
                v.push_back(make_pair(s[i], i));
            }
        }
    }
    if (opda[0] == 's') {
        for (j = 0; j < v.size(); ++j) {
            cout << v[j].first;
        }
        cout << endl;
    }
    else if (opda[0] == 'p') {
        cout << pageFaultTime << endl;
    }
    else {
        for (j = 0; j < v.size(); ++j) {
            if (v[j].first - '0' == B) {
                cout << 1 << endl;
                return;
            }
        }
        cout << 0 << endl;
    }
}


void OPT(int A, string opda, int B = 0) {
    vector < pair<char, int> > v;
    vector < int > vi;
    map<char, int> timeMap;
    map<char, int>::iterator iter;
    for (int i = 0; i < s.size(); ++i) {
        iter = timeMap.find(s[i]);
        if (iter == timeMap.end()) {
            timeMap.insert(make_pair(s[i], 1));
        }
        else {
            timeMap[s[i]] += 1;
        }
    }
    int j, pageFaultTime = 0;
    for (int i = 0; i < A; ++i) {
        for (int k = 0; k < v.size(); ++k) {
            int moren = 1<<30;
            for (int m = i+1; m < s.size(); ++m) {
                if (s[m] == v[k].first) {
                    moren = m; break;
                }
            }
            vi[k] = moren;
        }
        for (j = 0; j < v.size(); ++j) {
            if (s[i] == v[j].first) {
                v[j].second = i; // refresh the time stamp
                timeMap[s[i]] -= 1;
                break;
            }
        }
        if (j == v.size()) { // page fault
            pageFaultTime += 1;
            if (v.size() == N) { //  full
                                 // choose a victim
                                 // more than one choice.
                int MINIndex;
                for (j = 0; j < v.size(); ++j) {
                    if (j == 0 || vi[j] > vi[MINIndex] || (vi[j] == vi[MINIndex] && v[j].second < v[MINIndex].second)) {
                        MINIndex = j;
                    }
                }
                v[MINIndex] = make_pair(s[i], i);
            }
            else { // no full
                v.push_back(make_pair(s[i], i));
                vi.push_back(0);
            }
        }
    }
    if (opda[0] == 's') {
        for (j = 0; j < v.size(); ++j) {
            cout << v[j].first;
        }
        cout << endl;
    }
    else if (opda[0] == 'p') {
        cout << pageFaultTime << endl;
    }
    else {
        for (j = 0; j < v.size(); ++j) {
            if (v[j].first - '0' == B) {
                cout << 1 << endl;
                return;
            }
        }
        cout << 0 << endl;
    }
}

int main() {
    cin >> N >> s;
    cin >> k;
    int op, A, B = 0;
    string opda;
    for (int i = 0; i < k; ++i) {
        cin >> op >> opda >> A;
        if (opda[0] == 'g') cin >> B;
        if (op == 1) {
            fifo(A, opda, B);
        }
        else if (op == 2) {
            LRU(A, opda, B);
        }
        else {
            OPT(A, opda, B);
        }
    }
}
————————————————
版权声明：本文为CSDN博主「肥宅_Sean」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/a19990412/article/details/80826854
