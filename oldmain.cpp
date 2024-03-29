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
#define file_read                     \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define rep(i, a, n) for (ll i = a; i < n; ++i)

int def_wiresur[6];

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

int main(void)
{
    file_read int n_node;
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