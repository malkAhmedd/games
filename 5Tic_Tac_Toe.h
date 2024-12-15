#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "boardgame_classes.h"
using namespace std;
//------------------------- Tic_Tac_Toe Class -------------------------//
template <typename T>
class Tic_Tac_Toe : public Board<T> {
public:
    Tic_Tac_Toe(int r = 5, int c = 5);
    ~Tic_Tac_Toe();                  
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
protected:
    int rows, columns, n_moves;
    T** board;
};

//------------------------- Tic_Tac_ToePlayer Class -------------------------//
template <typename T>
class Tic_Tac_ToePlayer : public Player<T> {
public:
    Tic_Tac_ToePlayer(string name, T symbol);
    virtual void getmove(int& x, int& y);

protected:
    string name;
    T symbol;
};

//------------------------- Tic_Tac_ToeRandomPlayer Class -------------------------//
template <typename T>
class Tic_Tac_ToeRandomPlayer : public RandomPlayer<T> {
public:
    Tic_Tac_ToeRandomPlayer(T symbol); 
    void getmove(int& x, int& y) override;
};


template <typename T>
Tic_Tac_Toe<T>::Tic_Tac_Toe(int r, int c) {
    this->rows = r;
    this->columns = c;
    this->n_moves = 0;

    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = '-';
        }
    }
}

template <typename T>
Tic_Tac_Toe<T>::~Tic_Tac_Toe() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool Tic_Tac_Toe<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '-') {
        return false;
    }
    this->board[x][y] = symbol;
    ++this->n_moves;
    return true;
}
template <typename T>
void Tic_Tac_Toe<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            cout << this->board[i][j] << " ";
        }
        cout << endl;
    }
    
}
template <typename T>
bool Tic_Tac_Toe<T>::is_win() {
    int player1_triples = 0, player2_triples = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns - 2; ++j) {
            if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != '-') {
                if (this->board[i][j] == 'X') player1_triples++;
                else if (this->board[i][j] == 'O') player2_triples++;
            }
            if (this->board[j][i] == this->board[j+1][i] && this->board[j+1][i] == this->board[j+2][i] && this->board[j][i] != '-') {
                if (this->board[j][i] == 'X') player1_triples++;
                else if (this->board[j][i] == 'O') player2_triples++;
            }
        }
    }
   for (int i = 0; i < this->rows - 2; ++i) {
        for (int j = 0; j < this->columns - 2; ++j) {
            if (this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != '-') {
                if (this->board[i][j] == 'X') player1_triples++;
                else if (this->board[i][j] == 'O') player2_triples++;
            }
            if (this->board[i][j+2] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j] && this->board[i][j+2] != '-') {
                if (this->board[i][j+2] == 'X') player1_triples++;
                else if (this->board[i][j+2] == 'O') player2_triples++;
            }
        }
    }
    if (this->n_moves == 24) {
        if (player1_triples > player2_triples) {

            return true;
        } else if (player2_triples > player1_triples) {

            return true;
        } else {

            return true;
        }
    }
    return false; 
}
template <typename T>
bool Tic_Tac_Toe<T>::is_draw() {
    return this->n_moves == 24;
}
template <typename T>
bool Tic_Tac_Toe<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
Tic_Tac_ToePlayer<T>::Tic_Tac_ToePlayer(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void Tic_Tac_ToePlayer<T>::getmove(int& x, int& y) {
    cout << this->name << "'s turn (" << this->symbol << "). Enter your move (row and column): ";
    cin >> x >> y;
}
template <typename T>
Tic_Tac_ToeRandomPlayer<T>::Tic_Tac_ToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
     this->name = "Random Computer Player";
    srand(time(0));
}
template <typename T>
void Tic_Tac_ToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    cout << "Computer's move: " << x << " " << y << endl;
}
#endif