#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 200100, mod = 999999599 - 1, Mod = 999999599;
int t[N], s[N];
int pow(int a, int b){
	int w = 1;
	for(;b; b >>= 1, a = 1LL * a * a % Mod) if (b & 1) w = 1LL * w * a % Mod;
	return w;
}
int main(){
	int n, m; scanf("%d%d",&n,&m);
	int T = (int)(sqrt(n) + 0.5);
	s[0] = 1, t[0] = 1;
	rep(j,1,T)
		rep(i,j,n) {
			s[i] = (s[i] + s[i - j]) % mod;
			if (i + j * T <= n) t[i + j * T] += s[i - j], t[i + j * T] %= mod;
		}
	int ans = 0;
	rep(i,0,n) ans = (ans + 1LL * s[i] * t[n - i]) % mod;
	printf("%d\n",pow(m, ans));
}
