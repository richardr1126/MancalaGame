#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QTime>
#include <QTimer>
#include <chrono>
#include <thread>
#include <QtWidgets>
#include <QFile>
#include <QStringList>
#include <QString>
#include <fstream>
#include <sstream>
#include <iostream>

#include "gamewindow.h"
#include "ui_gamewindow.h"

struct Stat {
    string name;
    int numWins;
    int numGames;
    double winPercentage;

    bool operator<(const Stat& a) const {
        return winPercentage > a.winPercentage;
    }
};

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    npd = new NumPlayersDiaglog;
    npd->setModal(true);
    npd->exec();
    num_players_ = npd->get_num_players();

    ud = new UsernamesDialog(nullptr, npd->get_num_players());
    ud->setModal(true);
    ud->exec();

    players_removed_ = 0;
    time_ = 20;
    player_is_moving_ = false;

    game_started_ = false;

    ui->currentPlayerLabel->hide();
    ui->timeLeftLabel->hide();
    ui->endGameButton->hide();
    ui->newGameButton->hide();
    ui->undoButton->hide();
    ui->rerollButton->hide();
    ui->rollButton->hide();
    ui->moveButton->hide();
    ui->quitGameButton->hide();
    ui->diceResultLabel->hide();
    ui->alertLabel->hide();

    MakeGame();
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::WritePlayerInformation(Player* winner) {
    QFile file("/Users/richardroberson/Documents/QtCreator/chutesAndLadders/leaderboard.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QStringList wordList;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        wordList.append(line.split(',').at(0));
        wordList.append(line.split(',').at(1));
        wordList.append(line.split(',').at(2));

    }

    vector<Stat> stats;
    for (int i = 0; i < wordList.size(); i+=3) {
        Stat stat;
        stat.name = wordList.at(i).toLocal8Bit().constData();
        stat.numWins = stoi(wordList.at(i+1).toLocal8Bit().constData());
        stat.numGames = stoi(wordList.at(i+2).toLocal8Bit().constData());
        stat.winPercentage = (stod(wordList.at(i+1).toLocal8Bit().constData())/stod(wordList.at(i+2).toLocal8Bit().constData()))*100;
        stats.push_back(stat);
    }
    file.close();

    int size = stats.size();
    bool winnerAdded = false;
    bool loserAdded = false;

    for (int i = 0; (i < size); i++) {
        for (int j = 0; j < num_players_; j++) {
            if (players_[j]->get_username()==stats[i].name && players_[j]==winner) {
                stats[i].numWins++;
                stats[i].numGames++;
                stats[i].winPercentage = double(stats[i].numWins)/double(stats[i].numGames)*100;
                winnerAdded = true;
            } else if (players_[j]->get_username()==stats[i].name) {
                stats[i].numGames++;
                stats[i].winPercentage = double(stats[i].numWins)/double(stats[i].numGames)*100;
                loserAdded = true;
            }
        }
    }

    for (int i = 0; (i < num_players_); i++) {
        if (players_[i]==winner && !winnerAdded) {
            Stat stat;
            stat.name = winner->get_username();
            stat.numWins = 1;
            stat.numGames = 1;
            stat.winPercentage = 100.0;
            stats.push_back(stat);
        } else if (!loserAdded) {
            Stat stat;
            stat.name = players_[i]->get_username();
            stat.numWins = 0;
            stat.numGames = 1;
            stat.winPercentage = 0;
            stats.push_back(stat);
        }
    }

    sort(stats.begin(), stats.end());
    size = stats.size();
    file.resize(0);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream( &file );
        for (int i = 0; i < size; i++) {
            QString name(stats[i].name.c_str());
            QString wins(to_string(stats[i].numWins).c_str());
            QString games(to_string(stats[i].numGames).c_str());
            stream << name <<  "," << wins << "," << games << Qt::endl;
        }
    }
    file.close();
}

void GameWindow::on_startGameButton_clicked() {
    if (!game_started_) {
        QString username(curr_player_->get_username().c_str());
        ui->currentPlayerLabel->setText(username);
        ui->currentPlayerLabel->setStyleSheet("color: "+curr_player_->get_player_color().name());
        ui->currentPlayerLabel->show();
        ui->timeLeftLabel->show();
        ui->diceResultLabel->show();

        ui->endGameButton->show();
        ui->undoButton->show();
        ui->rerollButton->show();
        ui->rollButton->show();
        ui->moveButton->show();
        ui->quitGameButton->show();
        ui->newGameButton->show();

        ui->moveButton->setEnabled(false);
        ui->undoButton->setEnabled(false);
        ui->rerollButton->setEnabled(false);
        ui->startGameButton->setEnabled(false);

        timer_ = new QTimer(this);
        connect(timer_, &QTimer::timeout, this, QOverload<>::of(&GameWindow::IncrementTimer));
        timer_->start(1000);
    }
}

void GameWindow::MakeGame() {
    for (int i = 0; i < num_players_; i++) {
        Player* player = new Player(ud->get_usernames().at(i));
        player->SetPlayerNum(i);
        players_.push_back(player);
    }

    curr_player_ = players_.at(0);

    QGraphicsView *starting_view = ui->pawnContainer;
    starting_area_scene_ = new QGraphicsScene;
    starting_view->setScene(starting_area_scene_);

    int starting_width = starting_view->frameSize().width()-8;
    int starting_height = starting_view->frameSize().height()-8;
    starting_view->setSceneRect(0, 0, starting_width, starting_height);

    int starting_x_mid = starting_width/2;
    int starting_y_mid = starting_height/2;

    int t_half_width = 50/2;

    int t1_x_adj = (-25 + starting_x_mid) - t_half_width;
    int t1_y_adj = (starting_y_mid - -25) - t_half_width;
    Tile *t1 = new Tile(t1_x_adj, t1_y_adj);
    starting_area_scene_->addItem(t1);
    players_[0]->get_pawn()->SetTile(t1);
    starting_area_scene_->addItem(players_[0]->get_pawn());

    int t2_x_adj = (25 + starting_x_mid) - t_half_width;
    int t2_y_adj = (starting_y_mid - -25) - t_half_width;
    Tile *t2 = new Tile(t2_x_adj, t2_y_adj);
    starting_area_scene_->addItem(t2);
    players_[1]->get_pawn()->SetTile(t2);
    starting_area_scene_->addItem(players_[1]->get_pawn());

    int t3_x_adj = (-25 + starting_x_mid) - t_half_width;
    int t3_y_adj = (starting_y_mid - 25) - t_half_width;
    Tile *t3 = new Tile(t3_x_adj, t3_y_adj);
    starting_area_scene_->addItem(t3);
    if (num_players_ > 2) {
        players_[2]->get_pawn()->SetTile(t3);
        starting_area_scene_->addItem(players_[2]->get_pawn());
    }

    int t4_x_adj = (25 + starting_x_mid) - t_half_width;
    int t4_y_adj = (starting_y_mid - 25) - t_half_width;
    Tile *t4 = new Tile(t4_x_adj, t4_y_adj);
    starting_area_scene_->addItem(t4);
    if (num_players_ > 3) {
        players_[3]->get_pawn()->SetTile(t4);
        starting_area_scene_->addItem(players_[3]->get_pawn());
    }

    QGraphicsView *view = ui->board;
    board_ = new Board;
    view->setScene(board_);

    int width = view->frameSize().width()-8;
    int height = view->frameSize().height()-8;
    view->setSceneRect(0, 0, width, height);

    int x_mid = width/2;
    int y_mid = height/2;

    for (int y_at = 0; y_at < 10; y_at++) {
        for (int x_at = 0; x_at < 10; x_at++) {
            int x = (-225+(x_at*50));
            int y = (-225+(y_at*50));
            int x_adj = (x + x_mid) - t_half_width;
            int y_adj = (y_mid - y) - t_half_width;
            Tile *t = new Tile(x_adj, y_adj);
            board_->SetTileAt(x_at, y_at, t);
            board_->addItem(t);
        }
    }
    board_->MakeVector();

    for (int i = 0; i < 6; i++) {
        int starting_tile_num = QRandomGenerator::global()->generate() % 100;
        for (int j = 0; j < 100; j++) {
            if (board_->get_tiles().at(starting_tile_num)->get_has_shortcut()) {
                starting_tile_num = QRandomGenerator::global()->generate() % 100;
            } else {
                break;
            }
        }
        int ending_tile_num = (QRandomGenerator::global()->generate() % (100-starting_tile_num)) + starting_tile_num;
        for (int z = 0; z < 100; z++) {
            if (board_->get_tiles().at(ending_tile_num)->get_has_shortcut() || ending_tile_num==starting_tile_num) {
                ending_tile_num = (QRandomGenerator::global()->generate() % (100-starting_tile_num)) + starting_tile_num;
            } else {
                break;
            }
        }

        Tile* chuteTop;
        Tile* chuteEnd;
        if (starting_tile_num > ending_tile_num) {
            chuteTop = board_->get_tiles().at(starting_tile_num);
            chuteEnd = board_->get_tiles().at(ending_tile_num);
        } else {
            chuteTop = board_->get_tiles().at(ending_tile_num);
            chuteEnd = board_->get_tiles().at(starting_tile_num);
        }

        QPen pen;
        pen.setWidth(4);
        pen.setBrush(QColor("purple"));

        board_->addLine(chuteTop->get_x()+25, chuteTop->get_y()+25, chuteEnd->get_x()+25, chuteEnd->get_y()+25, pen);

        chuteTop->SetHasShortcut(true);
        chuteTop->SetShortcutNum(chuteEnd->get_tile_num());
        chuteEnd->SetHasShortcut(true);
    }
    for (int i = 0; i < 7; i++) {
        int starting_tile_num = QRandomGenerator::global()->generate() % (99)+1;
        for (int j = 0; j < 100; j++) {
            if (board_->get_tiles().at(starting_tile_num)->get_has_shortcut()) {
                starting_tile_num = QRandomGenerator::global()->generate() % (99)+1;
            } else {
                break;
            }
        }
        int ending_tile_num = (QRandomGenerator::global()->generate() % (99-starting_tile_num)) + (starting_tile_num+1);
        for (int z = 0; z < 100; z++) {
            if (board_->get_tiles().at(ending_tile_num)->get_has_shortcut() || ending_tile_num==starting_tile_num) {
                ending_tile_num = (QRandomGenerator::global()->generate() % (99-starting_tile_num)) + (starting_tile_num+1);
            } else {
                break;
            }
        }

        Tile* ladderBegin;
        Tile* ladderEnd;
        if (starting_tile_num > ending_tile_num) {
            ladderEnd = board_->get_tiles().at(starting_tile_num);
            ladderBegin = board_->get_tiles().at(ending_tile_num);
        } else {
            ladderEnd = board_->get_tiles().at(ending_tile_num);
            ladderBegin = board_->get_tiles().at(starting_tile_num);
        }

        QPen pen;
        pen.setStyle(Qt::DashDotLine);
        pen.setWidth(4);
        pen.setBrush(Qt::green);

        board_->addLine(ladderBegin->get_x()+25, ladderBegin->get_y()+25, ladderEnd->get_x()+25, ladderEnd->get_y()+25, pen);

        ladderBegin->SetHasShortcut(true);
        ladderBegin->SetShortcutNum(ladderEnd->get_tile_num());
        ladderEnd->SetHasShortcut(true);
    }
}

void GameWindow::ResetGame() {
    time_ = 20;

    player_is_moving_ = false;
    game_started_ = false;
    ui->currentPlayerLabel->hide();
    ui->timeLeftLabel->hide();
    ui->endGameButton->hide();
    ui->undoButton->hide();
    ui->rerollButton->hide();
    ui->rollButton->hide();
    ui->moveButton->hide();
    ui->quitGameButton->hide();
    ui->diceResultLabel->hide();
    ui->alertLabel->hide();
    ui->newGameButton->hide();
    ui->startGameButton->setEnabled(true);

    players_.clear();
    num_players_+=players_removed_;

    MakeGame();

    timer_->stop();
    update();
}

void GameWindow::CheckWin() {
    int tileNum = curr_player_->get_pawn()->get_curr_tile()->get_tile_num();
    if (tileNum == 99) {
        std::string alert_string = curr_player_->get_username()+" won!";
        QString alert(alert_string.c_str());
        ui->alertLabel->setText(alert);
        ui->alertLabel->show();
        WritePlayerInformation(curr_player_);
        delay(5000);
        ResetGame();
    }
}

void GameWindow::IncrementTimer() {
    if(time_ > 0 && !player_is_moving_) {
        std::string time = "Time Left: "+std::to_string(time_);
        QString timer(time.c_str());
        ui->timeLeftLabel->setText(timer);
        time_--;
    } else if (time_ <= 0 && !player_is_moving_) {
        std::string alert_string = curr_player_->get_username()+" turn skipped!";
        QString alert(alert_string.c_str());
        ui->alertLabel->setText(alert);
        ui->alertLabel->show();
        delay(1500);
        ui->alertLabel->hide();
        SwitchPlayer();
    }
}

void GameWindow::SwitchPlayer() {
    Player *next_player;

    int next_index = curr_player_->get_player_num()+1;
    if (next_index > num_players_-1) {
        next_player = players_.at(0);

        qDebug() << "switching to player 0";
    } else {
        next_player = players_.at(next_index);

        qDebug() << "switching to next player";
    }

    curr_player_ = next_player;
    QString username(curr_player_->get_username().c_str());
    ui->currentPlayerLabel->setText(username);
    ui->currentPlayerLabel->setStyleSheet("color: "+curr_player_->get_player_color().name());
    ui->rollButton->setEnabled(true);
    ui->undoButton->setEnabled(true);
    time_ = 20;
}

void GameWindow::on_endGameButton_clicked() {
    ResetGame();
}

void GameWindow::on_undoButton_clicked() {

    if (curr_player_->get_num_undos() > 0 && curr_player_->get_prev_size() > 0) {
        curr_player_->UndoMove();

        Tile* prev_tile = curr_player_->get_prev_positions().at(curr_player_->get_prev_size()-1);

        curr_player_->get_pawn()->SetTile(prev_tile);
        curr_player_->get_prev_positions().pop_back();
        curr_player_->DecreasePrevSize();

        update();
        delay(200);
        SwitchPlayer();
    }

}

void GameWindow::on_rerollButton_clicked() {
    if (curr_player_->get_num_rerolls() > 0) {
        int diceResult = curr_player_->RerollDice();
        QString qs(std::to_string(diceResult).c_str());
        ui->diceResultLabel->setText(qs);
        curr_player_->SetDiceResult(diceResult);
    }
}

void GameWindow::on_rollButton_clicked() {
    int diceResult = curr_player_->RollDice();
    QString qs(std::to_string(diceResult).c_str());
    ui->diceResultLabel->setText(qs);
    curr_player_->SetDiceResult(diceResult);
    ui->rollButton->setEnabled(false);
    ui->moveButton->setEnabled(true);
    if (curr_player_->get_num_rerolls() > 0) {
        ui->rerollButton->setEnabled(true);
    }
}

void GameWindow::on_quitGameButton_clicked() {
    num_players_--;
    players_removed_++;
    Player *player = curr_player_;
    if (num_players_ >= 2) {
        SwitchPlayer();
        board_->removeItem(player->get_pawn());
        starting_area_scene_->removeItem(player->get_pawn());
        players_.erase(players_.begin()+player->get_player_num());
        for (int i = 0; i < num_players_; i++) {
            players_[i]->SetPlayerNum(i);
        }
        update();
    } else {
        ResetGame();
    }
}

void GameWindow::on_moveButton_clicked() {
    player_is_moving_ = true;
    ui->moveButton->setEnabled(false);
    ui->undoButton->setEnabled(false);
    ui->rerollButton->setEnabled(false);
    ui->rollButton->setEnabled(false);

    int tile_num = curr_player_->get_pawn()->get_curr_tile()->get_tile_num();

    if (tile_num==999 && curr_player_->get_dice_result() >= 6) {
        starting_area_scene_->removeItem(curr_player_->get_pawn());
        curr_player_->get_pawn()->SetTile(board_->get_tiles().at(0));
        board_->addItem(curr_player_->get_pawn());
        update();
        delay(200);
        curr_player_->SetOnBoard(true);
    } else if (curr_player_->get_on_board()) {
        Tile* prev_position = curr_player_->get_pawn()->get_curr_tile();
        curr_player_->push_back_prev(prev_position);
        curr_player_->IncreasePrevSize();
        for (int i = 0; i < curr_player_->get_dice_result(); i++) {
            Pawn* pawn = curr_player_->get_pawn();
            Tile* curr_tile = pawn->get_curr_tile();
            int tile_num = curr_tile->get_tile_num();
            if (tile_num+1 <= 99) {
                if (board_->get_tiles().at(tile_num+1)->get_shortcut_num() != -999 && i==curr_player_->get_dice_result()-1) {
                    int shortcut_num = board_->get_tiles().at(tile_num+1)->get_shortcut_num();
                    pawn->SetTile(board_->get_tiles().at(shortcut_num));
                } else {
                    pawn->SetTile(board_->get_tiles().at(tile_num+1));
                }
                update();
                delay(200);
            } else {
                CheckWin();
            }
        }
    }
    player_is_moving_ = false;
    SwitchPlayer();
}

void GameWindow::on_leaderboardButton_clicked() {
    leaderboard = new LeaderboardDialog(nullptr);
    leaderboard->setModal(true);
    leaderboard->exec();
}


void GameWindow::on_newGameButton_clicked() {
    npd = new NumPlayersDiaglog;
    npd->setModal(true);
    npd->exec();
    num_players_ = npd->get_num_players();

    ud = new UsernamesDialog(nullptr, npd->get_num_players());
    ud->setModal(true);
    ud->exec();

    ResetGame();
}

