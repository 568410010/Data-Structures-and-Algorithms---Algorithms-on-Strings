#include <iostream>
#include <map>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <float.h>
#include <cstdlib>
#include<ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unordered_set>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

char NumberToLetter(int i) {
    switch(i) {
        case 0: return 'A'; break;
        case 1: return 'C'; break;
        case 2: return 'G'; break;
        case 3: return 'T'; break;
        case 4: return '$'; break;
    }
    return '0';
}
int LetterToNumber(char c) {
    switch(c) {
        case 'A': return 0; break;
        case 'C': return 1; break;
        case 'G': return 2; break;
        case 'T': return 3; break;
        case '$': return 4; break;
    }
    return -1;
}

 struct TrieNode1{
     TrieNode1 *next[5];
     int start, end;
     char c;
     TrieNode1(char cc, int s=-1, int e=-1){
         memset(next, 0, sizeof(next));
         start=s;
         end=e;
         c=cc;
     }
 };
vector<string> ComputeSuffixTreeEdges1(const string& text) {
    vector<string> ans;
    TrieNode1 *t=new TrieNode1('0');
    for (int i=0; i<text.size(); i++) {
        TrieNode1 *temp=t;
        for (int j=i; j<text.size(); j++) {
            if (temp->next[LetterToNumber(text[j])]==nullptr)
                temp->next[LetterToNumber(text[j])]=new TrieNode1(text[j]);
            temp=temp->next[LetterToNumber(text[j])];
        }
    }
    vector<TrieNode1 *> stack {t};
    bool connect=false;
    while (!stack.empty()) {
        TrieNode1* cur=stack.back(); stack.pop_back();
        int nxt=0;
        if (!connect) ans.push_back("");
        if (cur->c!='0') ans.back()+=cur->c;
        //cout<<cur->c<<endl;
        char c;
        for (int i=0; i<5; i++) {
            if (cur->next[i]!=nullptr) {
                nxt++;
                //c=NumberToLetter(i);
                stack.push_back(cur->next[i]);
            }
        }
        if (nxt==1) {connect=true;}
        else connect=false;
        //for (auto& d:ans) cout<<d<<" ";
        //cout<<endl;
    }
    sort(ans.begin(), ans.end());
    ans.erase(ans.begin());
    return ans;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
class TrieNode {
public:
    int start, end;
    TrieNode *next[5];
    TrieNode(int s=-1, int e=-1) {
        memset(next, 0, sizeof(next));
        start=s;
        end=e;
    }
};

vector<string> ComputeSuffixTreeEdges(const string& text) {
    vector<string> result;
    TrieNode *t=new TrieNode();
    TrieNode *n;
    for (int i=0; i<text.size() ; i++) {
        //cout<<"i "<<i<<" text "<<text[i]<<endl;
        TrieNode *temp=t;
        if (temp->next[LetterToNumber(text[i])]==nullptr) {
            temp->next[LetterToNumber(text[i])]=new TrieNode(i, (int) text.size()-1);
            continue;
        }
        temp=temp->next[LetterToNumber(text[i])];
        int s=temp->start, e=temp->end;
        for (int j=i; j<text.size(); j++){
            if (text[j]==text[s]) {
                s++;
            } else {
                n=new TrieNode();
                *n=*temp;
                temp->next[LetterToNumber(text[s])]=n;
                temp->end=s-1;
                for (int i=0; i<5; i++) {
                    if (i==LetterToNumber(text[j]))
                        temp->next[i]=new TrieNode(j, (int) text.size()-1);
                    else if (i==LetterToNumber(text[s]))
                        temp->next[i]->start=s;
                    else temp->next[i]=nullptr;
                }
                //cout<<text[j]<<" "<<text[s]<<" j "<<j<<" s "<<s<<" end "<<(int) text.size()-1<<endl;
                break;
            }
            if (s>e) { // && j+1<text.size() !!!这里需要加上
                if (temp->next[LetterToNumber(text[j+1])]==nullptr) {
                    temp->next[LetterToNumber(text[j+1])]=new TrieNode(j+1, (int) text.size()-1);
                    break;
                }
                temp=temp->next[LetterToNumber(text[j+1])];
                s=temp->start;
                e=temp->end;
            }
        }
        /*
        vector<TrieNode*> stack {t};
        TrieNode* cur;
        while (!stack.empty()) {
            cur=stack.back(); stack.pop_back();
            cout<<cur->start<<" end "<<cur->end<<endl;
            for (int i=0; i<5; i++) {
                if (cur->next[i]!=nullptr) {
                    stack.push_back(cur->next[i]);
                }
            }
        } */
        
    }
    vector<TrieNode*> stack {t};
    TrieNode* cur;
    while (!stack.empty()) {
        cur=stack.back(); stack.pop_back();
        if (cur->start>=0)
            result.push_back(text.substr(cur->start, cur->end-cur->start+1));
        for (int i=0; i<5; i++) {
            if (cur->next[i]!=nullptr) {
                stack.push_back(cur->next[i]);
            }
                
        }
    }
    //sort(result.begin(), result.end());
    return result;
}

int main() {
  string text;
    /*
    srand((unsigned) time(NULL));
    size_t n=7;
    for (size_t i = 0; i < n; i++) {
        text+=NumberToLetter(rand()%4);
    }
    text+='$';

     text="AGTGTAG$";
     cout<<text<<endl;
     vector<string> edges1 = ComputeSuffixTreeEdges1(text);
     if (edges!=edges1) cout<<"WRONG!!!"<<endl;
     else cout<<"right"<<endl;
     cout<<edges.size()<<" "<<edges1.size()<<endl;
    */
  cin >> text;
    
  vector<string> edges = ComputeSuffixTreeEdges(text);


    for (int i = 0; i < edges.size(); ++i) {
      cout << edges[i] << endl;
        //cout << edges1[i] << endl;
    }
  return 0;
}
