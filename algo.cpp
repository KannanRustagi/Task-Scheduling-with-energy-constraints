#include <bits/stdc++.h>
using namespace std;

int cube(int x)
{
    return (x * x * x);
}
void show(vector<vector<int>> &V, ofstream &fileStream)
{
    for (auto i : V)
    {
        for (auto j : i)
        {
            fileStream << j << " ";
        }
        fileStream << endl;
    }
}

int main()
{
    ifstream fin;
    fin.open("test_case.txt");

    ofstream fout;
    fout.open("output.txt");

    int N;
    int T;
    fin >> N;
    fin >> T;
    vector<vector<int>> D(N, vector<int>(T, 8)); // 2D Task array
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < T; j++)
        {
            fin >> D[i][j];
        }
    }

    vector<vector<int>> S(N, vector<int>(T, 400)); // 2D Incoming Energy Array

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < T; j++)
        {
            fin >> S[i][j];
        }
    }

    vector<int> D_New(T); // Total number of tasks in each time slot
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < T; j++)
        {
            D_New[j] += D[i][j];
        }
    }
    vector<vector<int>> D_Sched(N, vector<int>(T));              // Number of tasks scheduled in each machine in each time slot
    vector<vector<int>> Pref_S(N, vector<int>(T));               // Total energy available in each machine in each time slot if no tasks scheduled
    vector<vector<int>> Prev_Pref_Used(N, vector<int>(T));       // Total energy used till previous iteration
    vector<vector<int>> Curr_Extra_Pref_Used(N, vector<int>(T)); // Extra energy used by scheduling more tasks in this iteration
    vector<vector<int>> Prev_Suff_Left(N, vector<int>(T));       // Energy left in previous iteration in each machine in each time slot
    vector<pair<int, int>> Machine_Available;
    vector<pair<int, int>> Machine_Available_Next;

    // Calculating Pref_S
    for (int t = 0; t < T; t++)
    {
        for (int m = 0; m < N; m++)
        {
            Pref_S[m][t] = S[m][t];
            if (t)
                Pref_S[m][t] += Pref_S[m][t - 1];
        }
    }

    // Initializing Pref_Suff_Left
    for (int t = T - 1; t >= 0; t--)
    {
        for (int m = 0; m < N; m++)
        {
            Prev_Suff_Left[m][t] = Pref_S[m][t];
        }
    }

    for (int t = 0; t < T; t++)
    {
        for (int m = 0; m < N; m++)
        {
            Machine_Available.push_back({m, t});
        }
    }

    // Check if there is no extra task scheduled in previous iteration
    int changed = 1;
    set<pair<int, pair<int, int>>> Current_Machines;
    while (Machine_Available.size())
    {
        Current_Machines.clear();
        Machine_Available_Next.clear();
        // Updating Prev_Suff_Left
        for (int t = 0; t < T; t++)
        {
            for (int m = 0; m < N; m++)
            {
                Curr_Extra_Pref_Used[m][t] = 0;
                Prev_Suff_Left[m][t] = Pref_S[m][t] - Prev_Pref_Used[m][t];
            }
        }
        for (int t = T - 2; t >= 0; t--)
        {
            for (int m = 0; m < N; m++)
            {
                Prev_Suff_Left[m][t] = min(Prev_Suff_Left[m][t], Prev_Suff_Left[m][t + 1]);
            }
        }

        changed = 0;

        for (auto i : Machine_Available)
        {
            int m = i.first, t = i.second;

            // Find extra energy available to use
            int E_Available = Pref_S[m][t] - Prev_Pref_Used[m][t];
            if (t)
                E_Available -= Curr_Extra_Pref_Used[m][t - 1];

            // You can only use as much energy which does not reduce energy below 0 in any later time slot
            if (t != T - 1)
            {
                E_Available = min(E_Available, Prev_Suff_Left[m][t + 1]);
            }

            Current_Machines.insert({t, {E_Available, m}});
        }

        for (auto i : Current_Machines)
        {
            int t = i.first, m = i.second.second;
            int E_Available = Pref_S[m][t] - Prev_Pref_Used[m][t];
            if (t)
                E_Available -= Curr_Extra_Pref_Used[m][t - 1];
            // If tasks are left to be scheduled, try to schedule here
            if (D_New[t])
            {
                int Extra_Energy_Needed = cube(D_Sched[m][t] + 1) - cube(D_Sched[m][t]);
                if (Extra_Energy_Needed <= E_Available)
                {
                    Prev_Pref_Used[m][t] += Extra_Energy_Needed;
                    Curr_Extra_Pref_Used[m][t] += Extra_Energy_Needed;
                    D_Sched[m][t]++;
                    D_New[t]--;
                    changed++;
                    Machine_Available_Next.push_back({m, t});
                }
            }
            // Update arrays
            if (t)
            {
                Prev_Pref_Used[m][t] += Curr_Extra_Pref_Used[m][t - 1];
                Curr_Extra_Pref_Used[m][t] += Curr_Extra_Pref_Used[m][t - 1];
            }
        }

        Machine_Available = Machine_Available_Next;
    }

    fout << "Power received at each slot at each machine:" << endl;
    fout << endl;
    show(S, fout);
    fout << endl;
    fout << endl;
    fout << "Tasks received at each slot at each machine:" << endl;
    fout << endl;
    show(D, fout);
    cout << endl;
    fout << endl;
    fout << "Tasks scheduled at each slot at each machine:" << endl;
    fout << endl;
    show(D_Sched, fout);
    fout << endl;
    fout << "#########################################################################################" << endl;

    vector<int> energy_at_t(T);
    vector<int> energy_at_m(N);

    for (int t = 0; t < T; t++)
    {
        for (int m = 0; m < N; m++)
        {
            energy_at_t[t] += S[m][t];
            energy_at_m[m] += S[m][t];
        }
    }
    fout << "ANALYSIS OF THE OUTPUT GENERATED: " << endl;
    fout << endl
         << "Energy received at ith time slot:\n";
    fout << endl;
    for (auto i : energy_at_t)
    {
        fout << i << " ";
    }
    fout << endl;

    fout << endl
         << "Energy received at ith machine:\n";
    fout << endl;
    for (auto i : energy_at_m)
    {
        fout << i << " ";
    }
    fout << endl;

    int total_tasks = 0;
    vector<int> tasks_at_t(T);
    vector<int> tasks_at_m(N);
    for (int t = 0; t < T; t++)
    {
        for (int m = 0; m < N; m++)
        {
            total_tasks += D[m][t];
            tasks_at_t[t] += D_Sched[m][t];
            tasks_at_m[m] += D_Sched[m][t];
        }
    }

    fout << endl
         << "Tasks scheduled at ith time slot:\n";
    fout << endl;
    for (auto i : tasks_at_t)
    {
        fout << i << " ";
    }
    fout << endl;

    fout << endl
         << "Tasks scheduled at ith machine:\n";
    fout << endl;
    for (auto i : tasks_at_m)
    {
        fout << i << " ";
    }
    fout << endl;
    int total_tasks_scheduled = 0;

    for (int m = 0; m < N; m++)
    {
        for (int t = 0; t < T; t++)
        {
            total_tasks_scheduled += D_Sched[m][t];
        }
    }
    fout << endl;
    fout << "Total tasks receieved: " << total_tasks << endl;
    fout << "Total tasks completed: " << total_tasks_scheduled << endl;
    cout << "Task Scheduling is complete, see output.txt for the output" << endl;
}