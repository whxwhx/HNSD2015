#include <iostream>
#include <cstdio>
#include <bitset>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 8002, M = 40;
bitset<N> g, h, f;
void read(bitset<N> &a, int &l){
	scanf("%d",&l);
	rep(i,0,l){
		int t; scanf("%d",&t);
		a[i] = t;
	}
}
bitset<N> tmp, ans, w, pw[M + 1];
int fl, gl, hl;
void mod(bitset<N> &a){
	dep(i,hl + hl, hl) if (a[i]) a = a ^ (h << (i - hl));
}
void mult(bitset<N> &a){
	w = 0;
	rep(i,0,hl) if (g[i]) w ^= a << i;
	mod(w);
	rep(i,0,hl) a[i] = w[i];
}

void mult2(bitset<N> &a, bitset<N> &b){
	w = 0;
	rep(i,0,hl) if (b[i]) w ^= a << i;
	mod(w);
	rep(i,0,hl) a[i] = w[i];
}

int main(){
	tmp = 0, f = 0, g = 0, h = 0;
	read(f, fl), read(g, gl), read(h, hl);
	mod(g);
	pw[0] = tmp = 1;
	rep(i,1,M) mult(tmp), pw[i] = tmp;
	ans = 0;

	for(int i = fl; i >= 0; i -= M){
		int ed = min(M - 1, i);
		if (i != fl) mult2(ans, pw[ed + 1]);
		rep(j,0,ed) if (f[i - j]) ans ^= pw[ed - j];
	}

	int t = 0;
	dep(i,hl,0) if (ans[i]) {t = i; break;}
	printf("%d ",t);
	rep(i,0,t) {
		if (ans[i]) printf("%d", 1); else printf("%d",0);
		if (i != t) printf(" ");
	}
	printf("\n");
	return 0;
}
