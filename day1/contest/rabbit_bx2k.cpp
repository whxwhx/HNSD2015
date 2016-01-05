//用bx2k那个贪心+BIT的办法写的
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 2500010;
#define min(a,b) ((a) < (b) ? (a) : (b))
typedef long long LL;
int a[N], b[N];
LL s[N];
inline bool cmp(const int a, const int b){
	return a > b;
}

int m, n;
void add(int x, int d){
	for(;x <= n; x += (-x) & x) s[x] += d;
}

int main(){
	int m0, md, n0, nd; scanf("%d%d%d%d%d%d",&m,&n,&m0,&md,&n0,&nd);
	a[1] = m0;
	rep(i,2,m) a[i] = (a[i - 1] * 58 + md) % (n + 1);
	b[1] = n0;
	rep(i,2,n) b[i] = (b[i - 1] * 58 + nd) % (m + 1);
	/*
	rep(i,1,m) cout <<a[i]<<' ';cout <<endl;
	rep(i,1,n) cout <<b[i]<<' ';cout <<endl;
	*/
	sort(a + 1, a + m + 1, cmp); sort(b + 1, b + n + 1, cmp);
	LL ans = 0;
	rep(i,1,n) add(i, b[i]), add(i + 1, -b[i]);

	int j = 1; while (b[j] == 0) j++;
	rep(i,1,m){
		
	}

	printf("%lld\n",ans);
	return 0;
}
