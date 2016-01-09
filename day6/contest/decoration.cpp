#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int mod = 1000000007;
const int N = 2000010;
//启示这种统计的题目，不一定要考虑红色划分出i段奇、j段偶的方案数，
//可以先枚举出划分成多少段，然后直接考虑往里面插数
//不是把红色固定在格子上。。而是往红色里插
int ans = 0;
int M, R, G, B, pw[N], fac[N], inv[N];
int C(int n, int m){
	if (n < m) return 0;
	return 1LL * fac[n] * inv[n - m] % mod * inv[m] % mod;
} 

int pow(int a, int b){
	int w = 1;
	for(;b; b >>= 1, a = 1LL * a * a % mod) if (b & 1) w = 1LL * w * a % mod;
	return w;
}

void calc(){
	if (R == 0) return;
	//R - 1
	int cnt = R - 1, rest = M - R;
	if (cnt) {
		rep(i,0,cnt){
			int j = cnt - i;
			if ((rest & 1) == (j & 1) && G >= i && B >= i){
				int g = G - i, b = B - i;
				if ((g - b + j) & 1) continue;
				int x = (g - b + j) >> 1, y = j - x;//x->g y->b
				if (x < 0 || y < 0) continue;//!!!!
				g -= x, b -= y;
				if (g != b || g < 0) continue;
				ans += 1LL * C(cnt, i) * C(j, x) % mod * C(b + cnt - 1, cnt - 1) % mod * pw[i] % mod;
				ans %= mod;
			}
		}
	}
	//R
	cnt = R;
	rep(i,0,cnt){
		int j = cnt - i;
		if ((rest & 1) == (j & 1) && G >= i && B >= i){
			int g = G - i, b = B - i;
			if ((g - b + j) & 1) continue;
			int x = (g - b + j) >> 1, y = j - x;//x->g y->b
			if (x < 0 || y < 0) continue;//!!!!
			//题目里有的量是解方程解出来的时候，一定要使劲判判解是否合法
			g -= x, b -= y;
			if (g != b || g < 0) continue;
			ans += 1LL * C(cnt, i) * C(j, x) % mod * C(b + cnt - 1, cnt - 1) % mod * pw[i] % mod;
			ans %= mod;
		}
	}
}
int main(){
	scanf("%d%d%d%d",&M,&R,&G,&B);
	if (2 * M != R + G + B){ printf("0\n");return 0; }

	M *= 2;
	pw[0] = 1;
	rep(i,1,M) pw[i] = (pw[i - 1] << 1) % mod;
	fac[0] = 1;
	rep(i,1,M) fac[i] = 1LL * fac[i - 1] * i % mod;
	inv[M] = pow(fac[M], mod - 2);
	dep(i,M - 1,0) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
	M /= 2;

	R = M - R, G = M - G, B = M - B;
	calc();
	swap(R, B), calc();
	swap(R, G), calc();
	if (ans < 0) ans += mod;
	printf("%d\r\n",ans * 2 % mod);
	return 0;
}
