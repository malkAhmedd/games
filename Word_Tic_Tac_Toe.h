
#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <fstream>
#include<string>

template <typename T>
class  Word_Tic_Tac_Toe:public Board<T> {
protected:
    ifstream file ;
    vector<string> dic;
public:
   Word_Tic_Tac_Toe ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Word_Tic_Tac_Toeplayer : public Player<T>{
public:
  Word_Tic_Tac_Toeplayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Word_Tic_Tac_ToeRandomplayer : public RandomPlayer<T>{
public:
    Word_Tic_Tac_ToeRandomplayer (T symbol);

    void getmove(int &x, int &y) ;

};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <fstream>
#include<algorithm>

using namespace std;

// Constructor for X_O_Board
template <typename T>
 Word_Tic_Tac_Toe<T>:: Word_Tic_Tac_Toe() {
    file.open("dic.txt");
    string word;
    while (getline(this->file, word)) {
        dic.push_back(word);
    }
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '0';
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool Word_Tic_Tac_Toe<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '0') {
        return false;  // Invalid move if out of bounds or already occupied
    }
    else {
        this->board[x][y] = toupper( symbol);
        this->n_moves++;
        return true;
    }

}

// Display the board and the pieces on it
template <typename T>
void  Word_Tic_Tac_Toe<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Word_Tic_Tac_Toe<T>::is_win() {
    // Check rows, columns, and diagonals for a valid word
    string word;
    // Check rows
    for (int i = 0; i < 3; i++) {
        word = string(1, this->board[i][0]) + string(1, this->board[i][1]) + string(1, this->board[i][2]);
        if (find(dic.begin(), dic.end(), word) != dic.end()) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        word = string(1, this->board[0][i]) + string(1, this->board[1][i]) + string(1, this->board[2][i]);
        if (find(dic.begin(), dic.end(), word) != dic.end()) {
            return true;
        }
    }

    // Check diagonals
    word = string(1, this->board[0][0]) + string(1, this->board[1][1]) + string(1, this->board[2][2]);
    if (find(dic.begin(), dic.end(), word) != dic.end()) {
        return true;
    }
    word = string(1, this->board[0][2]) + string(1, this->board[1][1]) + string(1, this->board[2][0]);
    if (find(dic.begin(), dic.end(), word) != dic.end()) {
        return true;
    }
    // Check diagonals
    word = string(1, this->board[2][2]) + string(1, this->board[1][1]) + string(1, this->board[0][0]);
    if (find(dic.begin(), dic.end(), word) != dic.end()) {
        return true;
    }
    word = string(1, this->board[2][0]) + string(1, this->board[1][1]) + string(1, this->board[0][2]);
    if (find(dic.begin(), dic.end(), word) != dic.end()) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool  Word_Tic_Tac_Toe<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool  Word_Tic_Tac_Toe<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Word_Tic_Tac_Toeplayer<T>::Word_Tic_Tac_Toeplayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_Tic_Tac_Toeplayer<T>::getmove(int& x, int& y) {
    cout<<"please enter a character: ";
    cin>>this->symbol;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Word_Tic_Tac_ToeRandomplayer<T>::Word_Tic_Tac_ToeRandomplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Word_Tic_Tac_ToeRandomplayer<T>::getmove(int& x, int& y) {
    cout<<"please enter a character: ";
    this->symbol= (rand() % 26) + 'a';
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

}
#endif //WORD_TIC_TAC_TOE_H
