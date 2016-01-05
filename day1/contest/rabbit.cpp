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
LL sa[N], sb[N];
int main(){
	int m, n, m0, md, n0, nd; scanf("%d%d%d%d%d%d",&m,&n,&m0,&md,&n0,&nd);
	a[1] = m0;
	rep(i,2,m) a[i] = (a[i - 1] * 58 + md) % (n + 1);
	b[1] = n0;
	rep(i,2,n) b[i] = (b[i - 1] * 58 + nd) % (m + 1);

	/*
	rep(i,1,m) cout <<a[i]<<' ';cout <<endl;
	rep(i,1,n) cout <<b[i]<<' ';cout <<endl;
	*/

	rep(i,1,m) a[i] -= n;
	rep(i,1,n) b[i] -= m;

	sort(a + 1, a + m + 1); sort(b + 1, b + n + 1);
	sa[0] = sb[0] = 0;
	rep(i,1,m) sa[i] = sa[i - 1] + a[i];
	rep(i,1,n) sb[i] = sb[i - 1] + b[i];

	int j = n;
	LL ans = 1LL * N * N;
	rep(i,1,m){
		while (j && b[j] + i > 0) j--;
		ans = min(ans, sa[i] + sb[j] + 1LL * n * m + 1LL * i * j);
		//cout <<i<<' '<<j<<' '<<ans<<endl;
	}
	
	printf("%lld\n",ans);
	return 0;
}
