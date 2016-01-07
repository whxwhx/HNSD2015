#include <iostream>
#include <cstdio>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
const int mod = 1000000000 + 7;
void print(LL l){
	dep(i,60,0) cout <<(l >> i & 1);cout <<endl;
}
LL calc(LL l, LL r, int t){
	if (l == r) return 1;
	if ((l ^ r) >> t & 1){
		l &= (1LL << t) - 1, r &= (1LL << t) - 1;
		//print(l);print(r);
		//case1
		if (l == 0) return (1LL << (t + 1));
		int ans = ((1LL << t) - l) % mod;
		//case2
			//case2.1
			LL x = calc(0, r, t - 1);
			//case2.2
			LL y = l;
			//case2 cnt
			if (y <= x) ans += (1LL << t) % mod;
			else ans += (x + (1LL << t) - y) % mod;
			ans %= mod;
		return ans;
	}else {
		l &= (1LL << t) - 1, r &= (1LL << t) - 1;
		return calc(l, r, t - 1);
	}
}
int solve(LL l, LL r, int n){
	if (n == 1) return (r - l + 1) % mod; else return calc(l, r, 60);
}
void work(){
	int n; LL l, r; scanf("%d%lld%lld",&n,&l,&r);
	//print(l);print(r);
	printf("%d\n",(int)(solve(l, r, n) % mod));
}
int main(){
	int T; scanf("%d",&T);
	while (T--) work();
}
