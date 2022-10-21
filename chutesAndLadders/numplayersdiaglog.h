#ifndef NUMPLAYERSDIAGLOG_H
#define NUMPLAYERSDIAGLOG_H

#include <QDialog>

namespace Ui {
class NumPlayersDiaglog;
}

class NumPlayersDiaglog : public QDialog
{
    Q_OBJECT

public:
    explicit NumPlayersDiaglog(QWidget *parent = nullptr);
    ~NumPlayersDiaglog();
    int get_num_players() {return num_players_;};

private slots:
    void on_submitButton_clicked();

private:
    Ui::NumPlayersDiaglog *ui;
    int num_players_;
};

#endif // NUMPLAYERSDIAGLOG_H
