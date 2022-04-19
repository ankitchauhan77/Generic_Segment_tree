#include <bits/stdc++.h>
#define int long long
#define ll long long
ll md = 1000000007;
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);
#define pb push_back
#define g(v, i, j) get<i>(v[j])
#define vi vector<int>
#define vll vector<ll>
#define srt(v) sort(v.begin(), v.end())
#define rsrt(v) sort(v.begin(), v.end(), greater<int>())
#define fi(i, a, b) for (int i = a; i < b; i++)
#define fll(i, a, b) for (ll i = a; i < b; i++)
using namespace std;
//using namespace std::chrono;
template <typename T>
T pw(T a, T b)
{
    T c = 1, m = a;
    while (b)
    {
        if (b & 1)
            c = (c * m);
        m = (m * m), b /= 2;
    }
    return c;
}
template <typename T>
T ceel(T a, T b)
{
    if (a % b == 0)
        return a / b;
    else
        return a / b + 1;
}
template <typename T>
T my_log(T n, T b)
{
    T i = 1, ans = 0;
    while (1)
    {
        if (i > n)
        {
            ans--;
            break;
        }
        if (i == n)
            break;
        i *= b, ans++;
    }
    return ans;
}
template <typename T>
T gcd(T a, T b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
template <typename T>
T mysqt(T a)
{
    T ans = 1;
    while (ans * ans <= a)
        ans++;
    ans--;
    return ans;
}
ll pwmd(ll a, ll b)
{
    ll c = 1, m = a;
    while (b)
    {
        if (b & 1)
            c = (c * m) % md;
        m = (m * m) % md;
        b /= 2;
    }
    return c;
}
ll modinv(ll n)
{
    return pwmd(n, md - 2);
}
ll inverse(ll i)
{
    if (i == 1)
        return 1;
    return (md - ((md / i) * inverse(md % i)) % md + md) % md;
}
bool sortbysec(const pair<ll, ll> &a,
               const pair<ll, ll> &b)
{
    return (a.second < b.second);
}
/* auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cerr << "Time taken: "
         << duration.count()<< "ms" <<"\n";*/
vector<char> capl = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
vector<char> sml = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
template <typename T>
string conv(T a)
{
    string b;
    T e = 2;
    T c = my_log(a, e);
    c++, b = '1';
    for (T i = 0; i < c - 1; i++)
    {
        T k = a >> (c - 2 - i);
        if (k & 1)
            b += '1';
        else
            b += '0';
    }
    if (a == 0)
        return "0";
    return b;
}
/*
KEYNOTES:
------------------------------------------
merge(X,identity_element) = X
------------------------------------------
------------------------------------------
identity_transformation.combine(X) = X
------------------------------------------
------------------------------------------
ALWAYS: older_update.combine(newer_update)
------------------------------------------
*/
// example: addition: identity element is 0
// a + 0 = a or 0 + a = a
// min(x,INF) = x
struct node
{
    //int mn = INF;
    int q = 0;
    // use more variables if you want more information
    // these default values should be identity_element
    node() {}
    node(int val)
    {
        q = val;
    }
    void merge(const node &l, const node &r)
    { // store the thing you wanna query

        q = l.q + r.q;
        // if we wanted the maximum, then we would do
        // like q = max(l.v,r.v)
    }
};
// example: add on a range: identity transformation = 0
// old += new
// if old is identity which is 0, then 0 + new which new
struct update
{
    int q = 0; // 4
    // use more variables if you want more information
    // these default values should be identity_transformation
    update() {}
    update(int val)
    {
        q = val; // 5
    }
    // combine the current my_update with the other my_update (see keynotes)
    void combine(update &other, const int32_t &tl, const int32_t &tr)
    {
        q += other.q; // 6
        // you can be sure that the "other" is newer than current
    }
    // store the correct information in the my_node x
    void apply(node &x, const int32_t &tl, const int32_t &tr)
    {
       x.q += (tr - tl + 1) * q;
    }
};
//template <typename node, typename update>
struct segtree
{
    int len;
    vector<node> t;
    vector<update> u;
    vector<bool> lazy;
    node identity_element;
    update identity_transformation;
    segtree(int l)
    {
        len = l;
        t.resize(4 * len);
        u.resize(4 * len);
        lazy.resize(4 * len);
        identity_element = node();
        identity_transformation = update();
    }
    void pushdown(const int32_t &v, const int32_t &tl, const int32_t &tr)
    {
        if (!lazy[v])
            return;
        int32_t tm = (tl + tr) >> 1;
        apply(v << 1, tl, tm, u[v]);
        apply(v << 1 | 1, tm + 1, tr, u[v]);
        u[v] = identity_transformation;
        lazy[v] = 0;
    }
    void apply(const int32_t &v, const int32_t &tl, const int32_t &tr, update upd)
    {
        if (tl != tr)
        {
            lazy[v] = 1;
            u[v].combine(upd, tl, tr);
        }
        upd.apply(t[v], tl, tr);
    }
    template <typename T>
    void build(const T &arr, const int32_t &v, const int32_t &tl, const int32_t &tr)
    {
        if (tl == tr)
        {
            t[v] = arr[tl];
            return;
        }
        int32_t tm = (tl + tr) >> 1;
        build(arr, v << 1, tl, tm);
        build(arr, v << 1 | 1, tm + 1, tr);
        t[v].merge(t[v << 1], t[v << 1 | 1]);
    }
    node query(const int32_t &v, const int32_t &tl, const int32_t &tr, const int32_t &l, const int32_t &r)
    {
        if (l > tr || r < tl)
        {
            return identity_element;
        }
        if (tl >= l && tr <= r)
        {
            return t[v];
        }
        pushdown(v, tl, tr);
        int32_t tm = (tl + tr) >> 1;
        node a = query(v << 1, tl, tm, l, r), b = query(v << 1 | 1, tm + 1, tr, l, r), ans;
        ans.merge(a, b);
        return ans;
    }
    // rupd = range update
    void rupd(const int32_t &v, const int32_t &tl, const int32_t &tr, const int32_t &l, const int32_t &r, const update &upd)
    {
        if (l > tr || r < tl)
        {
            return;
        }
        if (tl >= l && tr <= r)
        {
            apply(v, tl, tr, upd);
            return;
        }
        pushdown(v, tl, tr);
        int32_t tm = (tl + tr) >> 1;
        rupd(v << 1, tl, tm, l, r, upd);
        rupd(v << 1 | 1, tm + 1, tr, l, r, upd);
        t[v].merge(t[v << 1], t[v << 1 | 1]);
    }
    public:
    template <typename T>
    void build(const T &arr)
    {
        build(arr, 1, 0, len - 1);
    }
    node query(const int32_t &l, const int32_t &r)
    {
        return query(1, 0, len - 1, l, r);
    }
    void rupd(const int32_t &l, const int32_t &r, const update &upd)
    {
        rupd(1, 0, len - 1, l, r, upd);
    }
};
int main()
{
    vector<int> v = {1,2,3,4,5,6};
    segtree s(6);
    s.build(v);
    s.rupd(1,3,5);
    fi(i, 0, 6) cout << s.query(i, i).q << " ";
    cout << "\n";
    cout << s.query(0, 5).q;
}
