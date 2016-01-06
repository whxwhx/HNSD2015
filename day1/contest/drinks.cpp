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
	return (a.a[1] < b.a[1]) || (a.a[1] == b.a[1] && a.a[2] < b.a[2]) || (a.a[1] == b.a[1] && a.a[2] == b.a[2] && a.a[3] < b.a[3]);
}
int s[N];
void add(int x, int d){
	for(;x <= n; x += (-x) & x) s[x] += d;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}
void solve(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	int t1 = l, t2 = mid + 1;
	rep(i,l,r)
		if (t1 <= mid && a[t1] < a[t2]){
			add(a[t1].a[2], 1);
			d[i] = a[t1++];
		}else {
			f[a[t2].num] = sum(a[t2].a[2]);
			d[i] = a[t2++];
		}
	rep(i,l,mid) add(a[i].a[2], -1);
	rep(i,l,r) a[i] = d[i];
}
void calc(){
	sort(a + 1, a + n + 1, cmp);
	solve(1, n);
}

LL ans = 0;
int main(){
	
	scanf("%d",&n);
	rep(i,1,n) {
		d[i].num = i;
		rep(j,0,2) scanf("%d",&d[i].a[j]);
	}

	rep(i,1,n) d[i] = a[i];
	calc();

	//case 1
	ans = n;
	//case 2
	ans += 1LL * n * (n - 1) / 2; rep(i,1,n) ans -= f[i];
	//case 3
	ans += 1LL * n * (n - 1) * (n - 2) / 6;
		//case 3.1
			rep(i,1,n) ans -= 1LL * f[i] * (f[i] - 1) / 2;
		//case3.2
			//case 3.2.1
			
			//case 3.2.2
			
	cout <<ans<<endl;
	return 0;
}
