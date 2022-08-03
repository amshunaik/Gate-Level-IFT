#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=5948366&tag=1

struct GATE
{
    int gate_number;
    string gate_type;
    vector<int> input_gate_numbers;
    int level = -1;
    bool output, shadow_output;
};

bool AND(vector<bool> v)
{
    bool res;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 0)
            continue;
        if (i == 1)
            res = v[0] && v[1];
        else
            res = res && v[i];
    }

    return res;
}
bool NAND(vector<bool> v)
{
    bool res;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 0)
            continue;
        if (i == 1)
            res = !(v[0] && v[1]);
        else
            res = !(res && v[i]);
    }

    return res;
}

bool NOT(vector<bool> v)
{
    return !v[0];
}

bool OR(vector<bool> v)
{
    bool res;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 0)
            continue;
        if (i == 1)
            res = v[0] || v[1];
        else
            res = res || v[i];
    }

    return res;
}
bool NOR(vector<bool> v)
{
    bool res;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 0)
            continue;
        if (i == 1)
            res = !(v[0] || v[1]);
        else
            res = !(res || v[i]);
    }

    return res;
}

bool XOR(vector<bool> v)
{
    bool res;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 0)
            continue;
        if (i == 1)
            res = (v[0] && (!v[1])) || (!v[0] && (v[1]));
        else
            res = (res && !v[i]) || (!res && v[i]);
    }

    return res;
}

bool shadow_not(vector<bool> v, vector<bool> sh_v)
{
    /*
        Lemma 2.1
    */
    return sh_v[0];
}

bool shadow_and(vector<bool> a, vector<bool> sh_a)
{
    /*
        Let's say
            F = A and B;
        Then;
            sh(F) = A*sh(B) + B*sh(A) + sh(A)*sh(B);
    */
    bool term1, term2;
    for (int i = 0; i < a.size(); i++)
    {
        if (i == 0)
            term1 = (a[0] || sh_a[0]);
        else if (i == 1)
        {
            term1 = term1 && (a[i] || sh_a[i]);
            term2 = a[0] && a[1];
        }
        else
        {
            term1 = term1 && (a[i] || sh_a[i]);
            term2 = term2 && a[i];
        }
    }

    return term1 - term2;
}

bool shadow_nand(vector<bool> a, vector<bool> sh_a)
{
    /*
        Let's say
            F = A and B;
        Then;
            sh(F) = A*sh(B) + B*sh(A) + sh(A)*sh(B);
    */
    bool term1, term2;
    for (int i = 0; i < a.size(); i++)
    {
        if (i == 0)
            term1 = (a[0] || sh_a[0]);
        else if (i == 1)
        {
            term1 = term1 && (a[i] || sh_a[i]);
            term2 = a[0] && a[1];
        }
        else
        {
            term1 = term1 && (a[i] || sh_a[i]);
            term2 = term2 && a[i];
        }
    }

    return term1 - term2;
}

bool shadow_or(vector<bool> a, vector<bool> sh_a)
{
    /*
        Let's say
            F = A or B;
        Then;
            sh(F) = A'*sh(B) + B'*sh(A) + sh(A)*sh(B);
    */
    bool term1, term2;
    for (int i = 0; i < a.size(); i++)
    {
        if (i == 0)
            term1 = (!a[0] || sh_a[0]);
        else if (i == 1)
        {
            term1 = term1 && (!a[i] || sh_a[i]);
            term2 = !a[0] && !a[1];
        }
        else
        {
            term1 = term1 && (!a[i] || sh_a[i]);
            term2 = term2 && !a[i];
        }
    }

    return term1 - term2;
}
bool shadow_nor(vector<bool> a, vector<bool> sh_a)
{
    /*
        Let's say
            F = A or B;
        Then;
            sh(F) = A'*sh(B) + B'*sh(A) + sh(A)*sh(B);
    */
    bool term1, term2;
    for (int i = 0; i < a.size(); i++)
    {
        if (i == 0)
            term1 = (!a[0] || sh_a[0]);
        else if (i == 1)
        {
            term1 = term1 && (!a[i] || sh_a[i]);
            term2 = !a[0] && !a[1];
        }
        else
        {
            term1 = term1 && (!a[i] || sh_a[i]);
            term2 = term2 && !a[i];
        }
    }

    return term1 - term2;
}

bool shadow_xor(vector<bool> a, vector<bool> sh_a)
{
    /*
        Let's say
            F = A xor B;
        Then;
            sh(F) = sh(A) + sh(B);
    */
    bool res;
    for (int i = 0; i < sh_a.size(); i++)
    {
        if (i == 0)
            continue;
        else if (i == 1)
            res = sh_a[0] || sh_a[1];
        else
        {
            res = res || sh_a[i];
        }
    }
    return res;
}

void read_input_output(vector<int> *v, string s)
{
    // A function to extract the gate name from the string and pushes into the vector
    int i = 0;
    bool store = false;
    string gate = "";
    while (s[i] != ')')
    {
        if (s[i - 1] == '(' && !store)
            store = true;
        if (store)
            gate += s[i];
        i++;
    }
    (*v).push_back(stoi(gate));
}

void read_intermediate(map<int, struct GATE> *v, string s)
{
    // A function to extract the gate name from the string and pushes into a map
    // where index of map is the gate number and the value is the properties of the gate
    int i = 0, count = 0;
    bool store = true;
    struct GATE g;
    string gate = "";
    while (s[i] != ' ')
    {
        if (store)
            gate += s[i];
        i++;
    }
    g.gate_number = stoi(gate);
    i += 3;
    string gate_type = "";
    while (s[i] != '(')
    {
        if (store)
            gate_type += s[i];
        i++;
    }
    g.gate_type = gate_type;
    i++;
    string inp_g_name = "";
    while (s[i] != ')')
    {
        if (s[i] == ' ' || s[i] == ',')
            store = false;
        else
            store = true;
        if (s[i - 1] == ' ')
            inp_g_name = "";
        if (store)
            inp_g_name += s[i];
        if (s[i + 1] == ',' || s[i + 1] == ')')
            g.input_gate_numbers.push_back(stoi(inp_g_name)), count++;
        i++;
    }
    (*v)[g.gate_number] = g;
}
map<int, vector<int>> levellise(map<int, struct GATE> m, vector<int> input_gate_numbers)
{
    /*
        This function returns a map where indices of the map are the levels and
        its values are the gate numbers belonging to the levels.
    */
    map<int, vector<int>> res; // Output Map
    map<int, int> levelled;    // Mapping a gate and it's corresponding level if determined
    map<int, struct GATE> M;
    M = m; // Just Copying the original argument, because in C++ we can change the local variables only
    for (auto i : input_gate_numbers)
    {
        // Assigning level 0 to all the input gates..
        levelled[i] = 0;
        res[0].push_back(i);
    }
    int count, MAX, level = 1;
    int tc = levelled.size(); // tc is a variable that
    while (tc < (m.size() + input_gate_numbers.size()))
    {
        for (auto i : M)
        {
            count = 0;
            MAX = -1;
            for (auto j : i.second.input_gate_numbers)
            {
                map<int, int>::iterator itr;
                for (itr = levelled.begin(); itr != levelled.end(); itr++)
                {
                    if (itr->first == j)
                    {
                        count++;
                        MAX = max(itr->second, MAX);
                    }
                }
            }
            if (count == i.second.input_gate_numbers.size() && MAX == level - 1)
            {
                MAX += 1;
                i.second.level = MAX;
                levelled[i.second.gate_number] = MAX;
                res[level].push_back(i.second.gate_number);
                tc++;
            }
        }
        level++;
    }
    return res;
}

vector<vector<bool>> generate_input_values(int n)
{
    vector<vector<bool>> v;
    vector<bool> x;
    for (int mask = 0; mask < (1 << 2 * n); mask++)
    {
        if(mask>=500) break;
        for (int i = 0; i < 2 * n; i++)
        {
            if ((mask & (1 << i)) != 0)
                x.push_back(true);
            else
                x.push_back(false);
        }
        reverse(x.begin(),x.end());
        v.push_back(x);
        x.clear();
    }
    return v;
}

map<int,pair<bool,bool>> evaluate(vector<bool> inputs, map<int, vector<int>> levellised, map<int, struct GATE> v, vector<int> input_gate_numbers,vector<int> output_gate_numbers)
{
    map<int,pair<bool,bool>> res,out;
    for (int i = 0; i < input_gate_numbers.size(); i++)
    {
        res[input_gate_numbers[i]] = make_pair(inputs[i],inputs[i+input_gate_numbers.size()]);
    }
    for(auto level:levellised)
    {
        if(level.first>0)
        {
            // cout<<"Executing: "<<level.first<<endl;
            for(auto j:level.second)
            {
                vector<bool> vec,vec_sh;
                for(auto k:v[j].input_gate_numbers)
                {
                    vec.push_back(res[k].first);
                    vec_sh.push_back(res[k].second);
                }
                bool out,out_t;
                if(v[j].gate_type=="AND")
                {
                    out = AND(vec);
                    out_t = shadow_and(vec,vec_sh);
                }
                else if(v[j].gate_type=="OR")
                {
                    out = OR(vec);
                    out_t = shadow_or(vec,vec_sh);
                }
                else if(v[j].gate_type=="NOT")
                {
                    out = NOT(vec);
                    out_t = shadow_not(vec,vec_sh);
                }
                else if(v[j].gate_type=="XOR")
                {
                    out = XOR(vec);
                    out_t = shadow_xor(vec,vec_sh);
                }
                else if(v[j].gate_type=="NOR")
                {
                    out = NOR(vec);
                    out_t = shadow_nor(vec,vec_sh);
                }
                else if(v[j].gate_type=="NAND")
                {
                    out = NAND(vec);
                    out_t = shadow_nand(vec,vec_sh);
                }
                
                res[v[j].gate_number] = make_pair(out,out_t);
            }
        }
    }
    for(auto i:res)
    {
        for(auto j:output_gate_numbers)
        {
            if(i.first==j)
                out[i.first] = i.second; 
        }
    }
    return out;
}
int main()
{
    string path = "D:/GLIFT-1/Test Benches/sample_circuit.txt";
    ifstream infile(path);
    string line;
    vector<int> input_gate_numbers, output_gate_numbers;
    map<int, struct GATE> intermediate_gates; // This is a map that stores gate properties corresponding to it's gate number
    while (getline(infile, line))
    {
        if (line[0] == '#')
            continue; // If the line is a commented line then we do not want to read that further
        else if (line[0] == '\0')
            continue; // If the line is newline/empty line, it doesn't contain any info
        else if (line[0] == 'I')
            read_input_output(&input_gate_numbers, line); // If the line starts with I then it contains input gate names
        else if (line[0] == 'O')
            read_input_output(&output_gate_numbers, line); // If the line starts with O then it contains output gate names
        else
        {
            read_intermediate(&intermediate_gates, line);
        }
    }
    cout<<"Executing these..";
    /*
    // Printing the Gate details
    for(auto i:intermediate_gates)
    {
        cout<<"Gate Details: "<<endl;
        cout<<i.gate_number<<endl;
        cout<<i.gate_type<<endl;
        for (auto j:i.input_gate_numbers)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    // Printing the Gate details
    for(auto i:intermediate_gates)
    {
        cout<<"Gate Details: "<<endl;
        cout<<i.second.gate_number<<endl;
        cout<<i.second.gate_type<<endl;
        for (auto j:i.second.input_gate_numbers)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    */

    map<int, vector<int>> res = levellise(intermediate_gates, input_gate_numbers);
    /*
    for(auto i:res)
    {
        cout<<"Level: "<<i.first<<endl;
        cout<<"Gates are: ";
        for(auto j:i.second)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    */
    ofstream output("output_sample_circuit.txt");
    vector<vector<bool>> input_values;
    input_values = generate_input_values(input_gate_numbers.size());
    for (int i = 0; i < input_gate_numbers.size(); i++)
    {
        output<<setw(6)<<"In-"<<input_gate_numbers[i];
    }
    for (int i = 0; i < input_gate_numbers.size(); i++)
    {
        output<<setw(6)<<"In-"<<input_gate_numbers[i]<<"t";
    }
    for (int i = 0; i < output_gate_numbers.size(); i++)
    {
        output<<setw(6)<<"Out-"<<output_gate_numbers[i];
        output<<setw(6)<<"Out-"<<output_gate_numbers[i]<<"t";
    }
    
    output<<endl;
    for(auto i:input_values)
    {
        map<int,pair<bool,bool>> q;
        q = evaluate(i, res, intermediate_gates,input_gate_numbers,output_gate_numbers);

        for(auto j:i)
            output<<setw(7)<<j;
        for(auto dj:q)
            output<<setw(7)<<dj.second.first<<setw(7)<<dj.second.second;
        output<<endl;
    }
    cout<<"Execution complete!!";
    return 0;
}


