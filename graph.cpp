#include <bits/stdc++.h>
using namespace std;

//undirected graph, zero based indexing

void display(vector<int> *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " "; // index signifies vertex i.e. first attribute
        for (auto &elem : arr[i])
        {
            cout << "->" << elem;
        }
        cout << endl;
    }
}

void BFS(vector<int> *arr, int n)
{
    int starting_node;
    cout << "Enter the starting node for BFS traversal\n";
    cin >> starting_node;

    queue<int> q;
    vector<bool> visited(n, false);

    visited[starting_node] = true;

    q.push(starting_node);

    while (!q.empty())
    {
        cout << q.front() << " ";
        for (auto &el : arr[q.front()])
        {
            if (!visited[el])
            {
                q.push(el);
                visited[el] = true;
            }
        }
        q.pop();
    }
}


int main()
{
    int v; // number of vertices 0,1,2...n
    int e; // number of edges
    cout << "enter\n";
    cin >> v >> e;

    vector<int> adj[v];

    for (int i = 0; i < e; i++)
    {
        int w, x;
        cin >> w >> x;
        adj[w].push_back(x);
        adj[x].push_back(w);
    }

    display(adj, v);
    BFS(adj, v);
    return 0;
}
