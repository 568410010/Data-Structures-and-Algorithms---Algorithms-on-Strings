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

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;
// Data structure to store edges of a suffix tree.
struct Edge {
  // The ending node of this edge.
  int node;
  // Starting position of the substring of the text 
  // corresponding to the label of this edge.
  int start;
  // Position right after the end of the substring of the text 
  // corresponding to the label of this edge.
  int end;

  Edge(int node_, int start_, int end_) : node(node_), start(start_), end(end_) {}
  Edge(const Edge& e) : node(e.node), start(e.start), end(e.end) {}
};

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).
map<int, vector<Edge> > SuffixTreeFromSuffixArray(
    const vector<int>& suffix_array,
    const vector<int>& lcp_array,
    const string& text) {
  map<int, vector<Edge> > tree;
  // Implement this function yourself
  return tree;
}
char NumberToLetter(int i) {
    switch(i) {
        case 0: return '$'; break;
        case 1: return 'A'; break;
        case 2: return 'C'; break;
        case 3: return 'G'; break;
        case 4: return 'T'; break;
    }
    return '0';
}
int LetterToNumber(char c) {
    switch(c) {
        case '$': return 0; break;
        case 'A': return 1; break;
        case 'C': return 2; break;
        case 'G': return 3; break;
        case 'T': return 4; break;
    }
    return -1;
}
struct Node {
    int start, end, L;
    Node *prev;
    Node *next[5];
    Node (int start_=-1, int end_=-1, int L_=0, Node *prev_=nullptr) : start(start_), end(end_), L(L_), prev(prev_) {
        memset(next, 0, sizeof(next));
    }
};
void visual(Node* root) {
    if (root==NULL) return;
    if (root->start>=0) cout<<root->start<<" "<<root->end+1<<endl;
    for (int k=0; k<5; k++)
        visual(root->next[k]);
}

Node* SuffixTreeFromSuffixArray1(const vector<int>& SA, const vector<int>& LCP, const string& text) {
    int S= (int) text.size(), L;
    for (auto& c:text) cout<<c;
    cout<<endl;
    Node *t = new Node(), *temp;
    temp = t;
    temp->next[0] = new Node(SA[0], S-1, 1, temp); // SA[0] '$'
    L=1;
    temp=temp->next[0];
    for (int i=1; i<text.size(); i++) {
        while (temp->prev!=nullptr && temp->prev->L >= LCP[i-1]) {
            temp = temp->prev;
            L = temp->L;
        }
        if (L==LCP[i-1]) {
            temp->next[LetterToNumber(text[SA[i]+L])] = new Node(SA[i]+L, S-1, S-SA[i], temp);
            temp = temp->next[LetterToNumber(text[SA[i]+L])];
            L=temp->L;
        } else {
            Node *tempcopy = new Node();
            *tempcopy = *temp;
            temp->end -= L-LCP[i-1];
            temp->L -= L-LCP[i-1];
            tempcopy->start = temp->end+1;
            for (int k=0; k<5; k++) {
                if (k== LetterToNumber(text[tempcopy->start])){
                    temp->next[k] = tempcopy;
                } else if (k== LetterToNumber(text[SA[i]+temp->L])) {
                    temp->next[k] = new Node(SA[i] + temp->L, S-1, S-SA[i], temp);
                } else temp->next[k] = nullptr;
            }
            temp = temp->next[LetterToNumber(text[SA[i]+temp->L])];
            L=temp->L;
        }
    }
    visual(t);
    return t;
}



int main() {
  char buffer[200001];
  scanf("%s", buffer);
  string text = buffer;
  vector<int> suffix_array(text.length());
  for (int i = 0; i < text.length(); ++i) {
    scanf("%d", &suffix_array[i]);
  }
  vector<int> lcp_array(text.length() - 1);
  for (int i = 0; i + 1 < text.length(); ++i) {
    scanf("%d", &lcp_array[i]);
  }
  // Build the suffix tree and get a mapping from 
  // suffix tree node ID to the list of outgoing Edges.
    Node* t=SuffixTreeFromSuffixArray1(suffix_array, lcp_array, text);
  map<int, vector<Edge> > tree = SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
  //printf("%s\n", buffer);
  // Output the edges of the suffix tree in the required order.
  // Note that we use here the contract that the root of the tree
  // will have node ID = 0 and that each vector of outgoing edges
  // will be sorted by the first character of the corresponding edge label.
  //
  // The following code avoids recursion to avoid stack overflow issues.
  // It uses a stack to convert recursive function to a while loop.
  // The stack stores pairs (node, edge_index). 
  // This code is an equivalent of 
  //
  //    OutputEdges(tree, 0);
  //
  // for the following _recursive_ function OutputEdges:
  //
  // void OutputEdges(map<int, vector<Edge> > tree, int node_id) {
  //   const vector<Edge>& edges = tree[node_id];
  //   for (int edge_index = 0; edge_index < edges.size(); ++edge_index) {
  //     printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
  //     OutputEdges(tree, edges[edge_index].node);
  //   }
  // }
  //
    
    
   /*
  vector<pair<int, int> > stack(1, make_pair(0, 0));    
  while (!stack.empty()) {
    pair<int, int> p = stack.back();
    stack.pop_back();
    int node = p.first;
    int edge_index = p.second;
    if (!tree.count(node)) {
      continue;
    }
    const vector<Edge>& edges = tree[node];
    if (edge_index + 1 < edges.size()) {
      stack.push_back(make_pair(node, edge_index + 1));
    }
    printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
    stack.push_back(make_pair(edges[edge_index].node, 0));
  }
    */
  return 0;
}
