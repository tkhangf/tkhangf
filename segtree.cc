struct ST {
  struct node {
    int add = 0;
    int opt = 0;
    int open = 0;
    int close = 0;
    
    void apply(int l, int r, char v) {
      open = v == '(';
      close = v == ')';
    }
  };
  
  node unite(const node& a, const node &b) const {
    node res;
    int t = min(a.open, b.close);
    res.opt = a.opt + b.opt + t;
    res.open = a.open + b.open - t;
    res.close = a.close + b.close - t;
    return res;
  }
  
  inline void push(int x, int l, int r) {
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    if (tree[x].add != 0) {
      tree[x + 1].apply(l, y, tree[x].add);
      tree[z].apply(y + 1, r, tree[x].add);
      tree[x].add = 0;
    }
  }
  
  inline void pull(int x, int z) {
    tree[x] = unite(tree[x + 1], tree[z]);
  }
  
  int n;
  vector<node> tree;
  
  void build(int x, int l, int r) {
    if (l == r) {
      return;
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    build(x + 1, l, y);
    build(z, y + 1, r);
    pull(x, z);
  }
  
  template <typename T>
  void build(int x, int l, int r, const vector<T> &a) {
    if (l == r) {
      tree[x].apply(l, r, a[l]);
      return;
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    build(x + 1, l, y, a);
    build(z, y + 1, r, a);
    pull(x, z);
  }
  
  node get(int x, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr) {
      return tree[x];
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    push(x, l, r);
    node res{};
    if (rr <= y) {
      res = get(x + 1, l, y, ll, rr);
    } else {
      if (ll > y) {
        res = get(z, y + 1, r, ll, rr);
      } else {
        res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
      }
    }
    pull(x, z);
    return res;
  }
  
  template <typename... T>
  void modify(int x, int l, int r, int ll, int rr, const T&... v) {
    if (ll <= l && r <= rr) {
      tree[x].apply(l, r, v...);
      return;
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    push(x, l, r);
    if (ll <= y) {
      modify(x + 1, l, y, ll, rr, v...);
    }
    if (rr > y) {
      modify(z, y + 1, r, ll, rr, v...);
    }
    pull(x, z);
  }
  
  ST(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(2 * n  - 1);
    build(0, 0, n - 1);
  }
  
  template <typename T>
  ST(const vector<T> &a) {
    n = (int) a.size();
    assert(n > 0);
    tree.resize(2 * n - 1);
    build(0, 0, n - 1, a);
  }
  
  node get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(0, 0, n - 1, ll, rr);
  }
  
  node get(int p) {
    assert(0 <= p && p <= n - 1);
    return get(0, 0, n - 1, p, p);
  }
  
  template <typename... T>
  void modify(int ll, int rr, const T&... v) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return modify(0, 0, n - 1, ll, rr, v...);
  }
};
