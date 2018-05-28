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
    int time = 0;
	vector<int> adj[kNmax];

	void read_input() {
		cin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			cin >> x >> y;
			adj[x].push_back(y);  // graf neorientat
			adj[y].push_back(x);
		}
	}

	void dfs() {
        vector<int> parent(n + 1, -1);
        vector<int> color(n + 1, WHITE);
        vector<int> start_time(n + 1, 0);
        vector<int> end_time(n + 1, 0);

        for (int v = 1; v <= n; v++) {
            if (color[v] == WHITE) {
                dfs_util(v, color, parent, start_time, end_time);
            }
        }
        cout << endl;

        cout << "PARENT NODES: " << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << " " << parent[i] << endl;
        }

        cout << "START - END TIME: " << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << " " << start_time[i] << " " << end_time[i] << endl;
        }
	}

    void dfs_util(int source, vector<int>& color, vector<int>& parent,
        vector<int>& start_time, vector<int>& end_time) {

        cout << source << " ";

        start_time[source] = time++;
        color[source] = GREY;

        for (vector<int>::iterator i = adj[source].begin(); i != adj[source].end(); i++) {
            if (color[*i] == WHITE) {
                parent[*i] = source;
                dfs_util(*i, color, parent, start_time, end_time);
            }
        }

        color[source] = BLACK;
        end_time[source] = time++;
    }
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
