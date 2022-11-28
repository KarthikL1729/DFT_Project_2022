int main(void)
{
    int fwire;
    char f_state;
    char f_states[2] = {'D', 'E'};
    rep(i, 0, 2)
    {
        rep(j, 0, n_edge)
        {
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
                getwire_sur(adj, n_node, k, nodetype);
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
                        cout << i + 50 << "-[" << wire_sur[i][1] << "]";
                    // else if(test_cube[test_cube.size()-1][i] == 'E')
                    //     cout<<i+50<<"-["<<wire_sur[i][1]<<"]";
                }
            }

            cout << endl;
        }
    }

    return 0;
}