/**
 * 给出题人：要想折磨别人，必先折磨自己（和CEM）！
 * 给切题人：这是一道很水的题目，却折磨了两个可怜的孩子两天。
*/

#define MXN (1000020)

#include <stdio.h>
#include <stdlib.h>

#include <algorithm>

struct ID {
    long long v;
    int w;
    bool operator<(const ID I) const { return v < I.v; }
} id[MXN];

long long bound[MXN];

class XDS {
    struct Node {
        int l, r, s;
        int w, a;
        Node *ls, *rs;
    } * root;

    int qry(Node *x) { return (x) ? (x->a) : (0); }

    void rcnt(Node *x, int w) {
        if (x) x->a = (x->w += w) ? (x->s) : (qry(x->ls) + qry(x->rs));
    }

    void up(Node *x) {
        if (!x || !x->ls || !x->rs) return;
        int cmp = std::min(x->ls->w, x->rs->w);
        rcnt(x->ls, -cmp), rcnt(x->rs, -cmp), rcnt(x, cmp);
    }
    void down(Node *x) {
        if (!x || !x->ls || !x->rs) return;
        rcnt(x->ls, x->w), rcnt(x->rs, x->w), rcnt(x, -x->w);
    }

    void build(Node *&x, int l, int r) {
        if (r < l) return;
        x = (Node *)calloc(sizeof(Node), 1);
        x->l = l, x->r = r, x->s = r - l + 1;
        if (l == r)
            x->w = id[l].w;
        else
            build(x->ls, l, (l + r) / 2), build(x->rs, (l + r) / 2 + 1, r);
        up(x);
    }

    int query(Node *x, int L, int R) {
        if (!x || x->r < L || R < x->l) return 0;
        return (L <= x->l && x->r <= R) ? (x->a) : (down(x), query(x->ls, L, R) + query(x->rs, L, R));
    }

    void modify(Node *x, int &L, int &R, int &W) {
        if (!x || x->r < L || R < x->l) return;
        if (x->l == x->r)
            x->w += W;
        else
            modify(x->ls, L, R, W), modify(x->rs, L, R, W);
        up(x);
    }

   public:
    void build(register int n) { build(root, 0, n - 1); }
    int modify(register int l, register int r, register int w) {
        if (l <= r && (w > 0 || query(root, l, r) == r - l + 1))
            modify(root, l, r, w);
        return root->a;
    }
} xds;

long long gett() {
    long long x = 0;
    register char c = getchar();
    while (c < '0' || '9' < c) c = getchar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x;
}
char s[20];
void putt(register int x) {
    if (x) {
        register int i = 0;
        while (x) s[++i] = (x % 10) + '0', x /= 10;
        while (i) putchar(s[i--]);
    } else
        putchar('0');
    putchar('\n');
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("00.in", "r", stdin);
#endif

    register int n, m;
    n = gett(), m = gett();

    for (register int i = 0; i < n; ++i)
        id[i].v = gett();
    for (register int i = 0; i < n; ++i)
        id[i].w = gett();
    std::sort(id, id + n);
    for (register int i = 0; i < n; ++i)
        bound[i] = id[i].v;
    xds.build(n);
    int o;
    register long long l, r;
    while (m-- > 0) {
        o = gett(), l = gett(), r = gett();
        putt(n - (xds.modify(std::lower_bound(bound, bound + n, l) - bound, std::upper_bound(bound, bound + n, r) - bound - 1, (o) ? (-1) : (1))));
    }

    return 0;
}