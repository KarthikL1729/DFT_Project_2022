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


int def_wiresur[6] = {-1, -1, -1, -1, -1, -1};
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

vi getbranch_sur(vector<pi> adj[], int n_node, int node_name, int node_front)
{
    vi branchsur;
    branchsur.pb(node_name);
    for(auto x = adj[u].begin(); adj[u].end(); x++)
    {
        int v = x->first;
        int w = x->second;
        branchsur.push_back(w - 50);
    }
    return branchsur;
}

void getwire_sur(vector<pi> adj[], int n_node, int wire_name, vi nodetype)
{
    rep(u, 0, 6)
        def_wiresur[u] = -1;

    rep(u, 0, n_node)
    {   
        for(auto x = adj[u].begin(); x != adj[u].end(); x++)
        {
            int v = x->first;
            int w = x->second;
            if(w == wire_name)
            {
                def_wiresur[0] = u;
                def_wiresur[1] = v;
                break;
            }
        }
    }
    int in = 2;
    bool pi = 1, po = 1;
    rep(u, 0, n_node)
    {
        for(auto x = adj[u].begin(); x != adj[u].end(); x++)
        {
            int v = x->first;
            int w = x->second;

            if(v == def_wiresur[0])
            {
                pi = 0;
                def_wiresur[in] = w-50;
                if(nodetype[def_wiresur[0]] == 1)
                    def_wiresur[3] = def_wiresur[2];
                else
                    in++;
            }

            if(u == def_wiresur[1])
            {
                po = 0;
                def_wiresur[4] = w-50;
            }

            if(v = def_wiresur[1] && w != wire_name)
            {
                po = 0;
                def_wiresur[5] = w-50;
            }
        }
    }
    //If none of these work, default value is -1 anyway. 
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
        cout<<"Enter the type of node for node" << i << ":\n -2: input\n -1: output\n 0: branching point\n 1: AND\n 2: OR\n 3:NAND\n 4:NOR\n 5:XOR\n 6:XNOR";
        int type;
        cin >> type;
        nodetype.pb(type);
    }
    printCirc(adj, n_node);
    for(int i = 0; i < n_node; ++i)
    {
        cout << "Node " << i << " is of type " << nodetype[i] << endl;
    }
    char prop_dc[7][12][3] = {
                                {{'0','0','0'},{'1','1','1'},{'N','N','N'},{'N','N','N'},{'0','0','E'},{'1','1','D'},{'N','N','N'},{'N','N','N'},{'D','D','D'},{'E','E','E'},{'N','N','N'},{'N','N','N'}},          // branch
                                {{'0','x','0'},{'x','0','0'},{'1','1','1'},{'N','N','N'},{'1','1','D'},{'0','x','E'},{'x','0','E'},{'N','N','N'},{'E','1','E'},{'D','1','D'},{'N','N','N'},{'N','N','N'}},          // and
                                {{'0','0','0'},{'x','1','1'},{'1','x','1'},{'N','N','N'},{'0','0','E'},{'x','1','D'},{'1','x','D'},{'N','N','N'},{'E','0','E'},{'D','0','D'},{'N','N','N'},{'N','N','N'}},          // or
                                {{'0','x','1'},{'x','0','1'},{'1','1','0'},{'N','N','N'},{'1','1','E'},{'0','x','D'},{'x','0','D'},{'N','N','N'},{'E','1','D'},{'D','1','E'},{'N','N','N'},{'N','N','N'}},          // nand
                                {{'0','0','1'},{'x','1','0'},{'1','x','0'},{'N','N','N'},{'0','0','D'},{'x','1','E'},{'1','x','E'},{'N','N','N'},{'E','0','D'},{'D','0','E'},{'N','N','N'},{'N','N','N'}},          // nor
                                {{'0','0','0'},{'0','1','1'},{'1','0','1'},{'1','1','0'},{'0','1','D'},{'1','0','D'},{'0','0','E'},{'1','1','E'},{'E','0','E'},{'D','0','D'},{'D','1','E'},{'E','1','D'}},          // xor
                                {{'0','0','1'},{'0','1','0'},{'1','0','0'},{'1','1','1'},{'0','0','D'},{'1','1','D'},{'0','1','E'},{'1','0','E'},{'E','0','D'},{'D','0','E'},{'D','1','D'},{'E','1','E'}}           //xnor
                             }; // 0 to 3 are no errors, 4 to 7 are error at output, 8 to 11 are error at input AND output

    int fwire;
    char f_states[2] = {'D', 'E'};
    rep(i, 0, 2)
    {   
        int j;
        rep(j, 0, n_edge)
        {
            cout << "Considering s-a-" << i << " for wire " << j << endl;
            fwire = j;
            char f_state = f_states[i];

            vector<vector<char>> test_cube;
            vector<char> temp;
            rep(k, 0, n_edge)
                temp.pb('x');
            test_cube.pb(temp);
            test_cube.pb(test_cube[test_cube.size()-1]);

           int wire_sur[n_edge][6];
           // rep(k, 0, n_edge)
           //     rep(l, 0, 6)
           //         wire_sur[k][l] = 0;

            rep(k, 0, n_edge) 
            {
                getwire_sur(adj, n_node, 50+k, nodetype);
                rep(l, 0, 6)
                    wire_sur[k][l] = def_wiresur[l];
            }
            vii branch_sur;
            rep(k, 0, n_edge)
                if (nodetype[wire_sur[k][i]] == 1)          //is branch
                    branch_sur.pb(getbranch_sur(adj, n_node, k, wire_sur[k][1]));

            test_cube[test_cube.size()-1][fwire] = f_state; // Updating next state with fault from xxxxxx
            test_cube.pb(test_cube[test_cube.size() - 1]);  // New copy
            
            

        }
    }

    return 0;
}