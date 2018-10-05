/*
Initially the largest value is the sum of entire array
now we have to options 2...n or 1...n-1
Put both in priority queue and select largest once in each iteration
Similar to BFS in a way
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long int

ll arr[100005];

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	ll n, k;
	cin >> n >> k;

	ll s = 0;
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
		s = s + arr[i];
	}

	priority_queue<pair<ll,pair<ll,ll>>>q;
	map< pair<int,int>, bool >m;

	q.push({s, {0, n - 1}});

	while(k--){
		cout << q.top().first << " ";
		ll ss = q.top().first;
		ll st = q.top().second.first;
		ll en = q.top().second.second;
		q.pop();
		if(st + 1 < n && st + 1 <= en && !m.count({st + 1, en})){
			q.push({ss - arr[st], {st + 1, en}});
			m.insert({{st + 1, en},true});
		}
		if(en - 1 >= 0 && st <= en - 1 && !m.count({st, en - 1})){
			q.push({ss - arr[en], {st, en - 1}});
			m.insert({{st, en - 1}, true});
		}
	}
	cout << endl;

}
