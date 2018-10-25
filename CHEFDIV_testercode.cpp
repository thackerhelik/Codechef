/*input
932451 935212
11 12
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long int

const int MAXN = 1000005;
vector<int>divisors[MAXN];
bool isprime[MAXN];

ll ceildivide(ll a, ll b){
	return (a + b - 1) / b;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	ll i, j, x, low, high;

	cin >> low >> high;

	for(i = 2; i < MAXN; ++i)
		isprime[i] = true;

	//segmented sieve
	for(i = 2; i < MAXN; ++i){
		if(isprime[i]){
			for(j = i*i; j < MAXN; j+=i){
				isprime[j] = false;
			}
			for(x = ceildivide(low, i)*i; x <= high; x += i){
				divisors[x - low].push_back(i);
			}
		}
	}

	ll ans = 0;

	for(x = low; x <= high; ++x){
		vector<int>times;
		ll temp = x;
		for(auto prime: divisors[x - low]){
			int ct = 0;
			while(temp % prime == 0){
				temp /= prime;
				ct++;
			}
			times.push_back(ct);
		}
		if(temp != 1){
			times.push_back(1);
		}
		sort(times.begin(), times.end());
		while(!times.empty()){
			ll here = 1;
			for(auto a: times){
				here = here * (a + 1);
			}
			ans = ans + here;
			times.back()--;
			if(times.back() == 0)times.pop_back();
			sort(times.begin(), times.end());
		}
	}

	cout << ans << endl;

	return 0;
}
