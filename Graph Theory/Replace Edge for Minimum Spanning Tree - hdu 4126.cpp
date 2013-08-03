#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
const double eps=1e-8;

#define MEM(a) memset(a,0,sizeof(a));
#define MEST(a) memset(a,-1,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i=1;i<=n;i++)

const int INF = 0x7f7f7f7f;
const int MAXN = 3005;

int n, m, Q, c[MAXN][MAXN];
vector<int> e[MAXN];
int mst, tot, from[MAXN], id[MAXN], f[MAXN][MAXN], g[MAXN][MAXN];

void init() {
	memset(c, 0x7f, sizeof(c));
	memset(g, 0xff, sizeof(g));
	for (int i=0; i<n; ++i) e[i].clear();
}

int prim() {
	int ret = 0;
	bool vst[MAXN] = {true};
	int d[MAXN];
	memcpy(d, c[0], sizeof(d));
	memset(from, 0, sizeof(from));
	for (int k, t = 1; t < n; ++t) {
		for (int i = k = 0; i < n; ++i)
			if (!vst[i] && d[i] < d[k]) k = i;
		ret += d[k];
		vst[k] = true;
		e[k].push_back(from[k]);
		e[from[k]].push_back(k);
		for (int i = 0; i < n; ++i)
			if (!vst[i] && c[k][i] < d[i])
				d[i] = c[from[i] = k][i];
	}
	return ret;
}

int gao(int r, int x, int pre) {
	for (int i = 0; i < e[x].size(); ++i) if (e[x][i] != pre)
		f[r][x] = min(f[r][x], gao(r, e[x][i], x));
	return f[r][x];
}

void dfs(int x, int pre) {
	int t, mi = INF;
	id[t = tot++] = x;
	for (int i = 0; i < e[x].size(); ++i)
		if (e[x][i] != pre) dfs(e[x][i], x);
	if (!x) return;
	for (int i = t; i < tot; ++i)
		mi = min(mi, f[id[i]][pre]);
	g[x][pre] = g[pre][x] = mi;
}

int main() {
	while (2==scanf("%d%d",&n,&m)) {
		if (!n && !m) break;
		init();
		for (int a,b,w,i = 0; i < m; ++i) {
			scanf("%d%d%d", &a, &b, &w);
			c[a][b] = c[b][a] = w;
		}
		mst = prim();
		memcpy(f, c, sizeof(f));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < e[i].size(); ++j)
				f[i][e[i][j]] = f[e[i][j]][i] = INF;
		for (int i = 0; i < n; ++i) gao(i, i, -1);
		dfs(tot = 0, -1);
		double sum = 0;
		scanf("%d", &Q);
		for (int a,b,w,i = 0; i < Q; ++i) {
			scanf("%d%d%d", &a, &b, &w);
			if (g[a][b] >= 0)
				sum += min(g[a][b], w) - c[a][b];
		}
		printf("%.4f\n", mst+sum/Q);
	}
}
