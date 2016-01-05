//用bx2k那个贪心+BIT的办法写的
//递增排序后，一段相等的元素的一个后缀-1可以转为它的一个前缀-1，这样就能不用平衡树仍然维护一个有序的数列了
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
int a[N], b[N], s[N];
inline bool cmp(const int a, const int b){
	return a > b;
}

int m, n;
void add(int x, int d){
	for(;x <= n; x += (-x) & x) s[x] += d;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}

/*
a[i]表示一个i..n的+1标记
所以sum(i)表示i这个点的值
sum(i)是单调递增的
*/

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
	sort(a + 1, a + m + 1, cmp); sort(b + 1, b + n + 1);
	LL ans = 0;
	rep(i,1,n) add(i, b[i]), add(i + 1, -b[i]);

	rep(i,1,m){
		//find the first element that is *positive* >.<
		int k = 0; 
		LL S = 0;
		dep(i,21,0){
			k |= 1 << i;
			if (k <= n && S + s[k] <= 0) S += s[k]; else k ^= 1 << i;
		}
		k++;
		if (k > n) break;

		if (k < n - a[i] + 1) {
			ans += a[i];
			k = n - a[i] + 1; 
			int t = sum(k);
			//find the first element that equals to sum(k)
			S = 0; int x = 0;
			dep(i,21,0){
				x |= 1 << i;
				if (x <= n && S + s[x] < t) S += s[x]; else x ^= 1 << i;
			}
			int l = x + 1;
			//find the last element that equals to sum(k)
			S = 0, x = 0;
			dep(i,21,0){
				x |= 1 << i;
				if (x <= n && S + s[x] <= t) S += s[x]; else x ^= 1 << i;
			}
			int r = x;
			//add 
			add(l, -1);
			add(l + r - k + 1, 1);
			add(r + 1, -1);
		}else add(k, -1), ans += n - k + 1;
	}

	printf("%lld\n",ans);
	return 0;
}
