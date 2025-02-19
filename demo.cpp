#include <bits/stdc++.h>

// #include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define int long long
#define ll long long
#define lld long double
#define PI 3.141592653589793238462
#define INF 1e18
#define M 1000000007
#define MOD1 998244353
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define set_bits __builtin_popcountll
#define all(x) (x).begin(), (x).end()

// typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key

// CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU
// CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU
// CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU
// CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU CHAKSHU

//...............................................................//
ll gcd(ll a, ll b)
{
    if (b > a)
    {
        return gcd(b, a);
    }
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

ll expo(ll a, ll b, ll mod)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}

void extendgcd(ll a, ll b, ll *v)
{
    if (b == 0)
    {
        v[0] = 1;
        v[1] = 0;
        v[2] = a;
        return;
    }
    extendgcd(b, a % b, v);
    ll x = v[1];
    v[1] = v[0] - v[1] * (a / b);
    v[0] = x;
    return;
} // pass an arry of size1 3

ll mminv(ll a, ll b)
{
    ll arr[3];
    extendgcd(a, b, arr);
    return arr[0];
} // for non prime b

ll mminvprime(ll a, ll b) { return expo(a, b - 2, b); }

ll combination(ll n, ll r, ll m, ll *fact, ll *ifact)
{
    ll val1 = fact[n];
    ll val2 = ifact[n - r];
    ll val3 = ifact[r];
    return (((val1 * val2) % m) * val3) % m;
}

ll mod_add(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a + b) % m) + m) % m;
}
ll mod_mul(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
ll mod_sub(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}
ll mod_div(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (mod_mul(a, mminvprime(b, m), m) + m) % m;
} // only for prime m

ll phin(ll n)
{
    ll number = n;
    if (n % 2 == 0)
    {
        number /= 2;
        while (n % 2 == 0)
            n /= 2;
    }
    for (ll i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            number = (number / i * (i - 1));
        }
    }
    if (n > 1)
        number = (number / n * (n - 1));
    return number;
} // O(sqrt(N))

// void google(int t) { cout << "Case #" << t << ": "; }

vector<ll> sieveVector(int n)
{
    int *arr = new int[n + 1]();
    vector<ll> vect;
    for (int i = 2; i <= n; i++)
        if (arr[i] == 0)
        {
            vect.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                arr[j] = 1;
        }
    return vect;
}

vector<int> sieve(int n)
{
    vector<int> primes(n + 1, 1);
    primes[0] = 0;
    primes[1] = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (primes[i])
        {
            for (int j = 2 * i; j <= n; j += i)
            {
                primes[j] = 0;
            }
        }
    }
    return primes;
}
// change to j = i*i for better performance
vector<int> spf(int n)
{
    vector<int> spf(n + 1);
    for (int i = 2; i <= n; i++)
    {
        spf[i] = i;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= n; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
    return spf;
}

int binaryExponentiation(int a, int b, int mod)
{
    int ans = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ans * 1ll * a) % mod;
        }
        a = (a * 1ll * a) % mod;
        b >>= 1;
    }
    return ans;
}

/*
    INTERACTIVE PROBLEMS:

    cout<<flush;

*After every cout statement,
    so that your solution is not stored in buffer and sent later ikkatha, rather every time the solution is sent to online judge..
*Take care of cin>>t;
*/

class SGTree
{

public:
    vector<int> seg;

    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int idx, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    int query(int idx, int low, int high, int l, int r)
    {

        if (r < low || high < l)
            return INT_MAX; // no match
        if (low >= l && high <= r)
            return seg[idx]; // complete match

        // if not both, then its partial match
        int mid = (low + high) / 2;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);
        return min(left, right);
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        // updation on the array is not handled here -> arr[idx] = val; handle it outside
        if (low == high)
        {
            seg[idx] = val;
            return;
        }

        int mid = (low + high) / 2;

        if (pos <= mid)
        {
            update(2 * idx + 1, low, mid, pos, val);
        }
        else
        {
            update(2 * idx + 2, mid + 1, high, pos, val);
        }

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
};


vector<int> intNumberToBinary(int n)
{
    vector<int> ans(32, 0);
    int index = 31;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            ans[index] = 1;
        }
        index--;
        n /= 2;
    }
    return ans;
}
vector<int> llNumberToBinary(ll n)
{
    vector<int> ans(64, 0);
    int index = 63;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            ans[index] = 1;
        }
        index--;
        n /= 2;
    }
    return ans;
}
long long binaryToNumber(vector<int> binary)
{

    int n = binary.size();
    int index = n - 1;
    ll ans = 0;
    ll current = 1;
    while (index >= 0)
    {
        if (binary[index] == 1)
        {
            ans += current;
        }
        current *= 2;
        index--;
    }

    return ans;
}

int BinarySearchedIndex(vector<int> &nums, int si, int ei, int num)
{

    int ans = -1;

    while (si <= ei)
    {
        int mid = si + (ei - si) / 2;

        if (nums[mid] > num)
        {
        }
        else if (nums[mid] < num)
        {
        }
        else
        {
        }
    }

    return ans;
}

double logBase(int x, int base)
{
    return log(x) / log(base);
}

//.....................................................//
// ctrl+shift+b --> to run

// class lazySegmentTree
// {

//     struct Node
//     {
//         int min_val;
//         int count;
//         int lazy;
//     };

//     vector<Node> tree;
//     int n;

//     void buildTree(int v, int tl, int tr)
//     {
//         if (tl == tr)
//         {
//             tree[v] = {1, 0, 1};
//             return;
//         }
//         int tm = (tl + tr) / 2;

//         buildTree(2 * v, tl, tm);
//         buildTree(2 * v + 1, tm + 1, tr);

//         merge(v);
//     }

//     void apply(int v, int tl, int tr, int val)
//     {
//         tree[v].min_val += val;
//         tree[v].lazy += val;
//     }

//     void push(int v, int tl, int tr)
//     {
//         if (tree[v].lazy == 0)
//         {
//             return;
//         }
//         int tm = (tl + tr) / 2;
//         apply(2 * v, tl, tm, tree[v].lazy);
//         apply(2 * v + 1, tm + 1, tr, tree[v].lazy);
//         tree[v].lazy = 0;
//     }

//     void merge(int v)
//     {
//         if (tree[2 * v].min_val < tree[2 * v + 1].min_val)
//         {
//             tree[v].min_val = tree[2 * v].min_val;
//             tree[v].count = tree[2 * v].count;
//         }
//         else if (tree[2 * v].min_val > tree[2 * v + 1].min_val)
//         {
//             tree[v].min_val = tree[2 * v + 1].min_val;
//             tree[v].count = tree[2 * v + 1].count;
//         }
//         else
//         {
//             tree[v].min_val = min(tree[2 * v].min_val, tree[2 * v + 1].min_val);
//             tree[v].count = tree[2 * v].count + tree[2 * v + 1].count;
//         }
//     }

//     void updateRange(int v, int tl, int tr, int l, int r, int addend)
//     {

//         if (l > r)
//         {
//             return;
//         }
//         if (l == tl && r == tr)
//         {
//             apply(v, tl, tr, addend);
//             return;
//         }

//         push(v, tl, tr);
//         int tm = (tl + tr) / 2;

//         updateRange(v, tl, tm, l, min(tm, r), addend);
//         updateRange(v, tm + 1, tr, max(tm + 1, l), r, addend);

//         merge(v);
//     }

//     pair<int, int> queryRange(int v, int tl, int tr, int l, int r)
//     {
//         if (l > r)
//             return {INT_MAX, 0};
//         if (l <= tl && tr <= r)
//         {
//             return {tree[v].min_val, tree[v].count};
//         }

//         push(v, tl, tr);
//         int tm = (tl + tr) / 2;
//         auto left = queryRange(v * 2, tl, tm, l, min(r, tm));
//         auto right = queryRange(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);

//         if (left.first < right.first)
//         {
//             return left;
//         }
//         else if (left.first > right.first)
//         {
//             return right;
//         }
//         else
//         {
//             return {left.first, left.second + right.second};
//         }
//     }

// public:
//     lazySegmentTree(int _n)
//     {
//         n = _n;
//         tree.resize(4 * n);
//         buildTree(1, 0, n - 1);
//     }

//     void updateRange(int l, int r, int addend)
//     {
//         updateRange(1, 0, n - 1, l, r, addend);
//     }

//     pair<int, int> queryRange(int l, int r)
//     {
//         queryRange(1, 0, n - 1, l, r);
//     }

//     int get_mantained()
//     {
//         pair<int, int> res = queryRange(0, n - 1);
//         assert(res.first == 0);
//         return n - res.second;
//     };
// };

// int binary(vector<int> &nums, int &n, int x)
// {

//     int si = 0;
//     int ei = n - 1;
//     int ans = -2;
//     while (si <= ei)
//     {
//         int mid = (si + ei) / 2;

//         if (nums[mid] < x)
//         {
//             si = mid + 1;
//         }
//         else
//         {
//             ans = mid;
//             ei = mid - 1;
//         }
//     }

//     return ans + 1;
// }

int binarySearch(vector<int> &current, int &size, int num)
{
    int si = 0;
    int ei = size - 1;
    int ans = -1;
    while (si <= ei)
    {
        int mid = (si + ei) / 2;

        if (current[mid] <= num)
        {
            ans = mid;
            ei = mid - 1;
        }
        else
        {
            si = mid + 1;
        }
    }
    return ans;
}

class DisjointSet
{
    vector<int> rank, parent;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};


int findPos(vector<int>& currentVec, int num){

    int si=0;
    int ei=currentVec.size()-1;

    int upper=-1;
    while(si<=ei){

        int mid=si + (ei-si)/2;

        if(currentVec[mid] > num){
            upper=mid;
            ei=mid-1;
        }
        else{
            si=mid+1;
        }
    }

    if(upper == -1){
        return currentVec.size();
    }
    return upper;

}

int binaSea(vector<int>& currentVec, int num){

    int si=0;
    int ei=currentVec.size()-1;

    int lower=-1;
    while(si<=ei){
        int mid=si + (ei-si)/2;

        if(currentVec[mid] < num){
            lower=mid;
            si=mid+1;
        }
        else{
            ei=mid-1;
        }
    }

    if(lower == -1){
        return 0;
    }
    return lower+1;

}

bool comp(pair<int,int> p1, pair<int,int> p2){
    return p1.second<p2.second;
}

void testcases(int t)
{
    int n;
    cin>>n;

    vector<int> nums(n,0);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    int largest=0;
    int ans=0;
    for(int i=0; i<n; i++){
        if(nums[i] > largest){
            ans++;
            largest=nums[i];
        }
    }   
    cout<<ans<<endl;
} 

signed main()
{
    int t = 1;
    // cin >> t;

    for (int i = 0; i < t; i++)
    {
        testcases(i + 1);
    }
}