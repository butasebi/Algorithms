//Buta Gabriel-Sebastian (butasebi)
//University of Bucharest
#include<bits/stdc++.h>
#define MOD 1000000007
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma warning(disable:4996)
using namespace std;
int ii, tt, n, q, x, log_2[100005], top_level, lca[100005][20], inside[100005], outside[100005], now, a, b;
bool seen[100005];
vector <int> v[100005];
void logs_ceil()
{
    log_2[1] = 1;
    for(int i = 2; i <= 100000; i *= 2)
        log_2[i + 1] = 1;
    for(int i = 2; i <= 100000; i ++)
        log_2[i] = log_2[i] + log_2[i - 1];

}
void DFS(int node, int dad)
{
    //cout << "We are in " << node << "\n";
    seen[node] = true;
    lca[node][0] = dad;
    inside[node] = ++ now;
    for(int i = 1; i <= top_level; i ++)
        lca[node][i] = lca[lca[node][i - 1]][i - 1];

    for(auto &son: v[node])
    {
        //cout << "A son is " << son << "\n";
        if (!seen[son])
            DFS(son, node);
    }

    outside[node] = ++ now;
}
bool is_ancestor(int a, int b)
{
    return inside[a] <= inside[b] && outside[a] >= outside[b];
}
int lowest_common_ancestor(int a, int b)
{
    if(is_ancestor(a, b))
        return a;
    if(is_ancestor(b, a))
        return b;

    for(int i = top_level; i >= 0; i --)
        if(!is_ancestor(lca[a][i], b))
            a = lca[a][i];

    return lca[a][0];
}
void read()
{
    cin >> n >> q;
    for(int i = 2; i <= n; i ++)
    {
        cin >> x;
        v[i].push_back(x);
        v[x].push_back(i);
    }
}
void solve()
{
    top_level = log_2[n];
    DFS(1, 1);
}
void write()
{
    for(int i = 1; i <= q; i ++)
    {
        cin >> a >> b;
        cout << lowest_common_ancestor(a, b) << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    logs_ceil();
    //cin >> tt;
    tt = 1;
    for(ii = 1; ii <= tt; ii ++)
    {
        read();
        solve();
        write();
    }

    return 0;
}