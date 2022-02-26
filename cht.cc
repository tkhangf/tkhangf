const long long inf = (long long) 1.01e18;
const long double eps = (long double) 1e-9;

struct CHT {
  struct line {
    long long a, b;
    
    line() : a(0), b(0) {}
    line(long long _a, long long _b) : a(_a), b(_b) {}
    
    line operator - (const line &o) const {
      return line(a - o.a, b - o.b);
    }
    
    long long eval(long long x) const {
      return a * x + b;
    }
    
    long double cross(const line &o) const {
      return (long double) a * o.b - (long double) o.a * b;
    }
  };
  
  vector<line> ls;
  
  bool ccw(line a, line b, line c) {
    return (a - b).cross(c - b) <= eps;
  }
  
  void insert(line line) {
    while ((int) ls.size() >= 2 && ccw(ls.end()[-2], ls.end()[-1], line)) {
      ls.pop_back();
    }
    ls.push_back(line);
  }
  
  long long get(long long x) {
    int n = (int) ls.size();
    if (n == 0) return -inf;
    int l = 0, r = n - 1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (mid + 1 < n && ls[mid].eval(x) <= ls[mid + 1].eval(x)) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return ls[l].eval(x);
  }
} cht;
