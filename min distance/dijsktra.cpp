#include <bits/stdc++.h>

#define NMAX 50010
#define oo (1 << 30)
#define NO_PARENT (-1)

using namespace std;

class Task {
public:
    void solve() {
        read_input();
        dijkstra();
        print_output();
    }

private:
    int n, m;
    int source;

    vector<pair<int, int>> adj[NMAX];

    // min-heap ce contine perechi de tipul: distanta de la source la
    // nodul x, nodul x
    // folosit pentru e extrage la fiecare pas nodul care are costul
    // estimat minim fata de sursa
    priority_queue<pair<int, int>, vector<pair<int, int> >, std::greater<pair<int, int> > > pq;

    vector<int> dist;
    vector<int> parent;

    void read_input() {
        cin >> n >> m;

        dist.resize(n + 1);
        parent.resize(n + 1);

        source = 1;

        for (int i = 1, x, y, c; i <= m; ++i) {
            cin >> x >> y >> c;
            adj[x].push_back({y, c});
        }
    }

    void dijkstra() {
        // ETAPA 1
        for (int i = 1; i <= n; ++i) {
            // presupun ca nu am drum
            dist[i] = oo;
            // deci nici parinte (i inaccesibil)
            parent[i] = NO_PARENT;
        }

        // ETAPA 2
        // parintele lui source este 0 - conventie
        parent[source] = 0;
        // distanta de la source la source e 0
        dist[source] = 0;

        pq.push({dist[source], source});

        // ETAPA 3
        while (!pq.empty()) {
            // extragem nodul care are costul estimat minim fata de sursa
            auto entry = pq.top();
            pq.pop();
            int cost = entry.first;
            int node = entry.second;

            // daca intrarea curenta nu este up-to-date
            if (cost > dist[node]) {
                continue;
            }

            // pentru fiecare vecin, incercam sa relaxam costul de la sursa
            // la el trecand prin nodul node
            for (auto &edge : adj[node]) {
                int neighbour = edge.first;
                int cost_edge = edge.second;

                // daca obtinem un costmai mic trecand prin node
                if (dist[node] + cost_edge < dist[neighbour]) {
                    // salvam noua distanta
                    dist[neighbour] = dist[node] + cost_edge;
                    // noul parinte devine node
                    parent[neighbour] = node;
                    // actualizez costul drumului de la sursa la vecin
                    pq.push({dist[neighbour], neighbour});
                }
            }
        }
  }

    void print_output() {
        for (int i = 1; i <= n; ++i) {
            if (i == source) {
                continue;
            }
            if (dist[i] == oo) {
                cout << "Nu exista drum de la " << source << " la nodul " << i << '\n';
            } else {
                cout << "Distanta minima de la nodul " << source << " la nodul " << i << " este " << dist[i] << endl;
            }
        }
    }
};

int main() {
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
