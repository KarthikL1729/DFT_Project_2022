#include "headerfiles.cpp"
#include "circuit_functions.cpp"
#include "d_algo_functions.cpp"

int main(void)
{
    file_read 
    int n_node;
    cout << "Enter the number of nodes (Branching points, gates, inputs, outputs): \n";
    cin >> n_node;
    int n_edge;
    cout << "Enter the number of edges (Wires): \n";
    cin >> n_edge;
    vector<pi> adj[n_node];
    vi nodetype;
    cout << "Enter connections in netlist format (node1 node2 wirenum): \n";
    rep(i, 0, n_edge)
    {
        int u, v, wire;
        cin >> u >> v >> wire;
        addWire(adj, u, v, wire);
    }
    cout << "Enter the type of node: \n -2: output\n -1: input\n 0: branching point\n 1: AND\n 2: OR\n 3:NAND\n 4:NOR\n 5:XOR\n 6:XNOR\n 7: NOT\n";
    rep(i, 0, n_node)
    {
        int type;
        cin >> type;
        nodetype.pb(type);
    }
    printCirc(adj, n_node);
    for (int i = 0; i < n_node; ++i)
    {
        cout << "Node " << i << " is of type " << nodetype[i] << endl;
    }
    char prop_dc[8][12][3] = {
        {{'0', '0', '0'}, {'1', '1', '1'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}, {'0', '0', 'E'}, {'1', '1', 'D'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}, {'D', 'D', 'D'}, {'E', 'E', 'E'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}}, // branch
        {{'0', 'x', '0'}, {'x', '0', '0'}, {'1', '1', '1'}, {'N', 'N', 'N'}, {'1', '1', 'D'}, {'0', 'x', 'E'}, {'x', '0', 'E'}, {'N', 'N', 'N'}, {'E', '1', 'E'}, {'D', '1', 'D'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}}, // and
        {{'0', '0', '0'}, {'x', '1', '1'}, {'1', 'x', '1'}, {'N', 'N', 'N'}, {'0', '0', 'E'}, {'x', '1', 'D'}, {'1', 'x', 'D'}, {'N', 'N', 'N'}, {'E', '0', 'E'}, {'D', '0', 'D'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}}, // or
        {{'0', 'x', '1'}, {'x', '0', '1'}, {'1', '1', '0'}, {'N', 'N', 'N'}, {'1', '1', 'E'}, {'0', 'x', 'D'}, {'x', '0', 'D'}, {'N', 'N', 'N'}, {'E', '1', 'D'}, {'D', '1', 'E'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}}, // nand
        {{'0', '0', '1'}, {'x', '1', '0'}, {'1', 'x', '0'}, {'N', 'N', 'N'}, {'0', '0', 'D'}, {'x', '1', 'E'}, {'1', 'x', 'E'}, {'N', 'N', 'N'}, {'E', '0', 'D'}, {'D', '0', 'E'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}}, // nor
        {{'0', '0', '0'}, {'0', '1', '1'}, {'1', '0', '1'}, {'1', '1', '0'}, {'0', '1', 'D'}, {'1', '0', 'D'}, {'0', '0', 'E'}, {'1', '1', 'E'}, {'E', '0', 'E'}, {'D', '0', 'D'}, {'D', '1', 'E'}, {'E', '1', 'D'}}, // xor
        {{'0', '0', '1'}, {'0', '1', '0'}, {'1', '0', '0'}, {'1', '1', '1'}, {'0', '0', 'D'}, {'1', '1', 'D'}, {'0', '1', 'E'}, {'1', '0', 'E'}, {'E', '0', 'D'}, {'D', '0', 'E'}, {'D', '1', 'D'}, {'E', '1', 'E'}}, // xnor
        {{'0', 'N', '1'}, {'1', 'N', '0'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}, {'0', 'N', 'D'}, {'1', 'N', 'E'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}, {'D', 'N', 'E'}, {'E', 'N', 'D'}, {'N', 'N', 'N'}, {'N', 'N', 'N'}}  // not
    };                                                                                                                                                                                                                // 0 to 3 are no errors, 4 to 7 are error at output, 8 to 11 are error at input AND output

    int fwire;
    char f_state;
    char f_states[2] = {'D', 'E'};
    rep(i, 0, 2)
    {
        rep(j, 0, n_edge)
        {
            // int i = 0, j = 0;
            cout << "Considering s-a-" << i << " for wire " << j + 50 << endl;
            fwire = j;
            f_state = f_states[i];

            vector<vector<char>> test_cube;
            vector<char> temp;
            rep(k, 0, n_edge)
                temp.pb('x');
            test_cube.pb(temp);
            test_cube.pb(test_cube[test_cube.size() - 1]);

            int wire_sur[n_edge][6];
            rep(k, 0, n_edge)
                rep(l, 0, 6)
                    wire_sur[k][l] = 0;

            rep(k, 0, n_edge)
            {
                getwire_sur(adj, n_node, k + 50, nodetype);
                rep(l, 0, 6)
                    wire_sur[k][l] = def_wiresur[l];
            }
            vii branch_sur;
            rep(k, 0, n_edge) if (nodetype[wire_sur[k][1]] == 0) // is branch
                branch_sur.pb(getbranch_sur(adj, n_node, k, wire_sur[k][1]));

            test_cube[test_cube.size() - 1][fwire] = f_state; // Updating next state with fault from xxxxxx
            test_cube.pb(test_cube[test_cube.size() - 1]);    // New copy

            rep(k, 4, 8)
            {
                if (prop_dc[nodetype[wire_sur[fwire][0]]][k][2] == test_cube[test_cube.size() - 1][fwire])
                {
                    test_cube[test_cube.size() - 1][wire_sur[fwire][2]] = prop_dc[nodetype[wire_sur[fwire][0]]][k][0];
                    test_cube[test_cube.size() - 1][wire_sur[fwire][3]] = prop_dc[nodetype[wire_sur[fwire][0]]][k][1];
                }
            }
            test_cube.pb(test_cube[test_cube.size() - 1]);

            // D Algorithm starts here
            int nout, nin;
            nout = 0;
            nin = 0;
            rep(k, 0, n_node)
            {
                if (nodetype[k] == -2)
                    nout++;
                if (nodetype[k] == -1)
                    nin++;
            }

            vector<char> out_states(n_edge);
            out_states = D_algorithm(test_cube, nout, nodetype, prop_dc, wire_sur, branch_sur);
            if (out_states.size() == 1)
            {
                cout << "Fault Untestable" << endl;
            }
            else
            {
                test_cube[test_cube.size() - 1] = out_states;
                cout << "Test Complete" << endl;
                cout << "Test Vector: ";
                rep(i, 0, nin)
                {

                    if (test_cube[test_cube.size() - 1][i] == 'D')
                        cout << "1 ";
                    else if (test_cube[test_cube.size() - 1][i] == 'E')
                        cout << "0 ";
                    else
                        cout << test_cube[test_cube.size() - 1][i] << " ";
                }

                cout << endl;

                cout << "Path (Format: Edge-[Node]): ";
                rep(i, 0, test_cube[test_cube.size() - 1].size())
                {
                    if (test_cube[test_cube.size() - 1][i] == 'D' || test_cube[test_cube.size() - 1][i] == 'E')
                        cout << i + 50 << "-[" << wire_sur[i][1] << "]-";
                    // else if(test_cube[test_cube.size()-1][i] == 'E')
                    //     cout<<i+50<<"-["<<wire_sur[i][1]<<"]";
                }
            }

            cout << endl;
        }
    }

    return 0;
}