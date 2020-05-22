#include <utility>
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
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> updateOrder(int L, vector<int>& orders, vector<int>& classes, const string& text) {
    vector<int> neworders(text.size(), 0), cnts(text.size(), 0);
    for (int i=0; i<text.size(); i++) {
        if (text[i]=='$') cnts[0]++;
        else cnts[classes[i]]++;
    }
    for (int i=1; i<cnts.size(); i++) {
        cnts[i]+=cnts[i-1];
    }
    int start, cl, S= (int) text.size();
    for (int i=S-1; i>=0; i--) {
        start = (orders[i] - L + S) % S;
        cl = classes[start];
        cnts[cl]--;
        neworders[cnts[cl]] = start;
    }
    return neworders;
}
vector<int> updateClasses(int L, vector<int>& orders, vector<int>& classes, const string& text) {
    vector<int> newclasses(text.size(), 0);
    int S= (int) text.size(), ii, ii_1;
    for (int i=1; i<text.size(); i++) {
        ii=orders[i];
        ii_1=orders[i-1];
        if (classes[ii] == classes[ii_1] &&\
            classes[(ii+L)%S] == classes[(ii_1+L)%S])
            newclasses[ii] = newclasses[ii_1];
        else newclasses[ii] = newclasses[ii_1] + 1;
    }
    return newclasses;
}


vector<int> BuildSuffixArray(const string& text) {
    vector<int> orders(text.size(), 0), classes(text.size(), 0), cnts(27, 0);
    for (int i=0; i<text.size(); i++) {
        if (text[i]=='$') cnts[0]++;
        else cnts[text[i]-'A'+1]++;
    }
    for (int i=1; i<cnts.size(); i++) {
        cnts[i]+=cnts[i-1];
    }
    for (int i= (int) text.size()-1; i>=0; i--) {
        if (text[i]=='$'){
            cnts[0]--;
            orders[cnts[0]] = i;
        } else {
            cnts[(text[i]-'A')+1]--;
            orders[cnts[(text[i]-'A')+1]] = i;
        }
    }
    for (int i=1; i<orders.size() ; i++) {
        if (text[orders[i-1]] != text[orders[i]] )
            classes[orders[i]]=classes[orders[i-1]]+1;
        else classes[orders[i]]=classes[orders[i-1]];
    }
    int L=1, S= (int) text.size();
    while (L<S) {
        orders=updateOrder(L, orders, classes, text);
        classes=updateClasses(L, orders, classes, text);
        L<<=1;
    }
    return orders;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
