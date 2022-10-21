#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "board.h"
#include "player.h"
#include "pawn.h"
#include "tile.h"
#include "numplayersdiaglog.h"
#include "usernamesdialog.h"
#include "leaderboarddialog.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    Player* get_curr_player() {return curr_player_;};
    void SetCurrPlayer(Player* curr_player) {curr_player_ = curr_player;};
    vector<Player*> get_players() {return players_;};
    bool get_game_started() {return game_started_;};
    void SetGameStarted(bool started) {game_started_=started;};
    void SwitchPlayer();
    void CheckWin();
    void MakeGame();
    void ResetGame();

    void WritePlayerInformation(Player *winner);

private slots:
    void on_startGameButton_clicked();
    void on_endGameButton_clicked();
    void on_undoButton_clicked();
    void on_rerollButton_clicked();
    void on_rollButton_clicked();
    void on_quitGameButton_clicked();
    void on_moveButton_clicked();
    void IncrementTimer();
    void on_leaderboardButton_clicked();
    void on_newGameButton_clicked();

private:
    Ui::GameWindow *ui;
    int num_players_;
    int players_removed_;

    NumPlayersDiaglog *npd;
    UsernamesDialog *ud;
    LeaderboardDialog *leaderboard;


    QGraphicsScene* starting_area_scene_;
    Board *board_;
    vector<Player*> players_;
    Player *curr_player_;
    bool game_started_;
    QTimer *timer_;
    int time_;
    bool player_is_moving_;
};
#endif // GAMEWINDOW_H
