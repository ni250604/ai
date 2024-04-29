#include <bits/stdc++.h>
using namespace std;
int N;

void printSol(vector<vector<int>> board)
{
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         if(board[i][j]==1)  cout<<"Q"<<" ";
    //         else                cout << board[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 1)
            {
                cout << "\033[1;35m" << "Q" << " "<< "\033[0m";
            }
            else        cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool isSafe(int row, int col, vector<bool> row_check, vector<bool> slash, vector<bool> back_slash)
{
    if (row_check[row] == true || slash[row + col] == true || back_slash[col - row + N - 1] == true)
    {
        return false;
    }

    return true;
}

bool solve(vector<vector<int>> &board, int col, vector<bool> row_check, vector<bool> slash, vector<bool> back_slash)
{
    if (col >= N)   return true;
    
    for (int i = 0; i < N; i++)
    {
        if (isSafe(i, col, row_check, slash, back_slash) == true)
        {
            row_check[i] = true;
            slash[i + col] = true;
            back_slash[col - i + N - 1] = true;
            board[i][col] = 1; 

            if (solve(board, col + 1, row_check, slash, back_slash) == true)      return true;
            
            row_check[i] = false;
            slash[i + col] = false;
            back_slash[col - i + N - 1] = false;
            board[i][col] = 0; 
        }
    }
    return false;
}

int main()
{
    cout << "Enter the no of rows for the square Board : ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));
    vector<bool> row_check(N, false);

    vector<bool> slash(2 * N - 1, false);
    vector<bool> back_slash(2 * N - 1, false);

    bool ans = solve(board, 0, row_check, slash, back_slash);

    if (ans == true)        {
        
        printSol(board);
    }
    else                    cout << "Solution Does not Exist\n";
    
}
