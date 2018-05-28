#include <bits/stdc++.h>

#define NMAX 100010
#define edge pair<int, int>

using namespace std;

class Task {
public:
  void solve() {
    read_input();
    tarjan();
    print_output();
  }

private:
  int n, m;
  vector<int> adj[NMAX];
  vector<vector<int>> bcc;
  stack<edge> sc;
  vector<int> found;
  vector<int> low_link;
  vector<int> cut_vertex;
  vector<int> is_cv;
  vector<edge> critical_edges;
  vector<int> parent;

  void read_input() {
    cin >> n >> m;

    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);
    parent = vector<int>(n + 1, 0);
    is_cv = vector<int>(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
      int x, y;
      cin >> x >> y;

      adj[x].push_back(y);
      adj[y].push_back(x);
    }
  }


  void tarjan() {
    int current_start = 0;

    for (int i = 1; i <= n; ++i) {
      if (found[i] == -1) {
        parent[i] = 0;
        dfs(i, current_start);
      }
    }
  }

  void dfs(int node, int &current_start) {
    ++current_start;

    found[node] = current_start;
    low_link[node] = current_start;

    int children = 0;

    for (auto &vecin : adj[node]) {
      if (found[vecin] == -1) { // deci il pot vizita
        parent[vecin] = node;

        ++children;

        sc.push(edge(node, vecin));

        dfs(vecin, current_start);

        low_link[node] = std::min(low_link[node], low_link[vecin]);

        if (low_link[vecin] >= found[node]) {
          if (parent[node] != 0) {
            if (!is_cv[node]) {
              is_cv[node] = 1;
              cut_vertex.push_back(node);
            }
          }

          get_bcc(edge(node, vecin));
        }

        if (low_link[vecin] > found[node]) {
          critical_edges.push_back(edge(node, vecin));
        }
      } else {
        if (vecin != parent[node]) {
          low_link[node] = std::min(low_link[node], found[vecin]);
        }
      }
    }

    if (parent[node] == 0 && children >= 2) {
      if (!is_cv[node]) {
        is_cv[node] = 1;
        cut_vertex.push_back(node);
      }
    }
  }

  void get_bcc(edge target_edge) {
    vector<int> current_bcc;

    edge current_edge = edge(-1, -1);

    while (current_edge != target_edge) {
      current_edge = sc.top();
      sc.pop();

      current_bcc.push_back(current_edge.first);
      current_bcc.push_back(current_edge.second);
    }

    sort(current_bcc.begin(), current_bcc.end());
    auto it = unique(current_bcc.begin(), current_bcc.end());
    current_bcc.erase(it, current_bcc.end());

    bcc.push_back(current_bcc);
  }

  void print_output() {
    if (cut_vertex.empty()) {
      cout << "Graful nu contine puncte de articulatie\n";
    } else {
      cout << "Punctele de articulatie ale grafului sunt:\n";
      for (auto &node : cut_vertex) {
        cout << node << ' ';
      }
      cout << '\n';
    }

    if (critical_edges.empty()) {
      cout << "Graful nu contine muchii critice\n";
    } else {
      cout << "Muhciile critice ale grafului sunt:\n";
      for (auto &E : critical_edges) {
        cout << '(' << E.first << ", " << E.second << ") ";
      }
      cout << '\n';
    }

    int sol = bcc.size();
    cout << "Graful are " << sol << " componente biconexe\n";
    for (int i = 0; i < sol; ++i) {
      cout << "Componenta biconexa [" << i + 1 << "]: ";
      for (auto &node : bcc[i]) {
        cout << node << " ";
      }
      cout << '\n';
    }
  }
};

int main() {
  Task *task = new Task();
  task->solve();
  delete task;

  return 0;
}
