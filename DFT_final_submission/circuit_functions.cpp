#include "headerfiles.cpp"

vector<char> D_algorithm(vector<vector<char>> test_cube, int nout, vi node_type, char prop_dc[8][12][3], int wire_sur[][6], vii branch_sur);

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
            cout << x->first << " ";
            cout << x->second << " ";
            cout << ";";
        }
        cout << endl;
    }
}