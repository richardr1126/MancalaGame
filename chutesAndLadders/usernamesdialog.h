#ifndef USERNAMESDIALOG_H
#define USERNAMESDIALOG_H

#include <QDialog>

namespace Ui {
class UsernamesDialog;
}

class UsernamesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsernamesDialog(QWidget *parent = nullptr, int num_players=2);
    ~UsernamesDialog();

    std::vector<std::string> get_usernames() {return usernames_;};

private slots:
    void on_startGameButton_clicked();

private:
    Ui::UsernamesDialog *ui;
    int num_players_;
    std::vector<std::string> usernames_;
};

#endif // USERNAMESDIALOG_H
