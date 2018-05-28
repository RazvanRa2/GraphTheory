#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		topSort();
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

	void topSort() {
        stack<int> topSortedNodes;
        vector<bool> visited(n + 1, false);
        for (int v = 1; v <= n; v++) {
            if (visited[v] == false) {
                topSort_util(v, visited, topSortedNodes);
            }
        }

        while(!topSortedNodes.empty()) {
            cout << topSortedNodes.top() << " ";
            topSortedNodes.pop();
        }
        cout << endl;
	}

    void topSort_util(int source, vector<bool>& visited, stack<int>& topSortedNodes) {
        visited[source] = true;

        for (vector<int>::iterator i = adj[source].begin(); i != adj[source].end(); i++) {
            if (visited[*i] == false) {
                topSort_util(*i, visited, topSortedNodes);
            }
        }

        topSortedNodes.push(source);
    }
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
