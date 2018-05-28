#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		bfs();
	}

 private:
	int n;
	int m;
	int source;
	vector<int> adj[kNmax];
    vector<int> in_degree;

	void read_input() {
		cin >> n >> m;
        in_degree = vector<int>(n + 1, 0);
    	for (int i = 1, x, y; i <= m; i++) {
			cin >> x >> y;
			adj[x].push_back(y);
            in_degree[y]++;
		}
	}

	void bfs() {
        queue<int> queue;
        vector<int> topSort;

        for (int v = 1; v <=n; v++) {
            if (in_degree[v] == 0) {
                queue.push(v);
            }
        }

        while (!queue.empty()) {
            int source = queue.front();
            queue.pop();
            topSort.push_back(source);

            for (auto &v : adj[source]) {
                in_degree[v]--;

                if (in_degree[v] == 0) {
                    queue.push(v);
                }
            }
        }
        for (int i = 0; i < topSort.size(); i++) {
            cout << topSort[i] <<  " ";
        }
        cout << endl;
    }
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
