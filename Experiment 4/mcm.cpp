#include <iostream>
#include <climits>
#include <random>
#include <ctime>
using namespace std;


void matrixChainOrder(int p[], int n, int m[][100], int s[][100]) {
    for(int i=1; i<=n; i++)
        m[i][i] = 0;

    for(int l=2; l<=n; l++) {
        for(int i=1; i<=n-l+1; i++) {
            int j = i+l-1;
            m[i][j] = INT_MAX;

            for(int k=i; k<=j-1; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

                if(q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void printOptimalParenthesis(int s[][100], int i, int j) {
    if(i == j)
        cout << "A" << i;
    else {
        cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j]+1, j);
        cout << ")";
    }
}

int main() {
    int p[10];
    srand ( time(NULL) );
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distr(15, 46); 

    for(int i=0; i<10; ++i)
        p[i] = distr(gen); 
    
    int n = sizeof(p)/sizeof(p[0]) - 1;

    int m[100][100];
    int s[100][100];

    matrixChainOrder(p, n, m, s);

    cout << "Optimal Parenthesization: ";
    printOptimalParenthesis(s, 1, n);
    cout << endl;

    cout << "Minimum Number of Scalar Multiplications: " << m[1][n] << endl;

    cout << "m table:";

    for(int a = 0; a < 10; a++)
    {
        for(int b = 0; b < 10; b++)
        {
            if(m[a][b] == 0){continue;}
            cout << m[a][b] << " ";
        }
        cout << endl;
    }

    cout << "s table:";

    for(int a = 0; a < 10; a++)
    {
        for(int b = 0; b < 10; b++)
        {
            if(s[a][b] == 0){continue;}
            cout << s[a][b] << " ";
        }
        cout << endl;
    }

     	

    return 0;
}
