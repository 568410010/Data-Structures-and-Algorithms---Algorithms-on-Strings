#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
    trie t;
    int node=0, matched;
    for (int p=0; p<patterns.size(); p++) {
        string pattern=patterns[p];
        bool found=true;
        matched=0;
        for (int j=0; j<pattern.size(); j++) {
            if (t.size()<=node) {
                edges temp;
                t.push_back(temp);
            }
            if (t[matched].find(pattern[j])==t[matched].end()) {
                found=false;
            } else matched=t[matched][pattern[j]];
            if (!found) {
                t[matched][pattern[j]]=++node;
                cout << matched << "->" << node << ":" << pattern[j] << "\n";
                matched=node;
                
            }
        }
        
    }
    return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      //std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
