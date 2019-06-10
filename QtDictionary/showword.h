#ifndef SHOWWORD_H
#define SHOWWORD_H

#include <QWidget>


namespace Ui {
class ShowWord;
}

class ShowWord : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWord(QWidget *parent = 0);
    ~ShowWord();
     void display(QString e,QString c);
signals:
     void SpeakEnglis(QString e);
private slots:
     void on_pushButton_clicked();

private:

    Ui::ShowWord *ui;
};

#endif // SHOWWORD_H
