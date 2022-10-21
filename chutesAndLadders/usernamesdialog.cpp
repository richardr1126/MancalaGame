#include "usernamesdialog.h"
#include "ui_usernamesdialog.h"
#include <QLabel>
#include <QTextEdit>

UsernamesDialog::UsernamesDialog(QWidget *parent, int num_players) :
    QDialog(parent),
    ui(new Ui::UsernamesDialog)
{
    ui->setupUi(this);
    num_players_=num_players;

    for (int i = 1; i <= num_players_; i++) {
        std::string pt_label = "Player: " + std::to_string(i);
        QLabel *pt = new QLabel(pt_label.c_str());
        pt->setParent(this);
        pt->setGeometry(40, i*50, 60, 30);

        QTextEdit *qet_x = new QTextEdit();
        qet_x->setGeometry(100, i*50, 150, 30);
        qet_x->setParent(this);
        std::string pt_x_qet = "Player_"+std::to_string(i);
        qet_x->setObjectName(pt_x_qet.c_str());
    }
}

UsernamesDialog::~UsernamesDialog()
{
    delete ui;
}

void UsernamesDialog::on_startGameButton_clicked()
{
    for (int i = 1; i <= num_players_; i++) {
        std::string username_qet = "Player_"+std::to_string(i);
        std::string username;
        QTextEdit *username_text = findChild<QTextEdit*>(username_qet.c_str());
        if (username_text) {
            username = username_text->toPlainText().toStdString();
        } else {
            qDebug() << "Widget not found!";
        }
        usernames_.push_back(username);
    }
    this->close();
}

