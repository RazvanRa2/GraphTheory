#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

	vector<vector<int>> get_scc() {
		vector<vector<int>> scc;

        

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
