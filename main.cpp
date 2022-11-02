//Palindromic PAL_tree
//Buta Gabriel-Sebastian (butasebi)
//University of Bucharest

//palindromes(STRING) returns a list of all the palindromes of a string
//Time complexity: O(n) where n is the length of the string
#include<bits/stdc++.h>
#define MOD 1000000007
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma warning(disable:4996)
using namespace std;
int ii, tt;
#define MAXN  1005

struct Node
{
    int start;
    int end;
    int len;
    int letter[30];
    int suffix;
}root1, root2, PAL_tree[MAXN];

// Keeps track the current Node while insertion
int cur, nr_nodes;
string s;

void insert(string & s, int index)
{
    int aux = cur;
    while (true)
    {
        int cur_len = PAL_tree[aux].len;
        if (index - cur_len >= 1 and s[index] == s[index - cur_len - 1])
            break;
        aux = PAL_tree[aux].suffix;
    }
    
    if(PAL_tree[aux].letter[s[index] - 'a'] != 0)
    {
        cur = PAL_tree[aux].letter[s[index] - 'a'];
        return;
    }

    //if node does not exist, we create one
    nr_nodes ++;

    PAL_tree[aux].letter[s[index] - 'a'] = nr_nodes;
    PAL_tree[nr_nodes].len = PAL_tree[aux].len + 2;
    PAL_tree[nr_nodes].end = index;
    PAL_tree[nr_nodes].start = index - PAL_tree[nr_nodes].len + 1;

    aux = PAL_tree[aux].suffix;
    cur = nr_nodes;

    if (PAL_tree[cur].len == 1)
    {
        PAL_tree[cur].suffix = 2;
        return;
    }
    while (true)
    {
        int cur_len = PAL_tree[aux].len;
        if (index-cur_len >= 1 and s[index] == s[index - cur_len - 1])
            break;
        aux = PAL_tree[aux].suffix;
    }

    PAL_tree[cur].suffix = PAL_tree[aux].letter[s[index] - 'a'];
}
void build_PAL_tree(string s)
{
    for (int i = 0; i < s.length(); i ++)
        insert(s, i);
}
void init()
{
    root1.len = - 1;
    root1.suffix = 1;
    
    root2.len = 0;
    root2.suffix = 1;

    PAL_tree[1] = root1;
    PAL_tree[2] = root2;

    nr_nodes = 2;
    cur = 1;
}
vector<string> palindromes(string s)
{
    init();
    build_PAL_tree(s);
    vector<string> rez;
    for (int i = 3; i <= nr_nodes; i ++)
    {
        string aux;
        for (int j = PAL_tree[i].start; j <= PAL_tree[i].end; j++)
            aux.push_back(s[j]);

        rez.push_back(aux);
    }
    return rez;
}
vector<string> pals;
void read()
{
    cin >> s;
}
void solve()
{
    pals = palindromes(s);
}
void write()
{
    for(auto &x: pals)
        cout << x << " ";
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    read();
    solve();
    write();

    return 0;
}