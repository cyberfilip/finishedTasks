#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    int nr;
    int h;
    vector<int> ns;
};

bool cmph(const node &a, const node &b) {
    return a.h < b.h;

}

vector<node> g;

int wysokosci[100001];

void create_edge(int src, int dest) {
    node& x = g[src - 1];
    node& y = g[dest - 1];
    x.ns.push_back(dest);
    y.ns.push_back(src);
}

int trasy[100001];

int find_set(int x) { //strona 507
    if (x != trasy[x]) {
        trasy[x] = find_set(trasy[x]);
    }
    return trasy[x];
}

void link (int x, int y) {
    trasy[x] = y;
}

void make_union(int x, int y) {
    link(find_set(x), find_set(y));
}

int main() {
    ios::sync_with_stdio(false);
    int n, m; //n - ilosc punktow na mapie; m - ilosc szlakow
    cin >> n >> m;
    g.resize(n);

    for (int i = 0; i < n; i++) {
        node& x = g[i];
        x.nr = i + 1;
        cin >> x.h;
        wysokosci[x.nr] = x.h;
    }

    for (int i = 1; i <= m; i++) {
        int src, dest;
        cin >> src >> dest;
        create_edge(src, dest);
    }

    sort(g.begin(), g.end(), cmph);

    for (int i = 1; i <= n; i++) {
        trasy[i] = i;
    }
//    int maxi
    for (auto& x : g) {
        for (auto& y : x.ns) {
            if (x.h >= wysokosci[y]) {
                //cout << "unia: " << x.nr << " " << y << endl;
                make_union(x.nr, y);
            }
        }
        if (find_set(1) == find_set(n)) {
            cout << x.h;
            return 0;
        }
    }

//    for (int i = 0; i < n; i++) {
//        node& x = g[i];
//        cout << "wierzhoclek numer: " << x.nr << " wysokosc: " << x.h << " ilosc sasiadow: " << x.ns.size() << endl;
//    }
}
