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
using std::istringstream;
using std::map;
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
// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   unordered_map<char, int>& FirstOcc,
                   unordered_map<char, vector<int> >& occ_count) {
    string i_bwt=bwt;
    sort(i_bwt.begin(), i_bwt.end());
    for (int i=0; i<i_bwt.size(); i++) {
        if (FirstOcc.find(i_bwt[i]) == FirstOcc.end() )
            FirstOcc[i_bwt[i]]=i;
    }
    for (auto& a:FirstOcc) {
        occ_count[a.first] = vector<int>(bwt.size()+1, 0);
    }
    for (int i=1; i<=bwt.size(); i++) {
        for (auto& a:occ_count) {
            if (a.first==bwt[i-1])
                occ_count[a.first][i]=occ_count[a.first][i-1]+1;
            else occ_count[a.first][i]=occ_count[a.first][i-1];
        }
    }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const unordered_map<char, int>& FirstOcc,
                     const unordered_map<char, vector<int> >& occ_count) {
    int top=0, bottom=(int) bwt.size()-1;
    for (int i= (int) pattern.size()-1; i>=0 && top<=bottom; i--) {
        char c=pattern[i];
        if (FirstOcc.find(c)==FirstOcc.end()) return 0;
        top = FirstOcc.at(c) + occ_count.at(c)[top];
        bottom = FirstOcc.at(c) + occ_count.at(c)[bottom+1]-1;
        //cout<<top<<" bottom "<<bottom<<endl;
    }
    return bottom-top+1;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  unordered_map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  unordered_map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
