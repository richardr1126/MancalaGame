#include "numplayersdiaglog.h"
#include "ui_numplayersdiaglog.h"

NumPlayersDiaglog::NumPlayersDiaglog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumPlayersDiaglog)
{
    ui->setupUi(this);
    num_players_ = 2;
}

NumPlayersDiaglog::~NumPlayersDiaglog()
{
    delete ui;
}

void NumPlayersDiaglog::on_submitButton_clicked()
{
    num_players_ = ui->numPlayersBox->value();
    close();
}

