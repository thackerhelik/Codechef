/*
We can model this problem as 2-SAT problem.
To change a position (i, j) we do (i xor j) which is equivalent to (i or j) and (not i or not j)
To not change a position (i, j) we do not(i xor j) which is
not ((i or j) and (not i or not j))
demorgan not(i or j) or not(not i or not j)
demorgan (not(i) and not(j)) or (i and j)
distribute (not(i) or (i and j)) and (not(j) or (i and j))
(not i or i and not i or j) and (not j or i and not j or j)
(not i or j) and (not j or i)
to do 2-SAT we can find topological order (note that we just need order because there might be cycle in the graph)
then we reverse the graph and find the SCCs
If we find i and not i in same component it is false
else true
*/
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int MAXN = 1025;
int a[MAXN][MAXN], b[MAXN][MAXN], n, change[MAXN][MAXN];
vector<int>adj[4*MAXN];
vector<int>reverse_graph[4*MAXN];
stack<int>stk;
bool used[4*MAXN];
int color[4*MAXN];
int counter;
int component[4*MAXN];

int nott(int x){
    if(x > n)
        return x - n;
    else
        return x + n;
}

void dfs1(int source){
    used[source] = true;
    for(auto it: adj[source]){
        if(!used[it]){
            dfs1(it);
        }    
    }
    stk.push(source);
}

bool check();

void dfs2(int source){
    used[source] = true;
    for(auto it: reverse_graph[source]){
        if(!used[it]){
            dfs2(it);
        }
    }
    component[source] = counter;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

    int t, i, j;
    cin >> t;
    while(t--){

        set<int>SET;

    	cin >> n;
    	   
        memset(used, false, sizeof(used));
        memset(color, 0, sizeof(color));
        

        for(i = 1; i <= n; ++i){
    		for(j = 1; j <= n; ++j){
    			cin >> a[i][j];
    		}
    	}
    	for(i = 1; i <= n; ++i){
    		for(j = 1; j <= n; ++j){
    			cin >> b[i][j];
    		}
    	}


    	for(i = 1; i <= n; ++i){
    		if(a[i][i] != b[i][i])break;
    	}
    	if(i <= n){
    		cout << "No" << endl;
    		continue;
    	}

        bool f = false;

        for(i = 1; i <= n; ++i){
            for(j = i + 1; j <= n; ++j){
                if(a[i][j] == b[i][j] && a[i][j] == b[j][i] && a[j][i] == b[j][i] && a[j][i] == b[i][j]){
                    change[i][j] = 2;
                    change[j][i] = 2;
                    continue;
                }
                if(a[i][j] == b[i][j] && a[j][i] == b[j][i]){
                    change[i][j] = 0;
                    change[j][i] = 0;
                    
                    SET.insert(i);
                    SET.insert(nott(i));
                    SET.insert(j);
                    SET.insert(nott(j));

                    adj[nott(i)].pb(nott(j));
                    adj[nott(j)].pb(nott(i));
                    adj[i].pb(j);
                    adj[j].pb(i);        

                    continue;
                }
                else if(a[i][j] == b[j][i] && a[j][i] == b[i][j]){
                    change[i][j] = 1;
                    change[j][i] = 1;

                    //i xor j
                    SET.insert(i);
                    SET.insert(nott(i));
                    SET.insert(j);
                    SET.insert(nott(j));
                    
                    adj[nott(i)].pb(j);
                    adj[nott(j)].pb(i);
                    adj[i].pb(nott(j));
                    adj[j].pb(nott(i));

                    continue;
                }
                else{f = true; break;}              
            }
            if(f)break;
        }

        if(f){
            for(auto it: SET){
                adj[it].clear();
                reverse_graph[it].clear();
            }
            cout << "No" << endl;
            continue;
        }
        
        for(auto it: SET){
            if(!used[it])
                dfs1(it);
        }


        for(auto it: SET){
            for(auto it2: adj[it]){
                reverse_graph[it2].push_back(it);
            }
        }
        
        bool fft = true;

        memset(used, false, sizeof(used));
        memset(component, 0, sizeof(component));

        while(!stk.empty()){
            int source = stk.top();
            stk.pop();
            if(!used[source]){
                counter++;
                dfs2(source);
            }
        }

        for(auto it: SET){
            if(component[it] == component[nott(it)]){
                fft = false;
                break;
            }
        }

        if(fft)cout << "Yes" << endl;
        else cout << "No" << endl;

        for(auto it: SET){
            adj[it].clear();
            reverse_graph[it].clear();
        }

    }        

    return 0;
}

