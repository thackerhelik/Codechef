/*
First set aside maximum element and all such elements <= k
Now we have to reduce 1 from smallest and largest element till we get all elements <= k
To do this make a frequency array. 2 pointers. First pointer points to smallest and second points to largest.
Now we can reduce the smallest by (value - k) and that (value - k) is used to reduce the largest elements.
There are 2 cases
Let diff = value - k
If diff >= freq[largest] we make freq[largest-1] += freq[largest] and diff -= freq[largest] and freq[largest] = 0
else freq[largest-1] += diff and freq[largest] -= diff and diff = 0
*/
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef long long int ll;

const int MAXN = 50005;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
    int n, t, i, x, k;
    cin >> t;
    while(t--){
        int mx = 0, ans = 0;
        cin >> n >> k;
        int freq[MAXN] = {0};
        for(i = 0; i < n; ++i){
            cin >> x;
            if(x <= k){
                ans = ans + x;
                continue;
            }
            mx = max(x, mx);
            freq[x]++;
        }
        if(mx == 0){
            cout << ans << endl;
            continue;
        }
        freq[mx]--;

        int up = 0, down = mx;

        while(up < MAXN){
            if(freq[up] > 0)break;
            up++;
        }
        while(down >= 0){
            if(freq[down] > 0)break;
            down--;
        }

        while(up <= down){

            while(up < MAXN){
                if(freq[up] > 0)break;
                up++;
            }
            if(up >= MAXN)break;
            while(down >= 0){
                if(freq[down] > 0)break;
                down--;
            }
            if(down < 0)break;

            if(up == down && freq[up] == 1)break;
            int diff = up - k;
            ans = ans + k;
            freq[up]--;
            while(diff > 0 && down > 0){
                
                if(diff >= freq[down]){
                    diff = diff - freq[down];
                    if((down - 1) > k)
                        freq[down - 1] += freq[down];
                    else ans = ans + freq[down]*k;
                    freq[down] = 0;
                    down--;
                    if(down <= up)up--;
                }
                else{
                    freq[down] = freq[down] - diff;
                    if((down - 1) > k)
                        freq[down - 1] += diff;
                    else ans = ans + diff*k;
                    diff = 0;
                    if(down == up)up--;
                }
            }
        }


        bool done = false;
        for(i = k + 1; i < MAXN; ++i){
            if(freq[i] > 0){
                int diff = i - k;
                ans = ans + k + (mx - diff);
                done = true;
                break;
            }
        }


        if(!done)
            ans = ans + mx;
        cout << ans << endl;

    }            

    return 0;
}

