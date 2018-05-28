#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_scc());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
	vector<int> adjt[kNmax];

	void read_input() {
		cin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			cin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
	}

    void dfs(int source, vector<bool>& visited, vector<int>& topSort) {
        visited[source] = true;

        for (vector<int>::iterator i = adj[source].begin(); i != adj[source].end(); i++) {
            if (!visited[*i]) {
                dfs(*i, visited, topSort);
            }
        }

        topSort.push_back(source);
    }

    void dfs_t(int source, vector<bool>& visited, vector<int>& current_scc) {
        visited[source] = false;
        current_scc.push_back(source);

        for (vector<int>::iterator i = adj[source].begin(); i != adj[source].end(); i++) {
            if (visited[*i]) {
                dfs_t(*i, visited, current_scc);
            }
        }
    }

	vector<vector<int> > get_scc() {
		vector<vector<int> > scc;
        stack<int>stack;
        vector<bool> visited(n + 1, false);

        vector<int> topSort;
        topSort.push_back(-1);

        for (int v = 1; v <= n; v++) {
            if (!visited[v]) {
                dfs(v, visited, topSort);
            }
        }

        for (int i = n; i >= 1; i--) {
            if (visited[topSort[i]]) {
                vector<int> current_scc;
                dfs_t(topSort[i], visited, current_scc);
                scc.push_back(current_scc);
            }
        }

		return scc;
	}

	void print_output(vector<vector<int>> result) {
		cout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				cout << nod << ' ';
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
