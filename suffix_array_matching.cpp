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
using std::string;
using std::vector;
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
bool comp1(int j, const string& b, const string& text){
    //b pattern
    string a=text.substr(j);
    for (int i=0; i<a.size(); i++ ) {
        if (a[i] == b[i]) continue;
        else return a[i] < b[i];
    }
    return a.size()<b.size();
}
bool comp2(int j, const string& b, const string& text){
    string a=text.substr(j);
    if (a.size()<b.size()) return false;
    for (int i=0; i<a.size() && i<b.size(); i++ ) {
        if (a[i] == b[i]) continue;
        else return false;
    }
    return true;
}


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
    vector<int> ans;
    int left=0, right= (int) text.size()-1, mid, L, R;
    while (left<=right) {
        mid=(left+right)/2;
        if (comp1(suffix_array[mid], pattern, text)){
            left=mid+1;
        } else {
            right=mid-1;
        }
    }
    L=left;
    right= (int) text.size()-1;
    while (left<=right) {
        mid=(left+right)/2;
        if (comp2(suffix_array[mid], pattern, text)){
            left=mid+1;
        } else {
            right=mid-1;
        }
    }
    R=left-1;
    //cout<<L<<" R "<<R<<endl;
    for (int i=L; i<=R; i++) {
        ans.push_back(suffix_array[i]);
    }
        
    
    return ans;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
