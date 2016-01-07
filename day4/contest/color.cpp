#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 200010;
int f[N], r[N];
struct edge{
	int to, pre, c;
}e[N * 2];
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ec e[i].c
#define v e[i].to
int u[N], l = 0;
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
int ndl;
void dfs(int x){
	int t = x;
	reg(i,x){
		ndl++, f[ndl] = t, r[ndl] = 0;
		f[v] = ndl, t = ndl;
	}
	reg(i,x) dfs(v);
}

int mark[N];
int n, m;

int ch[N][3], par[N], Sz[N][3], dep[N];
LL S[N][3], dis[N][19];
int sz[N], sum, s[N], rt;
bool vis[N];
#define max(a,b) ((a) > (b) ? (a) : (b))
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f && !vis[v])
		getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
void dfs(int x, int f, LL d){
	dis[x][++dep[x]] = d;
	reg(i,x) if (v != f && !vis[v]) dfs(v, x, d + ec);
}
void work(int x){
	vis[x] = 1; dfs(x, 0, 0);
	int cnt = 0, tmp = sum - sz[x];
	reg(i,x) if (!vis[v]) {
		rt = 0, sum = sz[v] < sz[x] ? sz[v] : tmp, getrt(v, x);//sum = sz[v] < sz[x] ? sz[v] : tmp!!!
		ch[x][cnt++] = rt, par[rt] = x;
		work(rt);
	}
}
void build(){
	sum = s[rt = 0] = n, getrt(1, 0);
	work(rt);
}

void modi(int x){
	int c = x;
	for(int w = par[x]; w; w = par[w]){
		rep(i,0,2) if (ch[w][i] && ch[w][i] == c) {
			Sz[w][i]++, S[w][i] += dis[x][dep[w]];
			break;
		}
		c = w;
	}	
}

LL qry(int x){
	int c = x; LL ans = 0;
	for(int w = x; w; w = par[w]){
		LL d = dis[x][dep[w]];
		if (mark[w]) ans += d;
		rep(i,0,2) if (ch[w][i] && ch[w][i] != c)
			ans += S[w][i] + 1LL * Sz[w][i] * d;
		c = w;
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,2,n) scanf("%d",&f[i]), f[i]++;
	rep(i,2,n) scanf("%d",&r[i]);
	rep(i,2,n) ins(f[i], i, r[i]);
	ndl = n;
	dfs(1);
	n = ndl;
	rep(i,1,n) u[i] = mark[i] = 0; l = 0;
	rep(i,1,n) if (f[i]) ins(f[i], i, r[i]), ins(i, f[i], r[i]);
	build();
	rep(i,1,m){
		int t, x; scanf("%d%d",&t,&x); x++;
		if (t == 1){
			if (!mark[x]) mark[x] = 1, modi(x);
		}else printf("%lld\r\n", qry(x));
	}
	return 0;
}
