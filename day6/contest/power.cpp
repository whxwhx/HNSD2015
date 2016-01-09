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
LL gcd(LL a, LL b){
	return b ? gcd(b, a % b) : a;
}
LL lcm(LL a, LL b){
	return a / gcd(a, b) * b;
}


int vis[35], key[35], kl = 0;
int a, b; 
LL L, R;

void dfs(int x, int f, LL lm, LL &F){
	if (x > kl) F -= (R / lm - L / lm) * f;
	else {
		if (lm > R) return;
		dfs(x + 1, f, lm, F);
		dfs(x + 1, -f, lcm(lm, key[x]), F);
	}
}

LL f[35];
void init(){
	scanf("%d%d",&a,&b);
	rep(k,1,29){
		rep(i,1,k){
			rep(j,i,k) vis[j] = 0;
			rep(j,i,k) if (!vis[j]){
				int ed = k / j;
				rep(t,2,ed) vis[t * j] = 1;
			}
			kl = 0;
			rep(j,i,k) if (!vis[j]) key[++kl] = j;
			L = 1LL * b * (i - 1), R = 1LL * b * i;
			dfs(1, 1, 1, f[k]);
			f[k] += R - L;
		}
	}
}

const int N = 100100;
bool pr[N];
void calc(){
	LL ans = 0;
	int m = (int)sqrt(a) + 1;
	int cnt = a - m;
	rep(i,2,m) if (!pr[i]){
		int k = i, tmp = 1;
		while (k <= a / i){
			k = k * i;
			if (k <= m) pr[k] = 1; else cnt--;
			tmp++;
		}
		ans = ans + f[tmp];
	}
	ans += 1LL * cnt * b;
	printf("%lld\r\n",ans + 1);
}

int main(){
	init();
	calc();
	return 0;
}
