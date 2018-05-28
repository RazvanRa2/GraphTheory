#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		dfs();
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];

	void read_input() {
		cin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			cin >> x >> y;
			adj[x].push_back(y);  // graf orientat
		}
	}

	void dfs() {
        vector<int> color(n + 1, WHITE);

        for (int v = 1; v <= n; v++) {
            if (color[v] == WHITE) {
                bool hasCycle = dfs_util(v, color);

                if (hasCycle) {
                    cout << "Graph has a cycle" << endl;
                    exit(0);
                }
            }
        }
        cout << "Graph is acyclical" << endl;
	}

    bool dfs_util(int source, vector<int>& color) {
        color[source] = GREY;

        for (vector<int>::iterator i = adj[source].begin(); i != adj[source].end(); i++) {
            if (color[*i] == GREY || dfs_util(*i, color)) {
                return true;
            }
        }

        color[source] = BLACK;
        return false;
    }
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
