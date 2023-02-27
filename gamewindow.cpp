#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QtWidgets>
#include <QTime>
#include <QGraphicsDropShadowEffect>
#include "gamewindow.h"
#include "ui_gamewindow.h"

/**
  GameWindow constructor, sets up the ui and calls MakeBoard()
*/
GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    MakeBoard();

    //set shadow effect under alert label
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(10);
    effect->setColor(QColor(0,0,0,200));
    effect->setOffset(0.5,0.5);
    ui->alertLabel->setGraphicsEffect(effect);
}

/**
  GameWindow destructor, tries to delete pointers
*/
GameWindow::~GameWindow()
{
    delete ui;
    delete board_;
    delete player1_;
    delete player2_;
}

/**
  Delay function

  @param n Miliseconds to delay for
*/
void GameWindow::delay(int n)
{
    ui->endGame->setEnabled(false);
    on_delay_ = true;
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    ui->endGame->setEnabled(true);
    on_delay_ = false;
}

/**
  Sets up the entire board, adds players, and updates labels to start the game
*/
void GameWindow::MakeBoard() {
    //hide things at the beginning
    ui->startGame->setEnabled(true);
    ui->alertLabel->hide();
    ui->endGame->hide();
    ui->store1Label->hide();
    ui->store2Label->hide();
    ui->instructionsFrame->show();

    game_started_ = false;
    game_over_ = false;
    on_delay_ = false;

    last_pit_num_ = 999;

    //setup players
    player1_ = new Player(1);
    player2_ = new Player(2);
    curr_player_ = player1_;

    //ui setup
    QGraphicsView *view = ui->graphicsView;
    int width = view->frameSize().width()-8;
    int height = view->frameSize().height()-8;
    view->setSceneRect(0, 0, width, height);

    board_ = new Board;
    view->setScene(board_);

    for (int i = 0; i < 14; i++) {
        if (i != 6 && i != 13) {
            Pit *p = board_->get_pit_at(i);
            connect(p, &Pit::PitSelected, this, &GameWindow::PitSelectedSlot);
        }
    }

    UpdateStoreLabels();
}

/**
  Set the alert label on the UI

  @param s String to set the alert label to
*/
void GameWindow::SetAlertText(std::string s) {
    QString text(s.c_str());
    ui->alertLabel->setText(text);
    ui->alertLabel->setStyleSheet("color: "+curr_player_->get_color().name());
}

void GameWindow::HandoutMarbles() {
    for (int i = 0; i < 14; i++) {
        if (i != 6 && i != 13 && i != 0 && i != 7) {
            Pit* p = board_->get_pit_at(i);
            for (int j = 0; j < 4; j++) {
                Marble* marble = MarbleFactory::GetMarble(p, QColor(255,255,255,175));
                p->AddMarble(marble);
                board_->addItem(marble);
            }
        } else if (i == 0 || i == 7) {
            Pit* p = board_->get_pit_at(i);
            for (int j = 0; j < 4; j++) {
                if (j == 0) {
                    SpecialMarble* sm = MarbleFactory::GetSpecialMarble(p, QColor(255, 0, 0, 175));
                    p->AddMarble(sm);
                    board_->addItem(sm);
                } else {
                    Marble* marble = MarbleFactory::GetMarble(p, QColor(255,255,255,175));
                    p->AddMarble(marble);
                    board_->addItem(marble);
                }
            }
        }
    }

    update();
}

/**
  Switches players
*/
void GameWindow::SwitchPlayer() {
    if (curr_player_ == player1_) {
        curr_player_ = player2_;
        SetAlertText("Player 2's turn!");
    } else {
        curr_player_ = player1_;
        SetAlertText("Player 1's turn!");
    }
}

/**
  Distributes marbles to next pits corresponding
   to the number of marbles in the original pit

  @param p Pit to distribute marbles from
*/
void GameWindow::DistributeMarblesFrom(Pit *p) {
    Marble *extraMarble = nullptr;
    int num_marbles = p->get_num_marbles();
    int curr_pit_index = 0;

    if (p->get_pit_num() >= 7) {
        curr_pit_index = p->get_pit_num();
    } else {
        curr_pit_index = p->get_pit_num()-1;
    }
    Pit *new_pit = p;
    for (int i = 0; i < num_marbles; i++) {
        if (i != 13) {
            Marble *m = p->get_marble_at(i);
            new_pit = nullptr;
            int new_pit_index = curr_pit_index+(i+1);
            if (new_pit_index >= 14) {
                new_pit_index -= 14;
            }
            new_pit = board_->get_pit_at(new_pit_index);
            board_->removeItem(m);
            new_pit->AddMarble(m);
            board_->addItem(m);

            std::string text = "moving marble " + std::to_string(i) + " to pit " + std::to_string(new_pit->get_pit_num());
            QString debug(text.c_str());
            qDebug() << debug;

        } else if (i == 13) {
            std::string text = "moving marble " + std::to_string(i) + " to pit " + std::to_string(p->get_pit_num());
            QString debug(text.c_str());
            qDebug() << debug;

            extraMarble = p->get_marble_at(i);
        }

    }
    last_pit_num_ = new_pit->get_pit_num();
    qDebug() << last_pit_num_;
    p->ClearMarbles();

    if (extraMarble != nullptr) {
        p->AddMarble(extraMarble);
    }

    update();
}

/**
  Calculates players scores and updates the labels accordingly
*/
void GameWindow::UpdateStoreLabels() {
    int score1 = 0;
    int store1_num_marbles = board_->get_store1()->get_num_marbles();
    for (int i = 0; i < store1_num_marbles; i++) {
        score1 += board_->get_store1()->get_marble_at(i)->get_points_value();
    }
    int score2 = 0;
    int store2_num_marbles = board_->get_store2()->get_num_marbles();
    for (int i = 0; i < store2_num_marbles; i++) {
        score2 += board_->get_store2()->get_marble_at(i)->get_points_value();
    }
    player1_->SetScore(score1);
    std::string string1 = std::to_string(score1);
    QString s1(string1.c_str());
    ui->store1Label->setText(s1);

    player2_->SetScore(score2);
    std::string string2 = std::to_string(score2);
    QString s2(string2.c_str());
    ui->store2Label->setText(s2);
}

/**
  Checks if all the pits on one side of the board are empty, if so
    all marbles are given to the player who doesn't
    have an empty board and the game ends.
*/
void GameWindow::CheckEmptyPits() {
    int sum1 = 0;
    for (int i = 0; i < 6; i++) {
        Pit* p = board_->get_pit_at(i);
        if (p->get_num_marbles() == 0) {
            sum1 += 1;
        }
    }
    int sum2 = 0;
    for (int i = 7; i < 13; i++) {
        Pit* p = board_->get_pit_at(i);
        if (p->get_num_marbles() == 0) {
            sum2 += 1;
        }
    }
    if (sum1 >= 6) {
        SetAlertText("GAME OVER! Player 2 is stealing all the marbles!");
        delay(2000);
        for (int i = 7; i < 13; i++) {
            Pit* p = board_->get_pit_at(i);
            Store *store2 = board_->get_store2();
            int num_marbles = p->get_num_marbles();
            if (num_marbles > 0) {
                for (int i = 0; i < num_marbles; i++) {
                    Marble *m = p->get_marble_at(i);
                    board_->removeItem(m);
                    store2->AddMarble(m);
                    board_->addItem(m);
                }
            }
            p->ClearMarbles();
            update();
        }
        game_over_ = true;
    } else if (sum2 >= 6) {
        SetAlertText("GAME OVER! Player 1 is stealing all the marbles!");
        delay(2000);
        for (int i = 0; i < 6; i++) {
            Pit* p = board_->get_pit_at(i);
            Store *store1 = board_->get_store1();
            int num_marbles = p->get_num_marbles();
            if (num_marbles > 0) {
                for (int i = 0; i < num_marbles; i++) {
                    Marble *m = p->get_marble_at(i);
                    board_->removeItem(m);
                    store1->AddMarble(m);
                    board_->addItem(m);
                }
            }
            p->ClearMarbles();
            update();
        }
        game_over_ = true;
    }

}

/**
  Checks the winner of the game after the game ends
*/
void GameWindow::CheckWinner() {
    if (game_over_) {
        if (player1_->get_score() > player2_->get_score()) {
            SetAlertText("Player 1 WINS!!");
            qDebug() << "Player 1 wins";
        } else {
            SetAlertText("Player 2 WINS!!");
            qDebug() << "Player 2 wins";
        }
    }
}

/**
  Steals marbles from one pit and transfers them to another

  @param stealFrom Pit to steal the marbles from
  @param transferTo Pit to transfer the stolen marbles to
  @param special Indicates whether or not this is a special
                    marble steal where one marble is upgraded to a special marble
*/
void GameWindow::StealMarbles(Pit *stealFrom, Pit *transferTo, bool special) {
    int num_marbles = stealFrom->get_num_marbles();
    if (num_marbles > 0) {
        for (int i = 0; i < num_marbles; i++) {
            Marble *m = stealFrom->get_marble_at(i);
            if (i == num_marbles-1 && special) {
                delete m;
                m = MarbleFactory::GetSpecialMarble(transferTo, QColor(255, 0, 0, 175));
            }
            board_->removeItem(m);
            transferTo->AddMarble(m);
            board_->addItem(m);
        }
    }
    stealFrom->ClearMarbles();
    update();
}

/**
  Checks what pit the last marble was distributed to in order to steal marbles
*/
void GameWindow::CheckMarbleLastPit() {
    if (last_pit_num_ != -1 && last_pit_num_ != -2) {
        Pit *transferTo = nullptr;
        Pit *stealFrom = nullptr;
        if (last_pit_num_ == 5 && curr_player_ == player1_) {
            transferTo = board_->get_player1_pit_at(4);
            stealFrom = board_->get_player2_pit_at(4);
            if (stealFrom->get_num_marbles() > 0) {
                SetAlertText("Player 1 is stealing marbles and one has been upgraded to special status!");
                delay(1500);
                StealMarbles(stealFrom, transferTo, true);
                delay(1000);
            }

        } else if (last_pit_num_ == 11 && curr_player_ == player2_) {
            transferTo = board_->get_player2_pit_at(1);
            stealFrom = board_->get_player1_pit_at(1);
            if (stealFrom->get_num_marbles() > 0 && stealFrom->get_num_marbles() > 0) {
                SetAlertText("Player 2 is stealing marbles and one has been upgraded to special status!");
                delay(1500);
                StealMarbles(stealFrom, transferTo, true);
                delay(1000);
            }
        } else if (last_pit_num_ >= 1 && last_pit_num_ <= 6  && curr_player_ == player1_) {
            transferTo = board_->get_player1_pit_at(last_pit_num_-1);
            stealFrom = board_->get_player2_pit_at(last_pit_num_-1);
            if (transferTo->get_num_marbles() == 1 && stealFrom->get_num_marbles() > 0) {
                SetAlertText("Player 1 is stealing Player 2's marbles!");
                delay(1500);
                StealMarbles(stealFrom, transferTo, false);
                delay(1000);
            }
        } else if (last_pit_num_ >= 7 && last_pit_num_ <= 12  && curr_player_ == player2_) {
            transferTo = board_->get_player2_pit_at((last_pit_num_-12)*(-1));
            stealFrom = board_->get_player1_pit_at((last_pit_num_-12)*(-1));
            if (transferTo->get_num_marbles() == 1 && stealFrom->get_num_marbles() > 0) {
                SetAlertText("Player 2 is stealing Player 1's marbles!");
                delay(1500);
                StealMarbles(stealFrom, transferTo, false);
                delay(1000);
            }
        }

    }

}

/**
  Called when a player clicks on one of their pits, most of the game occurs here

  @param p The pit selected
*/
void GameWindow::PitSelectedSlot(Pit *p) {
    if (game_started_ && p->get_player_num() == curr_player_->get_player_num() && p->get_num_marbles() > 0 && !on_delay_) {
        std::string text = "pit " + std::to_string(p->get_pit_num()) + " was clicked";
        QString debug(text.c_str());
        qDebug() << debug;

        DistributeMarblesFrom(p);
        CheckMarbleLastPit();
        CheckEmptyPits();
        UpdateStoreLabels();
        CheckWinner();

        if (!game_over_) {
            if (last_pit_num_ == -1 && curr_player_ == player1_) {
                SetAlertText("Player 1 goes again!");
            } else if (last_pit_num_ == -2 && curr_player_ == player2_) {
                SetAlertText("Player 2 goes again!");
            } else {
                SwitchPlayer();
            }
        }
    }
}

/**
  Called when Start Game button is clicked
*/
void GameWindow::on_startGame_clicked() {
    ui->startGame->setEnabled(false);
    ui->endGame->show();
    ui->alertLabel->show();
    ui->store1Label->show();
    ui->store2Label->show();
    ui->instructionsFrame->hide();
    SetAlertText("Player 1's turn!");
    HandoutMarbles();
    game_started_ = true;
}

/**
  Called when End Game button is clicked
*/
void GameWindow::on_endGame_clicked() {
    std::string text = "store 1: " + std::to_string(board_->get_store1()->get_num_marbles())
            + " - store 2: " + std::to_string(board_->get_store2()->get_num_marbles());
    QString debug(text.c_str());
    qDebug() << debug;
    delete board_;
    delete player1_;
    delete player2_;
    MakeBoard();
}

