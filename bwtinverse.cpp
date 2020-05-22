#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <string.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <float.h>
#include <cstdlib>
#include<ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string InverseBWT(const string& bwt) {
    string ans="";
    vector<pair<char, int>> s_bwt;
    for (int i=0; i<bwt.size(); i++) s_bwt.push_back(make_pair(bwt[i], i));
    sort(s_bwt.begin(), s_bwt.end());
    unordered_map<int, int> LastToFirst;
    for (int i=0; i<s_bwt.size(); i++) {
        LastToFirst[s_bwt[i].second]=i;
    }
    ans+='$';
    int i=0;
    while (ans.size()<bwt.size()) {
        ans+=bwt[i];
        i=LastToFirst[i];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
