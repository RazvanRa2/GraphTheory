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
		bfs(1);
	}

 private:
	int n;
	int m;
	int source;
	vector<int> adj[kNmax];

	void read_input() {
		cin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			cin >> x >> y;
			adj[x].push_back(y);  // graf neorientat
			adj[y].push_back(x);
		}
	}

	void bfs(int s) {
		vector<int> distance(n + 1, -1);
        vector<int> parent(n + 1, -1);
        vector<int> color(n + 1, WHITE);
        queue<int> queue;

        queue.push(s);
        color[s] = GREY;
        distance[s] = 0;
        cout << "BFS TRAVERSAL: " << endl;
        while (!queue.empty()) {

            int source = queue.front();
            cout << source << " ";

            for (vector<int>::iterator i = adj[source].begin(); i != adj[source].end(); i++) {
                if (color[*i] == WHITE) {
                    queue.push(*i);
                    parent[*i] = source;
                    color[*i] = GREY;
                    distance[*i] = distance[source] + 1;
                }
            }
            color[source] = BLACK;
            queue.pop();
        }
        cout << endl;

        cout << "DISTANCE FROM SOURCE: " << endl;
        for (int i = 1; i <= n; i++) {
            cout << distance[i] << " ";
        }
        cout << endl;

        cout << "PARENT NODES: " << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << " " << parent[i] << endl;
        }
	}

};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
