#include "showword.h"
#include "ui_showword.h"

ShowWord::ShowWord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWord)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
}

ShowWord::~ShowWord()
{
    delete ui;
}

void ShowWord::display(QString e, QString c)
{

    ui->textEdit->setText(e);
    ui->textEdit_2->setText(c);
}

void ShowWord::on_pushButton_clicked()
{
    QString e=ui->textEdit->toPlainText();
    emit SpeakEnglis(e);
}
