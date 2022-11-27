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
#define godspeed cin.tie(0), cout.tie(0)->sync_with_stdio(0)
 
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
        cout<<"Enter the type of node for node" << i << ":\n 0: input/output\n 1: branching point\n 2: AND\n 3: OR\n 4:NAND\n 5:NOR\n 6:XOR\n";
        int type;
        cin >> type;
        nodetype.pb(type);
    }
    printCirc(adj, n_node);
    for(int i = 0; i < n_node; ++i)
    {
        cout << "Node " << i << " is of type " << nodetype[i] << endl;
    }
    
    return 0;
}