#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<vi> vii;
 
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define file_read	\
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define rep(i, a, n) for (ll i = a; i < n; ++i)
#define brep(i, a, n) for (ll i = n - 1; i >= a; --i)
 
bool sortbysec(const pair<int, int> &a,
        const pair<int, int> &b)
{
    return a.second < b.second;
}

void addWire(vector<pi> wire[], int u, int v, int w_name)
{
    wire[u].pb(mp(v, w_name));
} 

void printCirc(vector<pi> wire[], int n_node)
{
    rep(i, 0, n_node)
    {
        cout << i << " -> ";
        for (auto x = wire[i].begin(); x != wire[i].end(); ++x)
        {
            cout << x->first << " ";;
            cout << x->second << " ";
            cout << ";";
        }
        cout << endl;
    }
}

int main(void){
    file_read
    int n_node;
    cout << "Enter the number of nodes (Branching points, gates, inputs, outputs): \n";
    cin >> n_node;
    int n_edge;
    cout << "Enter the number of edges (Wires): \n";
    cin >> n_edge;
    vector<pi> adj[n_node];
    vi nodetype;
    rep(i, 0, n_edge)
    {   
        cout<<"Enter first connection in netlist format (node1 node2 wirenum): \n";
        int u, v, wt;
        cin >> u >> v >> wt;
        addWire(adj, u, v, wt);
    } 
    rep(i, 0, n_node)
    {   
        cout<<"Enter the type of node for node" << i << ":\n 0: input/output\n 1: branching point\n 2: AND\n 3: OR\n 4:NAND\n 5:NOR\n 6:XOR\n 7:XNOR";
        int type;
        cin >> type;
        nodetype.pb(type);
    }
    printCirc(adj, n_node);
    for(int i = 0; i < n_node; ++i)
    {
        cout << "Node " << i << " is of type " << nodetype[i] << endl;
    }
    char prop_dc[7][16][3] = {{{'1', '1', '1'},  {'1', 'D', '1'}, {'1', '1', 'D'}, {'0', 'E', '0'}, {'0', '0', 'E'}, {'0', '0', '0'}, {'E', 'E', 'E'}, {'D', 'D', 'D'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}}, 
                              {{'1', '1', '1'},  {'x', '0', '0'}, {'0', 'x', '0'}, {'1', 'D', 'D'}, {'D', '1', 'D'}, {'1', '1', 'D'}, {'0', 'x', 'E'}, {'x', '0', 'E'}, {'1', 'D', 'D'}, {'D', '1', 'D'}, {'E', '1', 'E'}, {'1', 'E', 'E'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}},
                              {{'1', '1', '1'},  {'x', '1', '1'}, {'1', 'x', '1'}, {'0', 'D', 'D'}, {'D', '0', 'D'}, {'0', '0', 'E'}, {'1', 'x', 'D'}, {'x', '1', 'D'}, {'0', 'E', 'E'}, {'E', '0', 'E'}, {'D', '0', 'D'}, {'0', 'D', 'D'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}},
                              {{'1', '1', '0'},  {'x', '0', '1'}, {'0', 'x', '1'}, {'1', 'D', 'E'}, {'D', '1', 'E'}, {'1', '1', 'E'}, {'0', 'x', 'D'}, {'x', '0', 'D'}, {'1', 'D', 'E'}, {'D', '1', 'E'}, {'E', '1', 'D'}, {'1', 'E', 'D'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}},
                              {{'1', '1', '0'},  {'x', '1', '0'}, {'1', 'x', '0'}, {'0', 'D', 'E'}, {'D', '0', 'E'}, {'0', '0', 'D'}, {'1', 'x', 'E'}, {'x', '1', 'E'}, {'0', 'E', 'D'}, {'E', '0', 'D'}, {'D', '0', 'E'}, {'0', 'D', 'E'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}, {'x', 'x', 'x'}},
                              {{'1', '1', '0'},  {'1', '0', '1'}, {'0', '1', '1'}, {'0', '0', '0'}, {'1', 'D', 'E'}, {'D', '1', 'E'}, {'1', '1', 'E'}, {'0', '0', 'E'}, {'0', '1', 'D'}, {'1', '0', 'D'}, {'0', 'D', 'D'}, {'D', '0', 'D'}, {'E', '1', 'D'}, {'1', 'E', 'D'}, {'0', 'E', 'E'}, {'E', '0', 'E'}}, 
                              {{'1', '1', '1'},  {'1', '0', '0'}, {'0', '1', '0'}, {'0', '0', '1'}, {'1', 'D', 'D'}, {'D', '1', 'D'}, {'1', '1', 'D'}, {'0', '0', 'D'}, {'0', '1', 'E'}, {'1', '0', 'E'}, {'0', 'D', 'E'}, {'D', '0', 'E'}, {'E', '1', 'E'}, {'1', 'E', 'E'}, {'0', 'E', 'D'}, {'E', '0', 'D'}} 
                             };
    return 0;
}