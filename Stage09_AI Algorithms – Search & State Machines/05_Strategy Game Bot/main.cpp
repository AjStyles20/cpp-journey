#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

// Game constants
const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';

// Game board class
class TicTacToe {
private:
    vector<vector<char>> board;
    
public:
    TicTacToe() : board(3, vector<char>(3, EMPTY)) {}
    
    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " \n";
            if (i < 2) cout << "-----------\n";
        }
        cout << "\n";
    }
    
    bool isMoveValid(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY;
    }
    
    bool makeMove(int row, int col, char player) {
        if (!isMoveValid(row, col)) return false;
        board[row][col] = player;
        return true;
    }
    
    bool isBoardFull() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == EMPTY) return false;
            }
        }
        return true;
    }
    
    char checkWinner() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return board[i][0];
            }
        }
        
        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] != EMPTY && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                return board[0][j];
            }
        }
        
        // Check diagonals
        if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return board[0][0];
        }
        if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return board[0][2];
        }
        
        return EMPTY;
    }
    
    vector<pair<int, int>> getAvailableMoves() {
        vector<pair<int, int>> moves;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    moves.emplace_back(i, j);
                }
            }
        }
        return moves;
    }
    
    // Minimax algorithm implementation
    int minimax(bool isMaximizing, int depth) {
        char winner = checkWinner();
        
        if (winner == AI) return 10 - depth;
        if (winner == HUMAN) return depth - 10;
        if (isBoardFull()) return 0;
        
        if (isMaximizing) {
            int bestScore = numeric_limits<int>::min();
            for (const auto& move : getAvailableMoves()) {
                board[move.first][move.second] = AI;
                int score = minimax(false, depth + 1);
                board[move.first][move.second] = EMPTY;
                bestScore = max(score, bestScore);
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (const auto& move : getAvailableMoves()) {
                board[move.first][move.second] = HUMAN;
                int score = minimax(true, depth + 1);
                board[move.first][move.second] = EMPTY;
                bestScore = min(score, bestScore);
            }
            return bestScore;
        }
    }
    
    // AI makes a move using minimax
    void makeAIMove() {
        int bestScore = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};
        
        for (const auto& move : getAvailableMoves()) {
            board[move.first][move.second] = AI;
            int score = minimax(false, 0);
            board[move.first][move.second] = EMPTY;
            
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
        
        if (bestMove.first != -1) {
            makeMove(bestMove.first, bestMove.second, AI);
        }
    }
};

// Main game loop
void playGame() {
    TicTacToe game;
    bool humanTurn = true;
    
    cout << "Tic-Tac-Toe - You are X, AI is O\n";
    cout << "Enter row and column (0-2) separated by space\n";
    
    while (true) {
        game.printBoard();
        
        char winner = game.checkWinner();
        if (winner != EMPTY) {
            cout << (winner == HUMAN ? "You win!" : "AI wins!") << "\n";
            break;
        }
        
        if (game.isBoardFull()) {
            cout << "It's a tie!\n";
            break;
        }
        
        if (humanTurn) {
            int row, col;
            cout << "Your move (row col): ";
            cin >> row >> col;
            
            if (!game.makeMove(row, col, HUMAN)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
        } else {
            cout << "AI is thinking...\n";
            game.makeAIMove();
        }
        
        humanTurn = !humanTurn;
    }
}

int main() {
    playGame();
    return 0;
}