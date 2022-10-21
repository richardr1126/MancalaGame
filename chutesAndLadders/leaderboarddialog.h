#ifndef LEADERBOARDDIALOG_H
#define LEADERBOARDDIALOG_H

#include <QDialog>

namespace Ui {
class LeaderboardDialog;
}

class LeaderboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LeaderboardDialog(QWidget *parent = nullptr);
    ~LeaderboardDialog();
    void ReadFile();


private slots:
    void on_pushButton_clicked();

private:
    Ui::LeaderboardDialog *ui;
    int total_players_;
};

#endif // LEADERBOARDDIALOG_H
