#include <iostream>
#include <SolveSyst.h>
using namespace std;

int main()
{
    int n, m;
    cout << "Enter amount of equations and amount of variables: ";
    cin >> n >> m;
    int** syst = new int*[n];
    for (int i = 0; i < n; i++)
    {
        syst[i] = new int[m];
    }
    
    



    return 0;
}