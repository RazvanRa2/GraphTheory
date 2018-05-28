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


	vector<vector<int> > get_scc() {
		vector<vector<int> > scc;
        vector<int> found(n + 1, -1);
        vector<int> low_link(n + 1, 0);
        vector<int> in_stack(n + 1, 0);
        stack<int> stack;

        int current_start = 0;
        for (int v = 1; v <= n; v++) {
            if (found[v] == -1) {
                tarjan(v, current_start, found, low_link, stack, in_stack, scc);
            }
        }

		return scc;
	}


    void tarjan(int node, int& current_start, vector<int>& found, vector<int>& low_link,
        stack<int>& stack, vector<int> in_stack, vector<vector<int> >& scc) {
            found[node] = current_start;
            low_link[node] = current_start;

            in_stack[node] = 1;
            stack.push(node);

            current_start++;

            for (int neighbour : adj[node]) {
                if (found[neighbour] == -1) {
                    tarjan(neighbour, current_start, found, low_link, stack, in_stack, scc);
                    low_link[node] = min(low_link[node], low_link[neighbour]);
                } else {
                    if (in_stack[neighbour] == 1) {
                        low_link[node] = min(low_link[node], found[neighbour]);
                    }
                }
            }

            if (low_link[node] == found[node]) {
                int current;
                vector<int> new_scc;

                while(!stack.empty() && current != node) {
                    current = stack.top();
                    stack.pop();
                    new_scc.push_back(current);
                    in_stack[current] = 0;
                }

                scc.push_back(new_scc);
            }
        }

	void print_output(vector<vector<int> > result) {
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
