#include <bits/stdc++.h>
using namespace std;

int main()
{

    ofstream fout;
    fout.open("test_case.txt");

    int m, t, s;
    cout << "Enter no. of machines: ";
    cin >> m;
    fout << m << endl;
    cout << "Enter no. of time slots: ";
    cin >> t;
    fout << t << endl;
    cout << "Enter bound on energy generated in a slot: ";
    cin >> s;

    srand((unsigned)time(NULL));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < t; j++)
        {
            if (rand() % m ==0)
                fout << rand() % ((m*(int)cbrt(s) + 1)) << " ";
            else
                fout << rand() % (int(cbrt(s)) + 1)<<" ";
        }
        fout << endl;
    }
    fout << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < t; j++)
        {
            fout << rand() % (s + 1) << " ";
        }
        fout << endl;
    }

    return 0;
}