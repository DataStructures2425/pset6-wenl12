#include <vector>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void addMatEdge(vector<vector<int>> &graph, int i, int j){
    graph[i][j] = 1;
}

void printMat(vector<vector<int>> graph){
    for (vector<int> row : graph){
        for (int col : row){
            cout << col << " ";
        }
        cout << endl;
    }
}

bool DFS(vector<vector<int>> &graph, vector<bool> &visited, int a, vector<bool> &rec, int V){
    if (rec[a]) return true;
    rec[a] = true;
    visited[a] = true;
    for (int i = 0; i < V; i++){
        if (graph[a][i] && rec[i]) return true;
        if (!visited[i] && graph[a][i] && DFS(graph, visited, i, rec, V)) return true;
    }
    rec[a] = false;
}

bool isCycle(vector<vector<int>> &graph, vector<bool> &visited, int V){
    vector<bool> rec (V, false);
    for (int i = 0; i < V; i++){
        if (!visited[i] && DFS(graph, visited, i, rec, V)) return true;
    }
    return false;
}

vector<int> v;

vector<int> DFSMat(vector<vector<int>> &graph, vector<bool> &completed, int a, int V){
    if (!completed[a]){
        completed[a] = true;
        v.push_back(a);
        for (int i = 0; i < V; i++){
            if (!completed[i] && graph[i][a]){
                bool legal = true;
                for (int j = 0; j < V; j++){
                    if (graph[i][j] && !completed[j]) legal = false;
                }
                //cout << legal << endl;
                if (legal) DFSMat(graph, completed, i, V);
            }
        }
    }
    return v;
}
/*
    Problem 1 - Course Schedule
*/
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
{
    vector<vector<int>> graph(numCourses, vector<int>(numCourses, 0));
    vector<bool> completed(numCourses, false);
    vector<int> v2;
    v2.push_back(-1);
    if (prerequisites[0].empty()) return {0};
    for (int i = 0; i < prerequisites.size(); i++){
        int a = prerequisites[i][0];
        int b = prerequisites[i][1];
        addMatEdge(graph, a, b);
    }
    int f = prerequisites[0][1];
    int prev = f;
    int num = 0;
    while (true){
        for (int y = 0; y < numCourses; y++){
            if (f == prerequisites[y][0]){
                num = 0;
                f = prerequisites[f][1];
            }
        }
        prev = f;
        num++;
        if (num == 3) break;
    }
    //printMat(graph);
    //cout << "f" << f << endl;
    vector<bool> visited(numCourses, false);
    if (isCycle(graph, visited, numCourses)) return v2;
    v = DFSMat(graph, completed, f, numCourses);
    //cout << v.size() << endl;
    //for (int g : v) cout << "g" << g << endl;
    if (v.size() == numCourses) return v;
    return v2;
}

void turnIntoGraph(vector<vector<int>> &graph, vector<vector<int>> rooms){
    for (int i = 0; i < rooms.size(); i++){
        for (int j = 0; j < rooms[i].size(); j++){
            addMatEdge(graph, i, rooms[i][j]);
        }
    }
}
//dont need open
void DFS2(vector<vector<int>> &graph, vector<bool> &visited, int a, int V, vector<int> &v){
    if (!visited[a]){
        v.push_back(a);
        visited[a] = true;
    }
    for (int i = 0; i < V; i++){
        if (!visited[i] && graph[a][i]) DFS2(graph, visited, i, V, v);
    }
}

/*
    Problem 2 - Keys & Rooms
*/
bool canVisitAllRooms(vector<vector<int>>& rooms) 
{
    int n = rooms.size();
    vector<bool> visited(n, false);
    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<int> v;
    turnIntoGraph(graph, rooms);
    //printMat(graph);
    DFS2(graph, visited, 0, n, v);
    //cout << v.size() << endl;
    if (v.size() == n) return true;
    return false;
}


void printWeighted(vector<vector<vector<int>>> graph){
    for (int i = 0; i < graph.size(); i++){
        cout << i << ": ";
        for (vector<int> p : graph[i]){
            cout << "{" << p[0] << ", " << p[1] << ", " << p[2] << "} ";
        }
    }
}

typedef pair<int, pair<int, int>> vertex;

vector<int> dijkstra(const vector<vector<vertex>> &graph, vector<int> &prev, int source, int k, vector<int> &dist){
    int V = graph.size();
    priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

    dist[source] = 0;
    //cost, node, k
    pq.push({0, make_pair(source, 1)});
    while (!pq.empty()){
        int currentDist = pq.top().first;
        int currentNode = pq.top().second.first;
        int currK = pq.top().second.second;
        pq.pop();

        if (currentDist > dist[currentNode]) continue;
        if (currK <= k + 1){
            for (vertex edge : graph[currentNode]){
                int neighborNode = edge.second.first;
                int weight = edge.first;

                int newDist = currentDist + weight;

                if (newDist < dist[neighborNode]){
                    dist[neighborNode] = newDist;
                    prev[neighborNode] = currentNode;
                    pq.push({newDist, make_pair(neighborNode, currK + 1)});
                }
            }
        }
    }
    return dist;
}

void addEdge(vector<vector<vertex>> &graph, int u, int v, int w){
    graph[u].push_back({w, make_pair(v, 1)});
}

void printWeighted(vector<vector<vertex>> graph){
    for (int i = 0; i < graph.size(); i++){
        cout << i << ": ";
        for (vertex p : graph[i]){
            cout << "{" << p.second.first << ", " << p.first << "} ";
        }
    }
}

const int inf = INT_MAX;

/*
    Problem 3 - Cheapest Flight
*/
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) 
{
    //from, to, price
    if (src == dst) return 0;
    vector<vector<vertex>> graph(n, vector<vertex>());
    vector<int> dist(n, inf);
    vector<int> prev(n);
    for (int i = 0; i < n; i++){
        for (vector<int> j : flights){
            if (j[0] == i){
                addEdge(graph, j[0], j[1], j[2]);
                prev[j[1]] = j[0];
                if (j[1] == dst) dist[j[0]] = j[2];
            }
        }
    }
    //printWeighted(graph);
    cout << endl;
    dist = dijkstra(graph, prev, src, k, dist);
    return dist[dst];
}

typedef vector<int> arrow;

int dijkstra2(const vector<vector<arrow>> &graph, vector<vector<int>>& grid, int maxR, int maxC){
    //cost, row, col
    int V = graph.size();
    priority_queue<arrow, vector<arrow>, greater<arrow>> pq;

    pq.push({0, 0, 0});
    int prevR;
    int prevC;
    while (!pq.empty()){
        int currCost = pq.top()[0];
        int currR = pq.top()[1];
        int currC = pq.top()[2];
        pq.pop();
        if (currR == maxR - 1 && currC == maxC - 1) return currCost;

        int direction = grid[currR][currC];
        //right (1) c + 1
        //left (2) c -1
        //down (3) r + 1
        //up (4) r - 1

        if (direction == 1){
            if (prevR != currR && prevC != currC && currC + 1 < maxC) pq.push({currCost, currR, currC + 1});
            if (currC - 1 >= 0) pq.push({currCost + 1, currR, currC - 1});
            if (currR + 1 < maxR) pq.push({currCost + 1, currR + 1, currC});
            if (currR - 1 >= 0) pq.push({currCost + 1, currR - 1, currC});
        }
        if (direction == 2){
            if (currC + 1 < maxC) pq.push({currCost + 1, currR, currC + 1});
            if (prevR != currR && prevC != currC && currC - 1 >= 0) pq.push({currCost, currR, currC - 1});
            if (currR + 1 < maxR) pq.push({currCost + 1, currR + 1, currC});
            if (currR - 1 >= 0) pq.push({currCost + 1, currR - 1, currC});
        }
        if (direction == 3){
            if (currC + 1 < maxC) pq.push({currCost + 1, currR, currC + 1});
            if (currC - 1 >= 0) pq.push({currCost + 1, currR, currC - 1});
            if (prevR != currR && prevC != currC && currR + 1 < maxR) pq.push({currCost, currR + 1, currC});
            if (currR - 1 >= 0) pq.push({currCost + 1, currR - 1, currC});
        }
        if (direction == 4){
            if (currC + 1 < maxC) pq.push({currCost, currR, currC + 1});
            if (currC - 1 >= 0) pq.push({currCost + 1, currR, currC - 1});
            if (currR + 1 < maxR) pq.push({currCost + 1, currR + 1, currC});
            if (prevR != currR && prevC != currC && currR - 1 >= 0) pq.push({currCost, currR - 1, currC});
        }
        prevR = currR;
        prevC = currC;
    }
}

/*
    Problem 4 - Minimum Cost to Make Path
*/
int minCost(vector<vector<int>>& grid) 
{
    //1 right 2 left 3 down 4 up
    int destR = grid.size();
    int destC = grid[0].size();
    vector<vector<arrow>> g(destR, vector<arrow>(destC));
    //cost, row, col
    int a = dijkstra2(g, grid, destR, destC);
    return a;
}

void addMatEdge2(vector<vector<int>> &graph, int i, int j){
    graph[i][j] = 1;
    graph[j][i] = 1;
}

bool allTrue(vector<bool> v){
    int a = true;
    for (bool j : v){
        if (j == 0) a = false;
    }
    return a;
}

int BFSMat(vector<vector<int>> &graph, int a, int V){
    queue<pair<pair<int,int>, vector<bool>>> q;
    vector<bool> v(V, 0);
    v[a] = true;
    q.push(make_pair(make_pair(0, a), v));
    
    while (!q.empty()){
        int y = q.front().first.first;
        int o = q.front().first.second;
        vector<bool> p = q.front().second;
        q.pop();
        if (allTrue(p)) return y;
        for (int i = 0; i < V; i++){
            if (graph[o][i]){
                bool d = p[i];
                p[i] = true;
                q.push(make_pair(make_pair(y+1, i), p));
                p[i] = d;
            }
        }
    }
}

/*
    Problem 5 - Shortest Path Visting All Nodes
*/
int shortestPathLength(vector<vector<int>>& graph) 
{
    vector<vector<int>> g(graph.size(), vector<int>(graph.size(), 0));
    for (int i = 0; i < graph.size(); i++){
        for (int j = 0; j < graph[i].size(); j++){
            addMatEdge2(g, i, graph[i][j]);
        }
    }
    //printMat(g);
    int ans = inf;
    for (int k = 0; k < graph.size(); k++){
        int l = BFSMat(g, k, graph.size());
        if (l < ans) ans = l;
    }
    return ans;
}