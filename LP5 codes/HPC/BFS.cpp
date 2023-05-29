#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void bfs(int node)
{
	queue<int> q;
	q.push(node);
	while(!q.empty())
	{
		int curr_node = q.front();
		q.pop();
		if (!visited[curr_node])
		{
			visited[curr_node] = true;
			if (visited[curr_node])
			{
				cout << curr_node << " ";
			}
			#pragma omp parallel for 
			for (int i = 0; i < graph[curr_node].size(); i++)
			{
				int adj_node = graph[curr_node][i];
				if (!visited[adj_node])
				{
					q.push(adj_node);
				}
			}
		}
	}
}


int main()
{
	int n, m, start_node;
	cout << "Enter no. of Node, Edges, and start node : ";
	cin >> n >> m >> start_node;
	cout << "Enter Pair of edges: ";
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		visited[i] = false;
	}

	bfs(start_node);
	cout << endl;
	return 0;
}