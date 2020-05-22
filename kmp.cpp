#include <cstdio>
#include <iostream>
#include <utility>
#include <cstdio>
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
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
char value(int i, const string& pattern, const string& text){
    if (i<pattern.size()) return pattern[i];
    if (i==pattern.size()) return '$';
    return text[i-pattern.size()-1];
}

vector<int> find_pattern(const string& pattern, const string& text) {
    if (pattern.size()>text.size()) return {};
    vector<int> ans, lp(pattern.size() +1+ text.size(), 0);
    int P = (int) pattern.size(), j;
    for (int i=1; i<pattern.size() +1+ text.size(); i++) {
        if (value(i, pattern, text)==value(lp[i-1], pattern, text)) lp[i]=lp[i-1]+1;
        else {
            j = i-1;
            //cout<<"i "<<i<<endl;
            while (j>=0 && value(i, pattern, text)!=value(lp[j], pattern, text)) {
                j = lp[j]-1;
                //cout<<"j "<<j<<endl;
            }
                
            if (j>=0 && value(i, pattern, text)==value(lp[j], pattern, text)) lp[i]=lp[j]+1;
        }
        if (lp[i]==P) ans.push_back(i-2*P);
    }
    //for (auto& l:lp) cout<<l<<" ";
    //cout<<endl;
    return ans;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
