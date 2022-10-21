#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "board.h"
#include "marble.h"
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void delay(int n);
    void MakeBoard();
    void SetAlertText(std::string s);
    void HandoutMarbles();
    void SwitchPlayer();
    void DistributeMarblesFrom(Pit *p);
    void UpdateStoreLabels();
    void CheckEmptyPits();
    void CheckWinner();
    void StealMarbles(Pit *stealFrom, Pit* transferTo, bool special);
    void CheckMarbleLastPit();

private slots:
    void on_startGame_clicked();
    void on_endGame_clicked();
    void PitSelectedSlot(Pit *p);

private:
    Ui::GameWindow *ui;
    Board *board_;
    Player *player1_;
    Player *player2_;
    Player *curr_player_;
    bool game_started_;
    bool game_over_;
    int last_pit_num_;
    bool on_delay_;

};
#endif // GAMEWINDOW_H
