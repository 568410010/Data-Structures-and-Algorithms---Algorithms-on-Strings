#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
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
using namespace std;
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
struct TrieNode {
    int start, end;
    TrieNode *next[4];
    TrieNode(int s=-1, int e=-1) {
        memset(next, 0, sizeof(next));
        start=s;
        end=e;
    }
};

string solve (string p, string q) {
    string ans;
    TrieNode *t= new TrieNode(), *n, *temp;
    int s, e;
    for (int i=0; i<q.size(); i++) {
        temp=t;
        if (temp->next[LetterToNumber(q[i])] == nullptr) {
            temp->next[LetterToNumber(q[i])] = new TrieNode(i, (int) q.size()-1);
            continue;
        }
        temp=temp->next[LetterToNumber(q[i])];
        s=temp->start; e=temp->end;
        for (int j=i; j<q.size(); j++) {
            if (q[j]==q[s]) {
                s++;
            } else {
                n=new TrieNode();
                *n = *temp;
                temp->end=s-1;
                for (int k=0; k<4; k++) {
                    if (q[j] == NumberToLetter(k))
                        temp->next[k] = new TrieNode(j, (int) q.size()-1) ;
                    else if (q[s] == NumberToLetter(k)) {
                        temp->next[k] = n;
                        temp->next[k]->start = s ;
                    }
                    else temp->next[k] = nullptr;
                }
                break;
            }
            if (s>e && j+1<q.size()) {
                if (temp->next[LetterToNumber(q[j+1])] == nullptr) {
                    temp->next[LetterToNumber(q[j+1])] = new TrieNode(j+1, (int) q.size()-1);
                    break;
                }
                temp=temp->next[LetterToNumber(q[j+1])];
                s=temp->start;
                e=temp->end;
            }
        }
    }
    
    //vector<pair<int, int>> poss;
    //pair<int, int> cur;
    int left=1, right= (int) p.size(), mid;
    string possans;
    while (left<=right) {
        mid=(left+right)/2;
        unordered_set<string> poss;
        for (int i=0; i+mid<=p.size() && i+mid<=q.size(); i++) {
            poss.insert(p.substr(i, mid));
        }
        possans="";
        for (const string& cur : poss) {
            temp=t;
            if (temp->next[LetterToNumber(cur[0])] == nullptr) {
                possans=cur;
                break;
            }
            temp = temp->next[LetterToNumber(cur[0])];
            s=temp->start; e=temp->end;
            for (int j=0; j<cur.size(); j++) {
                if (cur[j]==q[s]) {
                    s++;
                } else {
                    possans=cur;
                    break;
                }
                if (s>e && j+1<cur.size()) {
                    if (temp->next[LetterToNumber(cur[j+1])] == nullptr) {
                        possans=cur;
                        break;
                    }
                    temp = temp->next[LetterToNumber(cur[j+1])];
                    s=temp->start; e=temp->end;
                }
            }
            if (!possans.empty()) break;
        }
        if (possans.empty()) {
            left=mid+1;
        } else {
            right=mid-1;
            ans=possans;
        }
    }
    return ans;
}

int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);

	cout << ans << endl;

	return 0;
}
