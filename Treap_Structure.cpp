/*  Treap data-structure
--- S.insert(x) to insert x in the structure
--- S.erase(x) to erase x from the structure (if it's not there then it does nothing)
--- S.minn() to find the minimum value from the structure
--- S.maxx() to find the maximum value from the structure
--- S.cardinal() to find the number of elements from the structure
--- S.is_in(x) return true if x is in the structure and false otherwise
--- S.succesor(x) returns the smallest element greater or equal to x (if you want greater (not equal) than x then uncomment line 151, comment 152)
--- S.predecesor(x) returns the biggest element smaller or equal to x (if you want smaller (not equal) than x then uncomment line 162, comment 163)
--- S.k_element(k) returns the element with k-th biggest value. If such element doesn't exist returns -INF
--- S.poz(x) returns the position of the element x for the sorted array (if x is not in the structure returns -1)
*/
#include <bits/stdc++.h>
#define MAX 2147483647
#define MIN -2147483647
#define INF MAX
using namespace std;
int max_of(int a, int b){if(a > b)return a;return b;}
int min_of(int a, int b){if(a < b)return a;return b;}
struct Nod
{
    int key;
    int priority;
    int weight;
    Nod* left_son;
    Nod* right_son;
};
Nod* nil = NULL;
struct treap
{
    Nod* root;
    void insert(int x)
    {
        insertion(root, x);
    }
    void insertion(Nod* & node, int x)
    {
        if(node == nil)
        {
            node = new Nod;
            node -> key = x;
            node -> priority = rand();
            node -> weight = 1;
            node -> left_son = NULL;
            node -> right_son = NULL;
            return;
        }
        if(x <= node -> key)insertion(node -> left_son, x);
        else insertion(node -> right_son, x);
        node -> weight = 1;
        if(node -> left_son != nil)node -> weight = node -> weight + node -> left_son -> weight;
        if(node -> right_son != nil)node -> weight = node -> weight + node -> right_son -> weight;

        balance(node);
    }
    void balance(Nod* & node)
    {
        if(node -> left_son != nil && node -> left_son -> priority > node -> priority)rotate_left(node);
        else if(node -> right_son != nil && node -> right_son -> priority > node -> priority)rotate_right(node);
    }
    void rotate_left(Nod* & node)
    {
        int weight_aux = 1;
        if(node -> left_son -> right_son != nil)weight_aux += node -> left_son -> right_son -> weight;
        if(node -> right_son != nil)weight_aux += node -> right_son -> weight;
        Nod* aux = node -> left_son;
        aux -> weight = node -> weight;
        node -> left_son = aux -> right_son, aux -> right_son = node;
        node = aux;
        node -> right_son -> weight = weight_aux;
    }
    void rotate_right(Nod* & node)
    {
        int weight_aux = 1;
        if(node -> right_son -> left_son != nil)weight_aux += node -> right_son -> left_son -> weight;
        if(node -> left_son != nil)weight_aux += node -> left_son -> weight;
        Nod* aux = node -> right_son;
        aux -> weight = node -> weight;
        node -> right_son = aux -> left_son, aux -> left_son = node;
        node = aux;
        node -> left_son -> weight = weight_aux;
    }
    void erase(int x)
    {
        eraser(root, x);
    }
    void eraser(Nod* & node, int x)
    {
        if(node == nil)return;
        if(x < node -> key)eraser(node -> left_son, x);
        else if(x > node -> key)eraser(node -> right_son, x);
        else // x == node -> key
        {
            if(node -> left_son == nil && node -> right_son == nil)
            {
                delete node;
                node = nil;
                //cout << "Delete successfull!\n";
                return;
            }
            else if(node -> left_son == nil)
            {
                rotate_right(node);
                eraser(node, x);
            }
            else if(node -> right_son == nil)
            {
                rotate_left(node);
                eraser(node, x);
            }
            else if(node -> left_son -> priority > node -> right_son -> priority)
            {
                rotate_left(node);
                eraser(node, x);
            }
            else
            {
                rotate_right(node);
                eraser(node, x);
            }
        }
        node -> weight = 1;
        if(node -> left_son != nil)node -> weight = node -> weight + node -> left_son -> weight;
        if(node -> right_son != nil)node -> weight = node -> weight + node -> right_son -> weight;
    }
    int minn()
    {
        if(root == nil)return 0;
        Nod* aux = root;
        while(aux -> left_son != nil)
            aux = aux -> left_son;
        return aux -> key;
    }
    int maxx()
    {
        if(root == nil)return 0;
        Nod* aux = root;
        while(aux -> right_son != nil)
            aux = aux -> right_son;
        return aux -> key;
    }
    int succesor(int x)
    {
        return aux_suc(root, x);
    }
    int aux_suc(Nod* & node, int x)
    {
        if(node == nil)return MAX;
        //if(node -> key > x)return min_of(node -> key, aux_suc(node -> left_son, x));
        if(node -> key >= x)return min_of(node -> key, aux_suc(node -> left_son, x));
        else return aux_suc(node -> right_son, x);
    }
    int predecesor(int x)
    {
        return aux_predd(root, x);
    }
    int aux_predd(Nod* & node, int x)
    {
        if(node == nil)return MIN;
        //if(node -> key < x)return max_of(node -> key, aux_predd(node -> right_son, x));
        if(node -> key <= x)return max_of(node -> key, aux_predd(node -> right_son, x));
        else return aux_predd(node -> left_son, x);
    }
    int k_element(int poz)
    {
        bool found = false;
        int aux = find_elem_of(root, poz, found);
        if(found == false)return -INF;
        return aux;
    }
    int find_elem_of(Nod* & node, int poz, bool & found)
    {
        if(node == nil)return 0;
        int aux;
        if(node -> left_son != nil)aux = node -> left_son -> weight;
        else aux = 0;
        if(aux + 1 == poz)
        {
            found = true;
            return node -> key;
        }
        if(aux + 1 < poz)return find_elem_of(node -> right_son, poz - aux - 1, found);
        else return find_elem_of(node -> left_son, poz, found);
    }
    int cardinal()
    {
        if(root == nil)return 0;
        return root -> weight;
    }
    int is_in(int x)
    {
        return is_in_search(root, x);
    }
    int poz(int x)
    {
        bool found = false;
        int poz = find_poz_of(root, x, found);
        if(found == false)return -1;
        else return poz;
    }
    int find_poz_of(Nod* & node, int x, bool & found)
    {
        if(node == nil)return 0;
        if(node -> key > x)return find_poz_of(node -> left_son, x, found);
        else if(node -> key < x)
        {
            if(node -> left_son != nil)return node -> left_son -> weight + 1 + find_poz_of(node -> right_son, x, found);
            else return 1 + find_poz_of(node -> right_son, x, found);
        }
        else
        {
            found = true;
            if(node -> left_son != nil)return  node -> left_son -> weight + 1;
            else return 1;
        }
    }
    int is_in_search(Nod* & node, int x)
    {
        if(node == nil)return 0;
        if(node -> key == x)return 1;
        if(node -> key > x)return is_in_search(node -> left_son, x);
        else return is_in_search(node -> right_son, x);
    }
};
// The treap can be declared like on the line bellow
//treap S;
int main()
{
    return 0;
}
