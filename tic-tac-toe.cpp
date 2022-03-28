// TIC-TAC-TOE [game]

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;

void displayBoard(string **b);
bool userFirst();
bool validSpace(string **b, int &row, int &col);
void pickRandomSpace(int &row, int &col);
void generateComputerMove(string **b, int &row, int &col);
bool currentPlayerWon(string **b, string symbol);

int main()
{
    int xScore = 0;
    int oScore = 0;
    int ties = 0;
    int round = 1;
    cout << "\nWelcome to Tic-Tac-Toe" << endl;
    while (true)
    {
        // construct board
        // string board[SIZE][SIZE];
        string **board = new string *[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            board[i] = new string[SIZE];
        }

        int position_id = 1;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                board[i][j] = to_string(position_id);
                /*
                    stringstream ss;
                    ss << position_id;
                    board[i][j] = ss.str();
                */
                position_id++;
            }
        }
        // Initial game output
        cout << "\nRound:" << round << endl;
        round++;
        bool userTurn = userFirst();
        if (userTurn == true)
        {
            cout << "Player goes first!" << endl;
        }
        else
        {
            cout << "Computer goes first!" << endl;
        }
        // Loop for turn taking in game
        int positionsRemaining = SIZE * SIZE;
        bool userWon = false;
        bool computerWon = false;
        while ((positionsRemaining > 0) && (!userWon) && (!computerWon))
        {
            displayBoard(board);
            // User's turn
            if (userTurn)
            {
                cout << "Player turn:" << endl;
                bool validMove = false;
                while (!validMove)
                {
                    int position_id;
                    cout << "Enter a position: ";
                    cin >> position_id;
                    if ((position_id <= (SIZE * SIZE)) && (position_id > 0))
                    {
                        int row = (position_id - 1) / SIZE;
                        int col = (position_id - 1) % SIZE;
                        // cout << "row = " << row << " col = " << col << endl;
                        if (validSpace(board, row, col))
                        {
                            board[row][col] = "X";
                            validMove = true;
                        }
                        else
                        {
                            cout << "Position already used. Try again." << endl;
                        }
                    }
                    else
                    {
                        cout << "Position invalid. Try again." << endl;
                    }
                }
                positionsRemaining--;
                userWon = currentPlayerWon(board, "X");
                userTurn = false;
            }
            // Computer's turn
            else
            {
                cout << "Computer turn:" << endl;
                // The row and col are both passed as call-by-reference
                int row, col;

                generateComputerMove(board, row, col);
                board[row][col] = "O";

                positionsRemaining--;
                computerWon = currentPlayerWon(board, "O");
                userTurn = true;
            }
        }
        // Display game result
        displayBoard(board);
        if (userWon)
        {
            cout << "Congratulations! You have won!" << endl;
            xScore++;
        }
        else if (computerWon)
        {
            cout << "The computer has won! Try again." << endl;
            oScore++;
        }
        else
        {
            cout << "Out of moves! Draw! Try again." << endl;
            ties++;
        }

        char next;
        cout << "Continue? Y / N: ";
        cin >> next;
        if (next == 'N' || next == 'n')
        {
            break;
        }
    }

    cout << "\nResults:" << endl;
    cout << "X:    " << xScore << endl;
    cout << "O:    " << oScore << endl;
    cout << "Ties: " << ties << endl;
    cout << "GG" << endl;

    return 0;
}

void displayBoard(string **b)
{
    cout << "Tic-tac-toe board:" << endl
         << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << b[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool userFirst()
{
    // set seed for random number generation
    srand(time(NULL));
    // generate a random number
    // 0 for computer
    // 1 for user
    int num = rand() % 2;
    if (num == 0)
    {
        return false;
    }
    return true;
}

bool validSpace(string **b, int &row, int &col)
{
    return (b[row][col] != "O" && b[row][col] != "X");
}

void pickRandomSpace(int &row, int &col)
{
    // srand(time(NULL));
    row = rand() % SIZE;
    col = rand() % SIZE;
}

void generateComputerMove(string **b, int &row, int &col)
{
    int count;
    //#1 Check winning condition:
    // Horizontal case
    // Loop through each row
    for (int i = 0; i < SIZE; i++)
    {
        count = 0;
        // Check all positions in row and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[i][j] == "O")
            {
                count++;
            }
            if (count == 2)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    row = i;
                    col = j;
                    if (validSpace(b, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
    // Vertical case
    // Loop through each column
    for (int i = 0; i < SIZE; i++)
    {
        count = 0;
        // Check all positions in column and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[j][i] == "O")
            {
                count++;
            }
            if (count == 2)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    row = j;
                    col = i;
                    if (validSpace(b, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
    // Diagonal case #1
    count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[i][i] == "O")
        {
            count++;
        }
        if (count == 2)
        {
            for (int i = 0; i < SIZE; i++)
            {
                row = i;
                col = i;
                if (validSpace(b, row, col))
                {
                    return;
                }
            }
        }
    }
    // Diagonal case #2
    count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[(SIZE - 1) - i][i] == "O")
        {
            count++;
        }
        if (count == 2)
        {
            for (int i = 0; i < SIZE; i++)
            {
                row = (SIZE - 1) - i;
                col = i;
                if (validSpace(b, row, col))
                {
                    return;
                }
            }
        }
    }

    //#2 Check the opponent winning condition and counter
    // Horizontal case
    // Loop through each row
    for (int i = 0; i < SIZE; i++)
    {
        count = 0;
        // Check all positions in row and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[i][j] == "X")
            {
                count++;
            }
            if (count == 2)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    row = i;
                    col = j;
                    if (validSpace(b, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
    // Vertical case
    // Loop through each column
    for (int i = 0; i < SIZE; i++)
    {
        count = 0;
        // Check all positions in column and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[j][i] == "X")
            {
                count++;
            }
            if (count == 2)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    row = j;
                    col = i;
                    if (validSpace(b, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
    // Diagonal case #1
    count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[i][i] == "X")
        {
            count++;
        }
        if (count == 2)
        {
            for (int i = 0; i < SIZE; i++)
            {
                row = i;
                col = i;
                if (validSpace(b, row, col))
                {
                    return;
                }
            }
        }
    }
    // Diagonal case #2
    count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[(SIZE - 1) - i][i] == "X")
        {
            count++;
        }
        if (count == 2)
        {
            for (int i = 0; i < SIZE; i++)
            {
                row = (SIZE - 1) - i;
                col = i;
                if (validSpace(b, row, col))
                {
                    return;
                }
            }
        }
    }

    //#3 Create single winning condition
    // Horizontal case
    // Loop through each row
    for (int i = 0; i < SIZE; i++)
    {
        count = 0;
        // Check all positions in row and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[i][j] == "O")
            {
                count++;
            }
            else if (b[i][j] == "X")
            {
                break;
            }
            if (count == 1)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    row = i;
                    col = j;
                    if (validSpace(b, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
    // Vertical case
    // Loop through each column
    for (int i = 0; i < SIZE; i++)
    {
        count = 0;
        // Check all positions in column and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[j][i] == "O")
            {
                count++;
            }
            else if (b[j][i] == "X")
            {
                break;
            }
            if (count == 1)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    row = j;
                    col = i;
                    if (validSpace(b, row, col))
                    {
                        return;
                    }
                }
            }
        }
    }
    // Diagonal case #1
    count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[i][i] == "O")
        {
            count++;
        }
        else if (b[i][i] == "X")
        {
            break;
        }
        if (count == 1)
        {
            for (int i = 0; i < SIZE; i++)
            {
                row = i;
                col = i;
                if (validSpace(b, row, col))
                {
                    return;
                }
            }
        }
    }
    // Diagonal case #2
    count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[(SIZE - 1) - i][i] == "O")
        {
            count++;
        }
        else if (b[(SIZE - 1) - i][i] == "X")
        {
            break;
        }
        if (count == 1)
        {
            for (int i = 0; i < SIZE; i++)
            {
                row = (SIZE - 1) - i;
                col = i;
                if (validSpace(b, row, col))
                {
                    return;
                }
            }
        }
    }

    //#4 Middle position move
    if ((b[1][1] != "X") && (b[1][1] != "O"))
    {
        row = 1;
        col = 1;
        return;
    }

    //#5 Random move
    while (true)
    {
        pickRandomSpace(row, col);
        if (validSpace(b, row, col))
        {
            return;
        }
    }
}

// Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string **b, string symbol)
{
    // Horizontal case
    // Loop through each row
    for (int i = 0; i < SIZE; i++)
    {
        bool rowWinDetected = true;
        // Check all positions in row and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[i][j] != symbol)
            {
                rowWinDetected = false;
            }
        }
        if (rowWinDetected)
        {
            return true;
        }
    }

    // Vertical case
    // Loop through each column
    for (int i = 0; i < SIZE; i++)
    {
        bool colWinDetected = true;
        // Check all positions in column and see if they are the same symbol
        for (int j = 0; j < SIZE; j++)
        {
            if (b[j][i] != symbol)
            {
                colWinDetected = false;
            }
        }
        if (colWinDetected)
        {
            return true;
        }
    }

    // Diagonal case #1
    bool diagonal1WinDetected = true;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[i][i] != symbol)
        {
            diagonal1WinDetected = false;
        }
    }
    if (diagonal1WinDetected)
    {
        return true;
    }

    // Diagonal case #2
    bool diagonal2WinDetected = true;
    for (int i = 0; i < SIZE; i++)
    {
        if (b[(SIZE - 1) - i][i] != symbol)
        {
            diagonal2WinDetected = false;
        }
    }
    if (diagonal2WinDetected)
    {
        return true;
    }

    // otherwise win not diagonal2WinDetected
    return false;
}
