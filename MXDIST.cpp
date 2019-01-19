/*
To find the maximum distance between points on a 2D plane, we can build a convex hull and find the diameter of the hull.
This can be done by monotone chain algorithm and the rotating calipers technique. To query faster, each node of segment tree
contains a convex hull. To merge the 2 convex hulls, we note that they are already sorted so we just merge the up and down vectors
of the 2 convex hulls and build a new hull. To query find the convex hull covering the entire segment and find diameter by
rotating calipers technique.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
int nn;

struct point{
	int x, y;

	point(int xx = 0, int yy = 0): x(xx), y(yy){

	}

	point operator - (const point &b) const{
		return point(x - b.x, y - b.y);
	}

	long long operator * (const point &b) const{
		return (long long)x*b.y - (long long)y*b.x;
	}

	bool operator < (const point &b) const{
		return x < b.x || (x == b.x && y < b.y);
	}

}x[N];


long long dist(point u, point v){
	return (long long)(u.x - v.x)*(u.x - v.x) + (long long)(u.y - v.y)*(u.y - v.y);
}

long long cross(point u, point v, point o){
	return (u - o) * (v - o);
}

struct convex_hull{
	//Monotone chain algorithm
	vector<point>up;
	vector<point>down;

	convex_hull(){}

	convex_hull(vector<point>all){
		up = all;
		down = all;
		build();
	}	

	void reserve(int i){up.reserve(i); down.reserve(i);}
	void clear(){up.clear(); down.clear();}

	convex_hull operator + (const convex_hull &b) const{
		convex_hull c;
		c.up.resize(up.size() + b.up.size());
		merge(up.begin(), up.end(), b.up.begin(), b.up.end(), c.up.begin());
		c.down.resize(down.size() + b.down.size());
		merge(down.begin(), down.end(), b.down.begin(), b.down.end(), c.down.begin());
		c.build();
		return c;
	}

	void build(){
		{	
			int n = (int)up.size();
			int m = 0;
			for(int i = 0; i < n; ++i){
				while(m >= 2 && cross(up[i], up[m - 1], up[m - 2]) <= 0)m--;
				up[m++] = up[i];
			}
			up.resize(m);
		}
		{
			int n = (int)down.size();
			int m = 0;
			for(int i = 0; i < n; ++i){
				while(m >= 2 && cross(down[i], down[m - 1], down[m - 2]) >= 0)m--;
				down[m++] = down[i];
			}
			down.resize(m);
		}
	}

	long long solve(){
		vector<point>hull = up;
		for(int i = int(down.size()) - 2; i >= 0; --i){
			hull.push_back(down[i]);
		}
		reverse(hull.begin(), hull.end());
		int n = int(hull.size()) - 1;
		long long ans = 0;
		for(int  i = 0, j = 1; i < n; ++i){
			while(dist(hull[i], hull[j+1]) > dist(hull[i], hull[j])){
				j = (j + 1) % n;
			}
			ans = max(ans, dist(hull[i], hull[j]));
		}
		return ans;
	}

};

convex_hull st[4*N];
convex_hull ret;

void build(int node, int be, int en){
	if(be == en){
		vector<point>temp;
		temp.push_back(x[be]);
		st[node] = convex_hull(temp);
		return;
	}
	int mid = (be + en) >> 1;
	build(2*node, be, mid);
	build(2*node + 1, mid + 1, en);
	st[node] = st[2*node] + st[2*node + 1];
}

void query(int node, int be, int en, int l, int r){
	if(be > r || en < l)return;
	if(l <= be && en <= r){
		ret = ret + st[node];
		return;
	}
	int mid = (be + en) >> 1;
	query(2*node, be, mid, l, r);
	query(2*node + 1, mid + 1, en, l, r);
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> nn;
	for(int i = 1; i <= nn; ++i){
		cin >> x[i].x >> x[i].y;
	}
	build(1, 1, nn);
	int q;
	cin >> q;
	while(q--){
		int l, r;
		cin >> l >> r;
		ret.clear();
		query(1, 1, nn, l, r);
		cout << ret.solve() << endl;
	}
}
