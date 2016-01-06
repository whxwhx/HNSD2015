#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100010;
typedef long long LL;
struct drink{
	int a[3], num;
}a[N], d[N], t[N];
int n;
bool cmp (const drink &a, const drink &b){
	return (a.a[0] < b.a[0]) || (a.a[0] == b.a[0] && a.a[1] < b.a[1]) || (a.a[0] == b.a[0] && a.a[1] == b.a[1] && a.a[2] < b.a[2]);
}
bool operator < (const drink &a, const drink &b){
	return (a.a[1] < b.a[1]) || (a.a[1] == b.a[1] && a.a[2] < b.a[2]) || (a.a[1] == b.a[1] && a.a[2] == b.a[2] && a.a[0] < b.a[0]);
}
int s[N];
void add(int x, int d){
	for(;x <= (n << 1) + 1; x += (-x) & x) s[x] += d;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}
int f[N];
void solve(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	int t1 = l, t2 = mid + 1;
	rep(i,l,r)
		if (t2 > r || (t1 <= mid && a[t1] < a[t2])){
			add(a[t1].a[2], 1);
			t[i] = a[t1++];
		}else {
			f[a[t2].num] += sum(a[t2].a[2]);
			t[i] = a[t2++];
		}
	rep(i,l,mid) add(a[i].a[2], -1);
	rep(i,l,r) a[i] = t[i];
}
void calc(){
	sort(a + 1, a + n + 1, cmp);
	solve(1, n);
}

LL ans = 0;
int F[N][8];
int main(){
	scanf("%d",&n);
	rep(i,1,n) {
		d[i].num = i;
		rep(j,0,2) scanf("%d",&d[i].a[j]);
	}

	rep(i,1,n) a[i] = d[i];
	calc();

	//case 1
	ans = n;
	//case 2
	ans += 1LL * n * (n - 1) / 2; rep(i,1,n) ans -= f[i];
	//case 3
	ans += 1LL * n * (n - 1) * (n - 2) / 6;
		//case 3.1
			rep(i,1,n) ans += 1LL * f[i] * (f[i] - 1) / 2;
		//case 3.2
			rep(i,0,7){
				rep(j,1,n) f[j] = 0;
				rep(j,1,n) {
					a[j].num = d[j].num;
					rep(k,0,2) if (i >> k & 1) a[j].a[k] = -d[j].a[k] + n + 1; else a[j].a[k] = d[j].a[k] + n + 1;
				}
				calc();
				rep(j,1,n) F[j][i] = f[j];
			}
			rep(i,1,n){
				rep(j,0,7) rep(k,j,7) if ((j | k) == 7) {
					if (j != k) ans -= 1LL * F[i][j] * F[i][k]; else ans -= 1LL * F[i][j] * (F[i][k] - 1) / 2;
				}
			}
	return 0;
}
