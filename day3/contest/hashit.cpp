#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <multiset>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
typedef long long LL;
LL ans = 0;

const int N = 201010;
struct node{
	node *ch[26], *trans[26], *par;
	int l;
}T[N], *S = &T[0], *rt[N];
int TL = 0;
node *nn(){
	return &T[++TL];
}
node *add(node *w, int c){
	if (w->trans[c] && w->trans[c]->l == w->l + 1) return w->trans[c];
	node *p = nn(); p->l = w->l + 1;
	for(;w && !w->trans[c]; w = w->par) w->trans[c] = p;
	if (!w) p->par = S;
	else{
		node *q = w->trans[c];
		if (q->l == w->l + 1) p->par = q;
		else {
			node *r = nn(); *r = *q; r->l = w->l + 1;
			p->par = q->par = r;
			for(;w && w->trans[c] == q; w = w->par) w->trans[c] = r;
		}
	}
	return p;
}

struct trie{
	trie *ch[26];
}Tr[N], *cur[N], *st[N];
int Trl = 0;
#define oc o->ch[c - 'a']
trie *add(trie *o, char c){
	if (!oc) oc = &Tr[++Trl]; return oc;	
}

trie *q[N];
void build(){
	int l = 0, r = 1; q[0] = &Tr[0];
	rt[0] = S;
	while (l < r){
		trie *x = q[l++]; int t = x - Tr;
		rep(i,0,25) if (x->ch[i]) rt[(x->ch[i]) - Tr] = add(rt[t], i), q[r++] = x->ch[i];
	}
}

struct edge{
	int to, pre;
}e[N];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int pre[N], dfs_clock = 0, sz[N], son[N], suc[N];
void dfs1(int x){
	sz[x] = 1, son[x] = 0;//!!! (son[x] == 0) ===> son[x] = v;
	reg(i,x) {
		dfs1(v), sz[x] += sz[v];
		if (son[x] == 0 || sz[v] >= sz[son[x]]) son[x] = v;
	}
}
void dfs2(int x){
	pre[x] = ++dfs_clock;
	if (son[x]) dfs2(son[x]);
	reg(i,x) if (v != son[x]) dfs2(v);
	suc[x] = dfs_clock;
}

int g[N][19];
void init_g(){
	rep(i,1,TL) g[i][0] = T[i].par - T;
	rep(j,1,17) rep(i,1,TL) g[i][j] = g[g[i][j - 1]][j - 1];
}

//BIT
int s[N];
void add(int x, int d){
	for(;x <= dfs_clock; x += (-x) & x) s[x] += d;
}
int sum(int x){
	int ans = 0;
	//int t = x;
	for(;x; x -= (-x) & x) ans += s[x];
	return ans;
}

void add(int x){
	int t = x;
	dep(i,17,0) if (g[x][i] && sum(suc[g[x][i]]) == sum(pre[g[x][i]] - 1)) x = g[x][i];
	if (sum(suc[x]) == sum(pre[x] - 1)) x = g[x][0];
	ans += T[t].l - T[x].l;
	add(pre[t], 1);
}
void del(int x){
	add(pre[x], -1);
}

char Q[N];
LL tmp[N];

int main(){
	scanf("%s",Q + 1);	int n = strlen(Q + 1);
	int l = 0;
	st[0] = cur[0] = &Tr[0];
	rep(i,1,n){
		char c = Q[i];
		if (c == '-') cur[i] = st[l], l--; else{
			l++;
			st[l] = add(st[l - 1], c);
			cur[i] = st[l];
		}
	}
	build();
	rep(i,1,TL) ins(T[i].par - T, i);
	dfs1(0);
	dfs2(0);
	init_g();
	l = 0; tmp[l] = 0;
	rep(i,1,n){
		char c = Q[i];
		if (c == '-') {
			del(rt[cur[i] - Tr] - T);
			ans = tmp[--l];
		}else add(rt[cur[i] - Tr] - T), tmp[++l] = ans;
		printf("%I64d\n",ans);
	}
	return 0;
}
