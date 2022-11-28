
#include "headerfiles.cpp"


int def_wiresur[6];

vi getbranch_sur(vector<pi> adj[], int n_node, int wire_name, int node_front)
{
    vi branchsur;
    branchsur.pb(wire_name);
    // goes through the adjacency list of node u alone
    // u is node that is definitely a branchout on the right of wire i
    for (auto x = adj[node_front].begin(); x != adj[node_front].end(); x++)
    {
        int v = x->first;            // gate that the branchout is connected to
        int w = x->second;           // wire
        branchsur.push_back(w - 50); // pushing back only wire that connects branch point to gate
    }
    // debug
    // cout<<"getbranchdata done\n";
    // for(int  i = 0; i < branchsur.size(); i++)
    //     cout << branchsur[i] << " " ;
    // cout<<endl;
    return branchsur;
}

void getwire_sur(vector<pi> adj[], int n_node, int wire_name, vi nodetype)
{
    rep(i, 0, 6)
        def_wiresur[i] = -1;
    rep(u, 0, n_node)
    {
        for (auto x = adj[u].begin(); x != adj[u].end(); x++)
        {
            int v = x->first;
            int w = x->second;
            if (w == wire_name)
            {
                // Iterate through all nodes, find wire, check if wire is connected to a gate, save those gates.
                def_wiresur[0] = u;
                def_wiresur[1] = v;
                break;
            }
        } // first two entries of i_gatedata[] are the gates connected to the wire
    }
    int in = 2;
    int pi = 1, po = 1;
    rep(u, 0, n_node)
    {
        for (auto x = adj[u].begin(); x != adj[u].end(); x++)
        {
            int v = x->first;  // Node connected to node u
            int w = x->second; // Wire connecting them

            if (v == def_wiresur[0]) // If node connected to node u is the gate connected to the previous wire
            {
                pi = 0;                            // not primary input
                if (nodetype[def_wiresur[0]] == 0) // if branch point
                {
                    def_wiresur[2] = w - 50;
                    def_wiresur[3] = def_wiresur[2]; // other wire is same, because stem
                }
                else
                {
                    def_wiresur[in] = w - 50; // wire that feeds into the gate
                    in++;                     // if not then find other input
                }
            }

            if (u == def_wiresur[1]) // u is gate that was connected to the output of the wire_name that we had before here
            {
                po = 0;                  // not primary output, because u definitely feeds into a v
                def_wiresur[4] = w - 50; // store wire
            }

            if (v == def_wiresur[1] && w != wire_name)
            {
                po = 0;
                def_wiresur[5] = w - 50; // Other input to the gate, wire_name not primary output because it feeds into a gate
            }
        }
    }
    // debug
    // cout<<"getgatedata done\n";
    // rep(i, 0, 6)
    //     cout<< def_wiresur[i] << " ";
    // cout<<endl;

    // If none of these work, default value is -1 anyway.
    /*
            def_wiresur[0] = gate on left of e
            def_wiresur[1] = gate on right of e
            def_wiresur[2] = input 1 of gate on left of e
            def_wiresur[3] = input 2 of gate on left of e
            def_wiresur[4] = output of gate on right of e
            def_wiresur[5] = input 2 of gate on right of e
        */
}

char tcube_intersec(char w1, char w2)
{
    char out;
    switch (w1)
    {
    case '0':
        switch (w2)
        {
        case '0':
            out = '0';
            break;
        case '1':
            out = 'C';
            break;
        case 'x':
            out = '0';
            break;
        case 'D':
            out = 'C';
            break;
        case 'E':
            out = 'C';
            break;
        case 'N':
            out = 'C';
            break;
        }
        break;

    case '1':
        switch (w2)
        {
        case '0':
            out = 'C';
            break;
        case '1':
            out = '1';
            break;
        case 'x':
            out = '1';
            break;
        case 'D':
            out = 'C';
            break;
        case 'E':
            out = 'C';
            break;
        case 'N':
            out = 'C';
            break;
        }
        break;

    case 'x':
        switch (w2)
        {
        case '0':
            out = '0';
            break;
        case '1':
            out = '1';
            break;
        case 'x':
            out = 'x';
            break;
        case 'D':
            out = 'D';
            break;
        case 'E':
            out = 'E';
            break;
        case 'N':
            out = 'C';
            break;
        }
        break;

    case 'D':
        switch (w2)
        {
        case '0':
            out = 'C';
            break;
        case '1':
            out = 'C';
            break;
        case 'x':
            out = 'D';
            break;
        case 'D':
            out = 'D';
            break;
        case 'E':
            out = 'C';
            break;
        case 'N':
            out = 'C';
            break;
        }
        break;

    case 'E':
        switch (w2)
        {
        case '0':
            out = 'C';
            break;
        case '1':
            out = 'C';
            break;
        case 'x':
            out = 'E';
            break;
        case 'D':
            out = 'C';
            break;
        case 'E':
            out = 'E';
            break;
        case 'N':
            out = 'C';
            break;
        }
        break;

    case 'N':
        switch (w2)
        {
        case '0':
            out = 'C';
            break;
        case '1':
            out = 'C';
            break;
        case 'x':
            out = 'C';
            break;
        case 'D':
            out = 'C';
            break;
        case 'E':
            out = 'C';
            break;
        case 'N':
            out = 'C';
            break;
        }
        break;
    }
    // debug
    return out;
}

vector<pi> dFrontier(vector<vector<char>> tc, vi nodetype, int wire_sur[][6])
{
    vector<pi> front;
    rep(i, 0, tc[tc.size() - 1].size())
    {
        if (tc[tc.size() - 1][i] == 'D' || tc[tc.size() - 1][i] == 'E')                                                                                     // if fault
            if (((wire_sur[i][4] != -1 || wire_sur[i][5] != -1)) && (tc[tc.size() - 1][wire_sur[i][4]] == 'x' && tc[tc.size() - 1][wire_sur[i][5]] == 'x')) // if not PO and has x (is a d frontier)
                front.pb(mp(wire_sur[i][1], i));                                                                                                            // Gate on the right is a D frontier then, add to list
    }
    // debug
    // cout << "dfrontier done\n";
    // rep(i, 0, front.size())
    //     cout << front[i].first << " " << front[i].second << endl;
    return front;
}

vector<pi> jFrontier(vector<vector<char>> tc, vi nodetype, int wire_sur[][6])
{
    vector<pi> front;
    rep(i, 0, tc[tc.size() - 1].size())
    {
        if (tc[tc.size() - 1][i] == '0' || tc[tc.size() - 1][i] == '1')                                                                                   // if input present
            if ((wire_sur[i][2] != -1 || wire_sur[i][3] != -1) && (tc[tc.size() - 1][wire_sur[i][2]] == 'x' && tc[tc.size() - 1][wire_sur[i][3]] == 'x')) // if not PI and has x (is a j frontier)
                front.pb(mp(wire_sur[i][0], i));                                                                                                          // Gate on the left is a J frontier then, add to list
    }
    // debug
    // cout << "jfrontier done\n";
    // rep(i, 0, front.size())
    //     cout << front[i].first << " " << front[i].second << endl;
    return front;
}

vector<char> justifyFront(vector<vector<char>> tc_new, vi nodetype, char prop_dc[8][12][3], int wire_sur[][6])
{
    // J Frontier
    vector<pi> jfront;
    int gate, wire;
    jfront = jFrontier(tc_new, nodetype, wire_sur);
    if (jfront.empty())
    { // No frontier implies primary input
        // debug
        // cout << "No J frontier\n";
        // rep(i, 0, tc_new[tc_new.size() - 1].size())
        //     cout<< tc_new[tc_new.size() - 1][i] << " ";
        // cout<<endl;
        return tc_new[tc_new.size() - 1];
    }

    for (auto it = jfront.begin(); it != jfront.end(); it++)
    {
        gate = it->first;
        wire = it->second;

        // Singular cover
        vector<vector<char>> tmp_sc;
        rep(i, 0, 4)
        {
            vector<char> sc_vector;
            if (tcube_intersec(prop_dc[nodetype[gate]][i][0], tc_new[tc_new.size() - 1][wire_sur[wire][2]]) != 'C' && tcube_intersec(prop_dc[nodetype[gate]][i][1], tc_new[tc_new.size() - 1][wire_sur[wire][3]]) != 'C' && prop_dc[nodetype[gate]][i][2] == tc_new[tc_new.size() - 1][wire])
            {

                sc_vector = {tcube_intersec(prop_dc[nodetype[gate]][i][0], tc_new[tc_new.size() - 1][wire_sur[wire][2]]),
                             tcube_intersec(prop_dc[nodetype[gate]][i][1], tc_new[tc_new.size() - 1][wire_sur[wire][3]]),
                             prop_dc[nodetype[gate]][i][2]};

                tmp_sc.pb(sc_vector);
            }
        }

        if (tmp_sc.empty())
        {
            // debug
            // cout << "No singular cover found\n";
            return {'0'};
        }

        vector<vector<char>> tc_new2;
        vector<char> tc_new3;

        while (!tmp_sc.empty())
        {
            tc_new[tc_new.size() - 1][wire_sur[wire][2]] = tmp_sc[tmp_sc.size() - 1][0];
            tc_new[tc_new.size() - 1][wire_sur[wire][3]] = tmp_sc[tmp_sc.size() - 1][1];
            tc_new[tc_new.size() - 1][wire] = tmp_sc[tmp_sc.size() - 1][2];
            tc_new.pb(tc_new[tc_new.size() - 1]);

            tmp_sc.pop_back();
            tc_new2 = tc_new;

            for (auto it = jfront.begin(); it != jfront.end(); it++)
            {
                int w = it->second;
                if (w != wire)
                    tc_new2[tc_new.size() - 1][w] = 'x';
            }

            tc_new3 = justifyFront(tc_new2, nodetype, prop_dc, wire_sur);

            if (tc_new3.size() == 1)
            {
                if (tc_new.empty())
                    // debug
                    // cout << "justify done tc_new empty\n";
                    return {'0'};
                else
                    tc_new.pop_back();
            }
            else
            {
                vector<char> tc_vector;
                rep(i, 0, tc_new[tc_new.size() - 1].size())
                    tc_vector.pb(tcube_intersec(tc_new[tc_new.size() - 1][i], tc_new3[i]));
                tc_new.pb(tc_vector);
            }
        }
    }
    // debug
    // cout << "justify done\n";
    // rep(i, 0, tc_new[tc_new.size() - 1].size())
    //     cout << tc_new[tc_new.size() - 1][i] << " ";
    // cout << endl;
    return tc_new[tc_new.size() - 1];
}

vector<char> D_algorithm_branch(vector<vector<char>> tc, int nout, vi nodetype, char prop_dc[8][12][3], int wire_sur[][6], vii branch_sur)
{
    vector<pi> dFront;
    dFront = dFrontier(tc, nodetype, wire_sur);
    bool flag = 0;
    if (dFront.empty()) // No d frontier
    {
        rep(i, tc[tc.size() - 1].size() - nout, tc[tc.size() - 1].size()) // Check outputs if fault detected
        {
            if (tc[tc.size() - 1][i] == 'D' || tc[tc.size() - 1][i] == 'E')
                flag = 1; // Error detected
        }
        if (!flag)
            // debug
            // cout << "No D frontier\n";
            return {'0'}; // Error not detected
        else
            // debug
            // cout << "Error detected\n";
            // rep(i, 0, tc[tc.size() - 1].size())
            //     cout << tc[tc.size() - 1][i] << " ";
            // cout << endl;
            return tc[tc.size() - 1];
    }

    // if d frontier not empty
    vector<vector<char>> tc_new;
    tc_new.pb(tc[tc.size() - 1]);
    int gate, wire;
    bool f1 = 0;
    for (auto x = dFront.begin(); x != dFront.end(); x++)
    {
        // Iterate through the dFrontiers, save pdc
        vector<vector<char>> pdc_new;
        gate = x->first;
        wire = x->second;
        rep(i, 8, 12)                                                                                                  // Fault at input dcubes, d drive
            if (prop_dc[nodetype[gate]][i][0] == tc_new[tc_new.size() - 1][wire])                                      // Checking if input matches wire val
            pdc_new.pb({prop_dc[nodetype[gate]][i][0], prop_dc[nodetype[gate]][i][1], prop_dc[nodetype[gate]][i][2]}); // Add to pdc_new

        while (!pdc_new.empty()) // As long as we have d frontiers in the pdc
        {
            tc_new[tc_new.size() - 1][wire] = pdc_new[pdc_new.size() - 1][0]; // Set the wires to the value of the d frontier from pdc set
            tc_new[tc_new.size() - 1][wire_sur[wire][5]] = pdc_new[pdc_new.size() - 1][1];
            tc_new[tc_new.size() - 1][wire_sur[wire][4]] = pdc_new[pdc_new.size() - 1][2];
            pdc_new.pop_back(); // Next d frontier

            // Need to justify based on set values
            // Calling justify
            vector<char> jst = justifyFront(tc_new, nodetype, prop_dc, wire_sur);

            if (jst.size() != 1)
            {
                tc_new.pb(jst);
                f1 = 1;
                break;
            }
        }
        if (f1)
            break;
    }
    if (f1)
    {
        tc[tc.size() - 1] = D_algorithm(tc_new, nout, nodetype, prop_dc, wire_sur, branch_sur);
        tc.pb(tc[tc.size() - 1]);
        // debug
        // cout << "D algorithm branch done\n";
        // rep(i, 0, tc[tc.size() - 1].size())
        //     cout << tc[tc.size() - 1][i] << " ";
        // cout<<endl;
        return tc[tc.size() - 1];
    }
    else
    {
        // debug
        // cout << "D algorithm branch done, end else\n";
        return {'0'};
    }
    // debug
    // cout<<"why are you here\n";
    return {'0'};
}

vector<char> D_algorithm(vector<vector<char>> test_cube, int nout, vi node_type, char prop_dc[8][12][3], int wire_sur[][6], vii branch_sur)
{

    // Obtain D Frontier
    vi b_data;      // Branch data for fault_net
    char assgn;     // Assignment for branches from fault_net
    int branch = 0; // Branch flag

    rep(i, 0, test_cube[test_cube.size() - 1].size())
    { // iterate through last testcube
        if (test_cube[test_cube.size() - 1][i] == 'D' || test_cube[test_cube.size() - 1][i] == 'E')
        { // if fault
            if (node_type[wire_sur[i][1]] == 0)
            { // if branch
                rep(j, 0, branch_sur.size())
                { // iterate through list of wires connected to branch
                    if (branch_sur[j][0] == i)
                    {
                        int x_flag = 1; // default assume all x
                        rep(k, 1, b_data.size())
                        {
                            if (test_cube[test_cube.size() - 1][b_data[k]] != 'x')
                            { // if not x
                                x_flag = 0;
                            }
                        }
                        if (x_flag)
                        {
                            branch = 1;
                            b_data = branch_sur[j];
                            assgn = test_cube[test_cube.size() - 1][b_data[0]]; // assign stem value
                            if (!b_data.empty())
                            {
                                b_data.erase(b_data.begin());
                            }
                        }
                    }
                }
            }
        }
    }
    vector<char> out_tc;

    if (branch)
    {
        bool flag2 = 0;
        while (!b_data.empty())
        {
            test_cube.pb(test_cube[test_cube.size() - 1]);
            test_cube[test_cube.size() - 1][b_data[b_data.size() - 1]] = assgn; // assigning stem value from before in new tc
            b_data.pop_back();

            out_tc = D_algorithm_branch(test_cube, nout, node_type, prop_dc, wire_sur, branch_sur); // calling main method

            if (out_tc.size() != 1)
            {
                test_cube.pb(out_tc);
                flag2 = 1;
                // debug
                // cout << "branch break f2 = 1\n";
                // rep(i, 0, test_cube[test_cube.size() - 1].size())
                //     cout << test_cube[test_cube.size() - 1][i] << " ";
                // cout<<endl;
                return test_cube[test_cube.size() - 1]; // result is returned
            }
            else
            {
                test_cube.pop_back();
            }
        }
        if (!flag2)
        {
            // debug
            // cout << "branch break f2 = 0\n";
            return {'0'};
        }
    }

    else
    {
        // not branch
        out_tc = D_algorithm_branch(test_cube, nout, node_type, prop_dc, wire_sur, branch_sur);
        if (out_tc.size() == 1)
        {
            // debug
            // cout << "not branch break, out size = 1\n";
            return {'0'};
        }
        else
        {
            test_cube.pb(out_tc);
            // debug
            // cout << "not branch break, out size != 1\n";
            // rep(i, 0, test_cube[test_cube.size() - 1].size())
            //     cout << test_cube[test_cube.size() - 1][i] << " ";
            // cout<<endl;
            return test_cube[test_cube.size() - 1];
        }
    }
    // debug
    // cout << "why are you here2\n";
    return {'0'};
}