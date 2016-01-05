#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 10000010;
bool cnt[N];
LL gcd(LL a, LL b){
	return b ? gcd(b, a % b) : a;
}
LL lcm(LL a, LL b){
	return a / gcd(a, b) * b;
}

typedef long long LL;
struct fac{
	LL z, m;
};
fac operator + (const fac &a, const fac &b){
	LL g = gcd(a.m, b.m);
	return (fac){a.z * (b.m / g) + b.z * (a.m / g), a.m / g * b.m};
}
fac operator - (const fac &a, const fac &b){
	LL g = gcd(a.m, b.m);
	return (fac){a.z * (b.m / g) - b.z * (a.m / g), a.m / g * b.m};
}

void dfs(fac a, int b, int k, int d){
	if (!k) cnt[d] = 1; else {
		if (!a.z) return;
		rep(i,b,1000){
			if (a.m * k < a.z * i) break;
			if (a.m > i * a.z) continue;
			dfs(a - (fac){1, i}, i, k - 1, lcm(d, i));
		}
	}
}

int s[N], l = 0;
map<int, int> f;

void dfs(int x, int c, int F){
	if (x > l) f[c] += F;
	else {
		dfs(x + 1, c, F);
		dfs(x + 1, lcm(c, s[x]), -F);
	}
}

int main(){
	rep(k,2,7){
		l = 0;
		f.clear();
		rep(i,1,N - 10) cnt[i] = 0;
		dfs((fac){1,1},2,k,1);
		
		int c1 = 0;
		rep(i,1,N - 10) if (cnt[i]){
			int t = (N - 10) / i;
			rep(j,2,t) cnt[i * j] = 0;
			s[++l] = i;
		}

		dfs(1, 1, 1);
		printf("{");
		for(map<int, int>::iterator it = f.begin(); it != f.end(); it++)
			if (it->second) printf(",{%d,%d}",it->first,it->second);
		printf("},\n");
	}
	return 0;
}
