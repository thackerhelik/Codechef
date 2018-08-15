    /*input
    This is a nice question regarding dsu + bfs to make components
    components are reseted cleverly
    it takes O(n*m*log(n*m)) time
    randomized dsu union is used here
    */
    #include <bits/stdc++.h>
    #define fo(i, n) for(i = 0; i < n; ++i)
    using namespace std;
     
    const int MAXN = 2005;
     
    int n, m;
    int a[MAXN][MAXN];
    int sz[MAXN * MAXN], par[MAXN * MAXN];
    int sizes[MAXN * MAXN];
    int visited[MAXN][MAXN];
     
    int find(int x){
    	return (x == par[x]) ? x : par[x] = find(par[x]);
    }
     
    bool isvalid(int x, int y, int k){
    	return (x >= 0 && x < n && y >= 0 && y < m && a[x][y] == k && !visited[x][y]);
    }
     
    bool isvalid2(int x, int y){
    	return (x >= 0 && x < n && y >= 0 && y < m);
    }
     
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
     
    int main(){
     
    	cin >> n >> m;
     
    	int i, j, k;
     
    	fo(i, n)fo(j, m)cin >> a[i][j];
     
    	int ctr = 0;
     
    	fo(i, n){
    		fo(j, m){
    			if(!visited[i][j]){
    				//do bfs now
    				int component_size = 0;
    				queue<pair<int, int>>q;
    				q.push({i, j});
    				component_size++;
    				visited[i][j] = ++ctr;
    				while(!q.empty()){	
    					int x = q.front().first, y = q.front().second;
    					q.pop();
    					for(k = 0; k < 4; ++k){
    						int xx = x + dx[k], yy = y + dy[k];
    						if(isvalid(xx, yy, a[i][j])){
    							q.push({xx, yy});
    							visited[xx][yy] = ctr;
    							component_size++;
    						}
    					}
    				}
    				sizes[ctr] = component_size;
    			}
    		}
    	}
     
    	map< pair<int,int>, vector<pair<int,int> > > mp;
     
    	//handle only a single value path
    	int ans = 0;
    	for(i = 1; i <= ctr; ++i){
    		par[i] = i;
    		sz[i] = sizes[i];
    		ans = max(ans, sz[i]);
    	}
     
    	for(i = 0; i < n; ++i){
    		for(j = 0; j < m; ++j){
    			for(k = 0; k < 4; ++k){
    				int x = i + dx[k], y = j + dy[k];
    				if(isvalid2(x, y)){
    					if(a[i][j] < a[x][y]){
    						mp[{a[i][j], a[x][y]}].push_back({visited[i][j], visited[x][y]});
    					}
    				}
    			}
    		}
    	}
     
    	for(auto it: mp){
    		// it.second is a vector containing components
    		// it.first is a pair of colors example 1 and 3
    		// so we are considering that pair right now
    		vector<int>changed; //to reset the size of the component after the iteration
    		for(auto it2: it.second){
    			int x = it2.first;
    			int y = it2.second;
    			x = find(x);
    			y = find(y);
    			if(x == y)continue;
    			changed.push_back(x);
    			changed.push_back(y);
    			if(rand() % 2){
    				par[x] = y;
    				sz[y] += sz[x];
    				ans = max(ans, sz[y]);
    			}
    			else{
    				par[y] = x;
    				sz[x] += sz[y];
    				ans = max(ans, sz[x]);
    			}
    		}
    		for(auto it2: changed){
    			sz[it2] = sizes[it2];
    			par[it2] = it2;
    		}
    	}
     
    	cout << ans << endl;
     
    	return 0;
    } 
