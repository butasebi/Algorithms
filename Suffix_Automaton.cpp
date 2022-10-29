//Suffix Automaton
// By Buta Gabriel-Sebastian (butasebi)
//University of Bucharest

//ATTENTION! Always use sa_init() to reset/initiate the string automaton
// sa_extend(CHAR) to append the character CHAR at the end of the string
// sa_extend_string(STRING)  to append the string STRING at the end of the string
//check_occ(STRING) checks if STRING is a substring of the big string
//nr_subs(STRING) checks the number of different substrings of STRING
//sum_len_subs(STRING) checks the sum of lengths of all substrings of STRING
// kth_subs(STRING, k) finds the k-th substring of the string STRING (k = 0 => empty string)
//smallest_cyclic_shift(STRING) find the smallest cyclic shift of the string
//nr_occurrences(STRING, STRING2) returns the number of occurrences of STRING2 in STRING
//first_occurrence(STRING, STRING2) returns the first occurrence of STRING2 in STRING (returns the position where STRING2 begins (considering STRING indexed by 1))
//all_occurrences(STRING, STRING2) returns all the possition where STRING2 occurs in STRING as a vector<int> list, if no occurrence returns empty list (returns the position where STRING2 begins (considering STRING indexed by 1))
//lcs(STRING, STRING2) returns the longest common substring between STRING and STRING2
//EVERYTHING FUNCTION FROM ABOVE IS DONE IN O(length(STRING))
#include<bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma warning(disable:4996)
using namespace std;
long long ii, tt;
struct state {
    int len, link;
    map<char, int> next;
    int first_occ;
    bool is_clone = false;
    vector <int> inverse_link;
};
const int MAXLEN = 100000;
state st[MAXLEN * 2];
int divine_cnt[MAXLEN * 2], cnt[MAXLEN * 2];
vector <int> all_occs;
int sz, last;
void sa_init()
{
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}
void sa_extend(char c)
{
    int cur = sz++;
    divine_cnt[cur] = 1;
    st[cur].len = st[last].len + 1;
    st[cur].first_occ = st[cur].len;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].first_occ =  st[q].first_occ;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
void sa_extend_string(string A)
{
    for(int i = 0; i < A.size(); i ++)
        sa_extend(A[i]);
}
bool check_occ(string A)
{
    int current_state = 0;
    for(int i = 0; i < A.size(); i ++)
        if(st[current_state].next.count(A[i]))
            current_state = st[current_state].next[A[i]];
        else
            return false;

    return true;
}
int dp[MAXLEN * 2], ans[MAXLEN * 2];
bool seen[MAXLEN * 2];
void DFS_sum(int state)
{
    seen[state] = true;
    dp[state] = 1;
    ans[state] = 0;
    for(auto &x: st[state].next)
    {
        if(!seen[x.second])
            DFS_sum(x.second);
        dp[state] += dp[x.second];
        ans[state] += dp[x.second] + ans[x.second];
    }

}

void DFS_nr(int state)
{
    seen[state] = true;
    dp[state] = 1;
    for(auto &x: st[state].next)
    {
        if(!seen[x.second])
            DFS_nr(x.second);
        dp[state] += dp[x.second];
    }

}

void DFS_kth(int state, int poz, string & rez)
{
    //cout << "Intrat, in starea " << state << " cauta pozitia " << poz << " cu sirul curent " << rez << "\n";
    if(poz == 0)
        return;
    int cur = 0;
    int new_poz = poz - 1;
    for(char k = 'a'; k <= 'z'; k ++)
        if(st[state].next.count(k))
        {
            cur += dp[st[state].next[k]];
            if(cur >= poz)
            {
                rez.push_back(k);
                DFS_kth(st[state].next[k], new_poz, rez);
                return;
            }
            else
                new_poz -= dp[st[state].next[k]];
        }
}

void DFS_cnt(int state)
{
    seen[state] = true;
    for(auto &x: st[state].next)
    {
        //cout << "We are searching for " << x.second << " which is " << seen[x.second] << "\n";
        if(!seen[x.second])
            DFS_cnt(x.second);
    }
    if(state != 0)
        //cout << "State " << state << ": added " << cnt[state] << " to the " << st[state].link << " state!\n";
        cnt[st[state].link] += cnt[state];

}

void DFS_all_occs(int state, int len)
{
    if (!st[state].is_clone)
        all_occs.push_back(st[state].first_occ - len + 1);
    for (int new_state : st[state].inverse_link)
        DFS_all_occs(new_state, len);
}

int sum_len_subs(string A)
{
    memset(dp, 0, sizeof(dp));
    memset(seen, false, sizeof(seen));
    sa_init();
    sa_extend_string(A);

    int rez = 0;
    DFS_sum(0);
    return ans[0];

}
int nr_subs(string A)
{
    memset(dp, 0, sizeof(dp));
    memset(seen, false, sizeof(seen));
    memset(ans, 0, sizeof(ans));
    sa_init();
    sa_extend_string(A);

    DFS_nr(0);
    return dp[0] - 1;

}
string kth_subs(string A, int poz)
{
    memset(dp, 0, sizeof(dp));
    memset(seen, false, sizeof(seen));
    sa_init();
    sa_extend_string(A);

    DFS_nr(0);

    string rez = "";
    DFS_kth(0, poz, rez);

    return rez;
}

string smallest_cyclic_shift(string A)
{
    sa_init();
    sa_extend_string(A);
    sa_extend_string(A);

    string rez = "";

    int state = 0;
    for(int i = 1; i <= A.size(); i ++)
    {
        for(char k = 'a'; k <= 'z'; k ++)
            if(st[state].next.count(k))
            {
                state = st[state].next[k];
                rez.push_back(k);
                break;
            }
    }
    return rez;
}
int nr_occurrences(string A, string B)
{
    memset(seen, false, sizeof(seen));
    sa_init();
    sa_extend_string(A);

    for(int i = 0; i < 2 * MAXLEN; i ++)
        cnt[i] = divine_cnt[i];

//    for(int i = 0; i < sz; i ++)
//        cout << "State " << i << ": divine_cnt is " << divine_cnt[i] << "\n";

    DFS_cnt(0);


    bool ok = true;
    int current_state = 0;
    for(int i = 0; i < B.size(); i ++)
        if(st[current_state].next.count(B[i]))
            current_state = st[current_state].next[B[i]];
        else
        {
            ok = false;
            break;
        }

    if(ok == 0)
        return 0;
//        for(int i = 0; i < sz; i ++)
//            cout << "State " << i << ": cnt is " << cnt[i] << "\n";
    return cnt[current_state];
}
int first_occurrence(string A, string B)
{
    sa_init();
    sa_extend_string(A);

    bool ok = true;
    int current_state = 0;
    for(int i = 0; i < B.size(); i ++)
        if(st[current_state].next.count(B[i]))
            current_state = st[current_state].next[B[i]];
        else
        {
            ok = false;
            break;
        }

    if(ok == 0)
        return -1;
    return st[current_state].first_occ - B.size() + 1;
}
vector<int> all_occurrences(string A, string B)
{
    all_occs.clear();
    sa_init();
    sa_extend_string(A);

    for (int i = 1; i < sz; i ++)
        st[st[i].link].inverse_link.push_back(i);

    bool ok = true;
    int current_state = 0;
    for(int i = 0; i < B.size(); i ++)
        if(st[current_state].next.count(B[i]))
            current_state = st[current_state].next[B[i]];
        else
        {
            ok = false;
            break;
        }

    if(ok == 0)
        return {};

    DFS_all_occs(current_state, B.size());

    return all_occs;
}

string lcs (string A, string B)
{
    sa_init();
    sa_extend_string(A);

    int maxx = 0, poz_maxx = 0, cur_length = 0;
    int current_state = 0;
    for (int i = 0; i < B.size(); i ++)
    {
        while (current_state && !st[current_state].next.count(B[i]))
        {
            current_state = st[current_state].link ;
            cur_length = st[current_state].len ;
        }
        if (st[current_state].next.count(B[i]))
        {
            current_state = st [current_state].next[B[i]];
            cur_length ++;
        }
        if (cur_length > maxx)
        {
            maxx = cur_length;
            poz_maxx = i;
        }
    }
    return B.substr(poz_maxx - maxx + 1, maxx);
}

void read()
{
//    string alfa = "alabalaportocalabbbbbb";
//    cout << lcs(alfa, "d");
}
void solve()
{
}
void write()
{

}
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

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
