#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
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
struct TrieNode {
    int start, end;
    TrieNode *next[5];
    TrieNode(int s=-1, int e=-2) {
        memset(next, 0, sizeof(next));
        start=s;
        end=e;
    }
};

string BWT(const string& text) {
    string ans;
    TrieNode *t= new TrieNode();
    for (int i=0; i<text.size(); i++) {
        if (t->next[LetterToNumber(text[i])]==nullptr) {
            t->next[LetterToNumber(text[i])]=new TrieNode(i, (int) text.size()-1);
            continue;
        }
        TrieNode *temp=t->next[LetterToNumber(text[i])];
        int s=temp->start, e=temp->end;
        for (int j=i; j<text.size(); j++) {
            if (text[s]==text[j]) {
                s++;
            } else {
                //cout<<s<<" j "<<j<<endl;
                TrieNode *tempcopy= new TrieNode();
                *tempcopy = *temp;
                temp->next[LetterToNumber(text[s])]=tempcopy;
                temp->end=s-1;
                for (int k=0; k<5; k++) {
                    if (k==LetterToNumber(text[s])) {
                        temp->next[k]->start=s;
                    } else if (k==LetterToNumber(text[j])) {
                        temp->next[k] = new TrieNode(j, (int) text.size()-1);
                    } else {
                        temp->next[k]=nullptr;
                    }
                }
                break;
            }
            if (s>e ) {
                //cout<<s<<" new j "<<j<<endl;
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
        vector<TrieNode*> untamed {t};
        cout<<" i "<<i<<endl;
        while (!untamed.empty()) {
            TrieNode *c = untamed.back();
            untamed.pop_back();
            cout<<c->start<<" "<<c->end<<endl;
            for (int k=0; k<5; k++) {
                if (c->next[k]!=nullptr)
                    untamed.push_back(c->next[k]);
            }
        }*/
    }
    vector<pair<TrieNode*, int>> st;
    st.push_back(make_pair(t, 0));
    TrieNode *cur; int l;
    while (!st.empty()) {
        cur=st.back().first;
        l=st.back().second+ cur->end - cur->start +1;
        //cout<<cur->start<<" "<<cur->end<<endl;
        st.pop_back();
        bool isleaf=true;
        for (int k=0; k<5; k++) {
            if (cur->next[k]!=nullptr) {
                isleaf=false;
                st.push_back(make_pair(cur->next[k], l));
            }
        }
        if (isleaf) {
            //cout<<"isleaf "<<l<<endl;
            if (l==text.size()) {ans+=*(text.rbegin());}
            else {ans+=*(text.rbegin()+l);}
            //cout<<"isleaf "<<l<<" "<<ans.back()<<endl;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
