int main()
{

    int fault_net;
    char fault;
    char faults[2] = {'D', 'E'};

    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < edge; i++)
        {
            cout << "s-a-" << j << " Fault at w" << i + 20 << endl;
            fault = faults[j];
            fault_net = i;
            // Initialization
            vector<vector<char>> tc;
            for (int i = 0; i < 1; i++)
            {
                vector<char> v;
                for (int j = 0; j < edge; j++)
                {
                    v.push_back('x');
                }
                tc.push_back(v);
            }
            tc.push_back(tc[tc.size() - 1]);

            // Fault assignment
            int gatedata[edge][6];
            for (int i = 0; i < edge; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    gatedata[i][j] = 0;
                }
            }

            for (int i = 0; i < edge; i++)
            {
                getgatedata(adj, V, i, gate_type);
                for (int j = 0; j < 6; j++)
                {
                    gatedata[i][j] = i_gatedata[j];
                }
            }

            vector<vector<int>> branchdata;
            for (int e = 0; e < edge; e++)
            {
                if (gate_type[gatedata[e][1]] == 7)
                {
                    // if branchout
                    branchdata.push_back(getbranchdata(adj, V, e, gatedata[e][1]));
                }
            }
            tc[tc.size() - 1][fault_net] = fault;
            tc.push_back(tc[tc.size() - 1]);

            // PDCF

            for (int i = 4; i < 8; i++)
            {
                if (dcubes[gate_type[gatedata[fault_net][0]]][i][2] == tc[tc.size() - 1][fault_net])
                {                                                                                                // Type of gate on left of e has faulty output that is same as dcube of that gate
                    tc[tc.size() - 1][gatedata[fault_net][2]] = dcubes[gate_type[gatedata[fault_net][0]]][i][0]; // Then initialise inputs to those constant values.
                    tc[tc.size() - 1][gatedata[fault_net][3]] = dcubes[gate_type[gatedata[fault_net][0]]][i][1];
                }
            }
            tc.push_back(tc[tc.size() - 1]);

            // D algo
            int num_out = 0;
            for (int i = 0; i < V; i++)
            {
                if (gate_type[i] == -2)
                {
                    num_out++;
                }
            }
            int num_in = 0;
            for (int j = 0; j < V; j++)
            {
                if (gate_type[j] == -1)
                {
                    num_in++;
                }
            }

            vector<char> out(edge);
            out = dalgo(tc, num_out, gate_type, dcubes, gatedata, branchdata);
            if (out.size() == 1)
            {
                cout << "FAULT UNTESTABLE" << endl;
            }
            else
            {

                tc[tc.size() - 1] = out;
                cout << "TEST COMPLETED" << endl;
                cout << "Test Vector"
                     << ": ";
                for (int i = 0; i < num_in; i++)
                {
                    if (tc[tc.size() - 1][i] == 'D')
                    {
                        cout << 1 << " ";
                    }
                    else if (tc[tc.size() - 1][i] == 'E')
                    {
                        cout << 0 << " ";
                    }
                    else
                    {
                        cout << tc[tc.size() - 1][i] << " ";
                    }
                }
                cout << "" << endl;
                cout << "PATH (EdgeNumber-[GateNumber]): ";
                for (int i = 0; i < tc[tc.size() - 1].size(); i++)
                {
                    if (tc[tc.size() - 1][i] == 'D' || tc[tc.size() - 1][i] == 'E')
                    {
                        cout << i + 20 << "-[" << gatedata[i][1] << "]-";
                    }
                }
            }

            cout << "" << endl;
        }
    }

    return 0;
}
