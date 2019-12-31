#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include <map>
#include <vector>
int N, k;
string s;

void fifo() {
    cout << "FIFO\n";
    vector<char> v;
    int j, pageFaultTime = 0;
    for (int i = 0; i < s.size(); ++i) {
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
        for (int k = 0; k < v.size(); ++k) {
            cout << v[k]<<" ";
        }
        cout << endl;
    }

}


void LRU() {
    cout << "LRU\n";
    vector < pair<char, int> > v;
    int j, pageFaultTime = 0;
    for (int i = 0; i < s.size(); ++i) {
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
        for (int k = 0; k < v.size(); ++k) {
            cout << v[k].first<<" ";
        }
        cout << endl;
    }
}


void OPT() {
    cout << "OPT\n";
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
    for (int i = 0; i < s.size(); ++i) {
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
        for (int k = 0; k < v.size(); ++k) {
            cout << v[k].first<<" ";
        }
        cout << endl;
    }

}

int main() {
    cin >> N >> s;
    cin >> k;
    int op, A, B = 0;
    string opda;
    fifo();
    LRU();
    OPT();
}