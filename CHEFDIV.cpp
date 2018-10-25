/*
the answer is the sum of divisors of all the numbers - 1 (-1 because of root node has no parent)
greedy technique works in which we take the number with maximum divisors and then move down the tree
Why maximum divisors? 2^2*5^3 is the root and as we need to reduce 1 (exponent value) from either 2 or 5 for the next step
we have two options 2^1*5^3(2*4 divisors) or 2^2*5^2 (3*3 = 9 divisors). So we remove the maximum exponent.
for that we use priority queue.
The part of finding prime exponents can be done with segmented sieve since 1 <= A <= B <= 1e12 
so normal sieve will not fit in memory (note sieve can be used because B - A <= 1e5)
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
		
		priority_queue<int>times;
		ll temp = x;
		ll iterator_ans = 1;
		
		for(auto prime: divisors[x - low]){
			int ct = 0;
			while(temp % prime == 0){
				temp /= prime;
				ct++;
			}
			times.push(ct);
			iterator_ans = iterator_ans * (ct + 1); 
		}
		if(temp != 1){
			times.push(1);
			iterator_ans = iterator_ans * (1 + 1); 
		}

		ans = ans + iterator_ans;
				
		while(!times.empty()){
			
			int mx = times.top();

			times.pop();

			iterator_ans = iterator_ans / (mx + 1);
			iterator_ans = iterator_ans * (mx + 1 - 1);

			ans = ans + iterator_ans;

			if(mx > 1)
				times.push(mx - 1);

		}

		ans--; //remove 1 because of root node value is off by 1
	
	}

	cout << ans << endl;

	return 0;
}
