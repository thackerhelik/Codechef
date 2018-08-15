/*input
4
abcd
abce
abcdex
abcde
3
3 abcy
3 abcde
4 abcde
*/
 
 
#include <bits/stdc++.h>
using namespace std;
 
#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
#define sz(x) (int)(x).size()
 
typedef long long int ll;
 
const int ALPHABET_SIZE = 26;
 
string finalans;
 
struct tri{
	struct tri *children[ALPHABET_SIZE];
	bool isend;
};
 
struct tri* getnode(){	
	struct tri *pnode = new tri;
	pnode->isend = false;
	for(int i = 0; i < ALPHABET_SIZE; ++i){
		pnode->children[i] = NULL;
	}
	return pnode;
}
 
void insert(struct tri* root, string key){
	struct tri* pcrawl = root;
	for(int i = 0; i < sz(key); ++i){
		int index = key[i] - 'a';
		if(!pcrawl->children[index])
			pcrawl->children[index] = getnode();
		pcrawl = pcrawl->children[index];
	}
	pcrawl->isend = true;
}
 
 
void find(struct tri* root, string s){
	struct tri* pcrawl = root;
	int i;
	for(i = 0; i < (int)s.length(); ++i){
		int index = s[i] - 'a';
		if(!pcrawl->children[index])break;
		finalans.push_back(s[i]);
		pcrawl = pcrawl->children[index];
	}
	while(pcrawl != NULL && pcrawl->isend != 1){
		for(int j = 0; j < 26; ++j){
			if(!pcrawl->children[j])
				continue;
			finalans.push_back(char(j + 'a'));
			pcrawl = pcrawl->children[j];
			break;
		}
	}
	
}
 
struct helik{
	int k, idx;
	string s;
};
 
bool cmp(struct helik &lhs, struct helik &rhs){
	if(lhs.k == rhs.k)return lhs.idx < rhs.idx;
	else return lhs.k < rhs.k;
}
 
int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif
 
	int n, q, k;
	cin >> n;
	string s[n];
	struct tri* root = getnode();
 
	for(int i = 0; i < n; ++i){
		cin >> s[i];
	}            
 
	int ctr = 0;
 
	cin >> q;
 
	vector<struct helik>m;
 
	map<int, string>m2;
 
	string x;
 
	for(int i = 0; i < q; ++i){
		cin >> k >> x;
		struct helik item;
		item.k = k - 1;
		item.s = x;
		item.idx = i;
		m.push_back(item);
	}
 
	sort(m.begin(), m.end(), cmp);
 
	for(auto it: m){
		int kiki = it.k;
		string str = it.s;
		int idx = it.idx;
		while(ctr <= kiki){
			insert(root, s[ctr]);
			ctr++;
		}
		finalans = "";
		find(root, str);
		m2[idx] =  finalans;
	}
 
	for(auto it: m2){
		cout << it.second << endl;
	}
 
    //#if !ONLINE_JUDGE
    //    cout << fixed << setprecision(12) << "-------------------------------------------------\n";
    //    cout << double(clock())/CLOCKS_PER_SEC << " seconds" << endl;
    //#endif
    return 0;
}
