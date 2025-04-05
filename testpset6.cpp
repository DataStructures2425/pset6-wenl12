#include "problems.h"
using namespace std;

int main()
{
    /*
        Test your code here! You need at least 5 cases (five different graphs)
        for each solution you implement. Try to make the cases as different
        as you can to ensure maximum coverage. Only one example from the pdf
        handout will count towards your five. 
    */
    cout << "course schedule:" << endl;
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 2},{2, 0}, {3, 1}, {2, 3}};
    vector<int> v = findOrder(numCourses, prerequisites);
    for (int i : v){
        cout << i << " ";
    }
    cout << endl;
    numCourses = 1;
    prerequisites = {{}};
    v = findOrder(numCourses, prerequisites);
    for (int j : v){
        cout << j << " ";
    }
    cout << endl;
    numCourses = 3;
    prerequisites = {{1, 2},{2, 0}};
    v = findOrder(numCourses, prerequisites);
    for (int j : v){
        cout << j << " ";
    }
    cout << endl;
    numCourses = 4;
    prerequisites = {{1, 1},{2, 3}, {3, 1}, {3, 0}};
    v = findOrder(numCourses, prerequisites);
    for (int j : v){
        cout << j << " ";
    }
    cout << endl;
    numCourses = 4;
    prerequisites = {{1, 0},{2, 0}, {3, 0}, {3, 2}};
    v = findOrder(numCourses, prerequisites);
    for (int j : v){
        cout << j << " ";
    }
    
    cout << endl << endl << "rooms:" << endl;
    vector<vector<int>> rooms = {{1, 3},{3, 0, 1}, {2}, {0}};
    cout << canVisitAllRooms(rooms) << endl;
    rooms = {{}};
    cout << canVisitAllRooms(rooms) << endl;
    rooms = {{3}, {2}, {1}, {1}};
    cout << canVisitAllRooms(rooms) << endl;
    rooms = {{2}, {1}, {1}};
    cout << canVisitAllRooms(rooms) << endl;
    rooms = {{1}, {1}, {2}, {}};
    cout << canVisitAllRooms(rooms) << endl;

    cout << endl << "cheapest flight:" << endl;
    int n = 4;
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    int src = 0;
    int dst = 3;
    int k = 1;
    cout << findCheapestPrice(n, flights, src, dst, k);
    n = 4;
    flights = {{0, 3, 200}, {1, 2, 200}, {0, 2, 100}, {1, 2, 600}, {0, 1, 200}};
    src = 0;
    dst = 2;
    k = 3;
    cout << findCheapestPrice(n, flights, src, dst, k);
    n = 4;
    flights = {{0, 1, 700}, {0, 2, 100}, {0, 3, 100}, {3, 1, 300}, {2, 3, 200}};
    src = 0;
    dst = 1;
    k = 4;
    cout << findCheapestPrice(n, flights, src, dst, k);
    n = 4;
    flights = {{0, 2, 100}, {1, 2, 300}, {2, 3, 100}, {0, 3, 600}, {3, 1, 500}};
    src = 2;
    dst = 1;
    k = 2;
    cout << findCheapestPrice(n, flights, src, dst, k);
    n = 4;
    flights = {{0, 1, 100}};
    src = 0;
    dst = 1;
    k = 1;
    cout << findCheapestPrice(n, flights, src, dst, k);

    cout << endl << endl << "arrow grid thing:" << endl;
    vector<vector<int>> grid = {{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    cout << minCost(grid) << endl;
    grid = {{1, 3, 1}, {3, 3, 2}, {1, 1, 1}};
    cout << minCost(grid) << endl;
    grid = {{3, 1, 3}, {1, 3, 2}, {1, 1, 4}};
    cout << minCost(grid) << endl;
    grid = {{1, 1}, {3, 2}};
    cout << minCost(grid) << endl;
    grid = {{1, 2, 3}, {3, 2, 1}, {1, 2, 3}};
    cout << minCost(grid) << endl;

    cout << endl << "shortest path with all nodes: " << endl;
    vector<vector<int>> g = {{1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2}};
    cout << shortestPathLength(g) << endl;
    g = {{1, 2}, {2, 3}, {0, 1}, {1}};
    cout << shortestPathLength(g) << endl;
    g = {{1}, {0, 2}, {1}};
    cout << shortestPathLength(g) << endl;
    g = {{1, 2, 3, 4}, {0, 2}, {0, 1}, {0}, {0}};
    cout << shortestPathLength(g) << endl;
    g = {{3, 1}, {0, 2}, {1}, {0}};
    cout << shortestPathLength(g) << endl;
}