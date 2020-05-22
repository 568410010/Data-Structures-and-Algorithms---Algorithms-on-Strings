#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <cstring>
using namespace std;

int const Letters =    4;
//int const NA      =   -1;

struct TrieNode
{
	TrieNode* next[Letters];
    bool is_leaf;
	TrieNode (bool b=false)
	{
		memset(next, 0, sizeof(next));
        is_leaf=b;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
    vector <int> result;
    TrieNode *t=new TrieNode();
    for (int p=0; p<patterns.size(); p++) {
        TrieNode *temp=t;
        for (int i=0; i<patterns[p].size(); i++) {
            int letter=letterToIndex(patterns[p][i]);
            if (temp->next[letter]==nullptr) temp->next[letter]=new TrieNode();
            temp=temp->next[letter];
        }
        temp->is_leaf=true;
    }
    for (int i=0; i<text.size(); i++) {
        TrieNode *temp=t;
        int l=0;
        while (i+l<text.size() && temp->next[letterToIndex(text[i+l])]!=nullptr) {
            temp=temp->next[letterToIndex(text[i+l])];
            if (temp->is_leaf) result.push_back(i);
            l++;
        }
    }
	return result;}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
