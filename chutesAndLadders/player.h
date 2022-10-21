#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QObject>
#include "tile.h"
#include "pawn.h"

using namespace std;

class Player: public QObject
{
    Q_OBJECT

public:
    Player(string username);
    string get_username() {return username_;};
    void SetUsername(string username) {username_ = username;};
    int get_num_rerolls() {return num_rerolls_;};
    void SetNumRerolls(int num_rerolls) {num_rerolls_ = num_rerolls;};
    int get_num_undos() {return num_undos_;};
    void SetNumUndoes(int num_undos) {num_undos_ = num_undos;};
    Pawn* get_pawn() {return pawn_;};
    QColor get_player_color() {return color_;};
    void SetPlayerColor(QColor color) {color_ = color;};
    int get_dice_result() {return dice_result_;};
    void SetDiceResult(int dice_result) {dice_result_=dice_result;};
    bool get_on_board() {return on_board_;};
    void SetOnBoard(bool on_board) {on_board_=on_board;};
    vector<Tile*> get_prev_positions() {return prev_positions_;};
    void push_back_prev(Tile* tile) {prev_positions_.push_back(tile);};
    int get_prev_size() {return prev_positions_size_;};
    void IncreasePrevSize() {prev_positions_size_++;};
    void DecreasePrevSize() {prev_positions_size_--;};

    int get_player_num() {return player_num_;};
    void SetPlayerNum(int num) {player_num_ = num;};

    void UndoMove();

    int RollDice();
    int RerollDice();

    friend bool operator==(const Player &first, const Player &other);
private:
    string username_;
    int num_rerolls_;
    int num_undos_;
    vector<Tile*> prev_positions_;
    int prev_positions_size_;
    Pawn *pawn_;
    QColor color_;
    int dice_result_;
    bool on_board_;

    int player_num_;

};

#endif // PLAYER_H
