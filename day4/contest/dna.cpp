#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100100;
char s[N];
int l, a[N];

int get(char c){
	if (c == 'A') return 0;
	else if (c == 'C') return 1;
	else if (c == 'T') return 2;
	else return 3;
}

struct node{
	node *ch[4], *f, *fa, *hf;
	int l;
}T[N], *r0, *rm1, *p;
int Tl = 0;
node *nn(){
	++Tl;
	rep(i,0,3) T[Tl].ch[i] = NULL;
	T[Tl].f = T[Tl].fa = T[Tl].hf = NULL;
	return &T[Tl];
}

node *getfail(node *w, int x, int l){
	for(;a[l - w->l - 1] != x; w = w->f);
	return w;
}
void add(int x, int l){
	node *w = p;
	w = getfail(w, x, l);
	if (w->ch[x]) p = w->ch[x];
	else {
		p = nn(), p->l = w->l + 2, p->fa = w;
		node *q = w->f;
		if (!q) p->f = p->hf = r0;
		else {
			p->f = getfail(q, x, l)->ch[x];
			q = getfail(w->hf, x, l)->ch[x];//pay attention to w == r0
			for(;(q->l << 1) > p->l; q = q->f);
			p->hf = q;
		}
		w->ch[x] = p;
	}
}

void build(){
	Tl = 0;
	rm1 = nn(), r0 = nn();
	rm1->l = -1, r0->l = 0;
	r0->f = r0->hf = rm1;
	a[0] = -1;
	p = rm1;
	rep(i,1,l) add(a[i], i);
}

int f[N], ans;
#define min(a,b) ((a) < (b) ? (a) : (b))
void dp(){
	ans = l;
	rep(i,1,Tl) f[i] = T[i].l;
	f[r0 - T] = 1; f[rm1 - T] = 0;
	rep(i,3,Tl) if (T[i].l & 1){
		int w = T[i].fa - T, q = T[i].f - T;
		f[i] = min(f[i], f[w] + 2);
		f[i] = min(f[i], f[q] + (T[i].l - T[q].l));
		ans = min(ans, f[i] + l - T[i].l);
		//cout <<T[i].l<<' '<<f[i]<<endl;
	}else {
		int w = T[i].fa - T, q = T[i].hf - T;
		f[i] = min(f[i], f[w] + 1);
		f[i] = min(f[i], f[q] + (T[i].l / 2 - T[q].l) + 1);
		ans = min(ans, f[i] + l - T[i].l);
		//cout <<T[i].l<<' '<<f[i]<<endl;
	}
}

void work(){
	scanf("%s",s + 1); l = strlen(s + 1);
	rep(i,1,l) a[i] = get(s[i]);
	build();
	dp();
	printf("%d\r\n",ans);
}
int main(){
	int T; scanf("%d",&T);
	while (T--) work();
}
