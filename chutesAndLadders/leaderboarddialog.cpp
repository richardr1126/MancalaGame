#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QString>
#include <QLabel>
#include <algorithm>
#include "leaderboarddialog.h"
#include "ui_leaderboarddialog.h"

using namespace std;

struct Stat {
    string name;
    int numWins;
    int numGames;
    double winPercentage;

    bool operator<(const Stat& a) const {
        return winPercentage > a.winPercentage;
    }
};



LeaderboardDialog::LeaderboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderboardDialog)
{
    ui->setupUi(this);
    qDebug() << "hello";
    ReadFile();
}

LeaderboardDialog::~LeaderboardDialog()
{
    delete ui;
}

void LeaderboardDialog::on_pushButton_clicked()
{
    close();
}

void LeaderboardDialog::ReadFile() {
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
    sort(stats.begin(), stats.end());
    int size = stats.size();
    for (int i = 1; i <= size; i++) {
        string username = "Player: " + stats[i-1].name;
        QLabel *username_label = new QLabel(username.c_str());
        username_label->setParent(this);
        username_label->setGeometry(40, i*50, 150, 30);

        string wins = "Wins: "+to_string(stats[i-1].numWins);
        QLabel *wins_label = new QLabel(wins.c_str());
        wins_label->setParent(this);
        wins_label->setGeometry(200, i*50, 100, 30);

        string games = "Games Played: "+to_string(stats[i-1].numGames);
        QLabel *games_label = new QLabel(games.c_str());
        games_label->setParent(this);
        games_label->setGeometry(300, i*50, 150, 30);

        string percent_wins = "Win Percentage: "+to_string(stats[i-1].winPercentage)+"%";
        QLabel *percent_wins_label = new QLabel(percent_wins.c_str());
        percent_wins_label->setParent(this);
        percent_wins_label->setGeometry(450, i*50, 200, 30);
    }

}
