//Buta Gabriel-Sebastian, University of Bucharest
#include<bits/stdc++.h>
using namespace std;
int n, m, i, alfa, beta, total_cost, d[200005], nr_edges;
struct edge
{
    int x, y, c;
}v[200005], sol[200005];
bool cmp(edge a, edge b)
{
    return a.c < b.c;
}
int dad(int x)
{
    int y = x;
    while(x != d[x])
        x = d[x];
    while(y != x)
    {
        int aux = d[y];
        d[y] = x;
        y = aux;
    }
    return x;
}
int main()
{
    ifstream f("apm.in");
    ofstream g("apm.out");
    f >> n >> m;
    for(i = 1; i <= n; i ++)
        d[i] = i;
    for(i = 1; i <= m; i ++)
        f >> v[i].x >> v[i].y >> v[i].c;
    sort(v + 1, v + m + 1, cmp);
    for(i = 1; i <= m; i ++)
    {
        alfa = dad(v[i].x);
        beta = dad(v[i].y);
        if(alfa != beta)
        {
            d[alfa] = beta;
            total_cost = total_cost + v[i].c;
            nr_edges ++;
            sol[nr_edges].x = v[i].x;
            sol[nr_edges].y = v[i].y;
        }
    }
    g << total_cost << "\n";
    g << nr_edges << "\n";
    for(i = 1; i <= nr_edges; i ++)
            g <<sol[i].x << " " << sol[i].y << "\n";
    return 0;
}
