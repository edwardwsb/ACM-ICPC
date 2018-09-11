struct MinCost {
    struct Edge {
        int s, t, cap, cost, net;
        Edge() {}
        Edge(int s, int t, int cap, int cost, int net) : s(s), t(t), cap(cap), cost(cost), net(net) {}
    } e[M<<1];
    ll dis[N];
    queue <int> Q;
    int n, no, pre[N], vis[N], head[N];
    void init(int _n) {      // 最大点编号 + 1
        n = _n, no = 0;
        memset(head, -1, sizeof(head[0]) * n);
    }
    void addEdge(int s, int t, int cap, int cost) {
        e[no] = Edge(s, t, cap, cost, head[s]), head[s] = no++;
        e[no] = Edge(t, s, 0, -cost, head[t]), head[t] = no++;
    }
    bool bfs(int S, int T) {
        rep(i, 0, n) pre[i] = -1, dis[i] = LINF, vis[i] = false;
        dis[S] = 0, vis[S] = true, Q.push(S);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int i = head[u]; ~i; i = e[i].net) {
                int v = e[i].t;
                if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost) {
                    pre[v] = i, dis[v] = dis[u] + e[i].cost;
                    if (!vis[v]) vis[v] = true, Q.push(v);
                }
            }
            vis[u] = false;
        }
        return dis[T] != LINF;
    }
    pair<ll, ll> solve(int S, int T) {
        ll maxflow = 0, mincost = 0;
        while (bfs(S, T)) {
            ll flow = LINF;
            for (int i = pre[T]; ~i; i = pre[e[i].s]) flow = min(flow, (ll)e[i].cap);
            for (int i = pre[T]; ~i; i = pre[e[i].s]) e[i].cap -= flow, e[i^1].cap += flow;
            maxflow += flow, mincost += flow * dis[T];
        }
        return mp(maxflow, mincost);
    }
};

================================================== Problem Set ==================================================

// luogu P4016
// 题意：环形排列 n 个仓库，搬运最少的货物使得 n 个仓库存量相等
// 题解：算平均数，富余的仓库建源点到自己的边，不足的仓库建自己到汇点的边，流量皆为富余或不足量，再在仓库之间建边，跑最小费用最大流
int Solve() {
    obj.init(n+2);
    int tot = 0;
    rep(i, 1, n+1) {
        scanf("%d", a+i);
        tot += a[i];
    }
    int ave = tot / n, S = 0, T = n + 1;
    rep(i, 1, n+1) {
        if (a[i] > ave) obj.addEdge(S, i, a[i] - ave, 0);
        else obj.addEdge(i, T, ave - a[i], 0);
    }
    rep(i, 1, n+1) {
        obj.addEdge(i, (i + 1) % n ? : n, INF, 1);
        obj.addEdge(i, (i - 1) % n ? : n, INF, 1);
    }
    return printf("%lld\n", obj.solve(S, T).se);
}
