#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include <QTime>
#include<QFileDialog>
#include<QMessageBox>
#include<QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString appDirPath = QCoreApplication::applicationDirPath()+ "/txt/output_utf8_file.txt";
    qDebug()<<appDirPath;
    ui->setupUi(this);
    this->setWindowTitle("电子词典");
    //2010年大学英语四级词汇.txt作为输入和保存的文本,output_utf8_file是它utf8版本
    myDictionary=new Dictionary(appDirPath);
    completer=new QCompleter(myDictionary->Englishwords,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);//设置大小写不敏感
    ui->lineEditinPut->setCompleter(completer);     //实现模糊搜索
    group=new QButtonGroup(this);
    group->addButton(ui->checkBox,1);
    group->addButton(ui->checkBox_2,2);
    group->addButton(ui->checkBox_3,3);
    wordWidget=new ShowWord;
    Textspeak=new QTextToSpeech(this);  //发声音，用于读单词

    //接受单词详细界面传来的英文单词，进行读
    connect(wordWidget,&ShowWord::SpeakEnglis,
            [=](QString e)
    {
        Textspeak->say(e);
    }
            );

    ui->textEditMean->setReadOnly(true);
}

MainWindow::~MainWindow()
{

    delete ui;
    delete myDictionary;
}

//设置界面的ok，用于删除、增加单词
void MainWindow::on_buttonBox_accepted()
{
 //qDebug()<< group->checkedId();
    if(group->checkedId()==1)       //第一种情况插入单词
    {

        QString e=ui->textEditEnglish->toPlainText();
        QString c=ui->textEditChinese->toPlainText();
        QString path=ui->lineEditFile->text();
        if(!path.isEmpty())//如果路径不为空执行文本插入
        {
            myDictionary->insertFile(path);
            QMessageBox::information(this,"提示","路径不能为空");
        }

        if(myDictionary->insert(e,c))
        {
            QMessageBox::information(this,"提示","插入成功");
        }
        else
            QMessageBox::information(this,"提示","插入失败");
    }
    else if (group->checkedId()==2) //第二种情况删除单词
    {
        QString e=ui->textEditEnglish->toPlainText();
        if(myDictionary->remove(e))
            QMessageBox::information(this,"提示","删除成功");
        else
            QMessageBox::information(this,"提示","删除失败");
    }
    else if (group->checkedId()==3) //第三种情况修改单词
    {
        QString e=ui->textEditEnglish->toPlainText();
        QString c=ui->textEditChinese->toPlainText();
       if(myDictionary->update(e,c))
           QMessageBox::information(this,"提示","更新成功");
       else
       {
           QMessageBox::information(this,"提示","更新成功");
       }
    }
}

//设置界面的cancel
void MainWindow::on_buttonBox_rejected()
{
    ui->stackedWidget->setCurrentIndex(0);//跳回查询界面
}

//逐条查找，可以查找有单词
void MainWindow::on_actionall_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->listWidget->addItems(myDictionary->Englishwords);
}

//查找界面
void MainWindow::on_actionFind_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEditinPut->clear();
    ui->textEditMean->clear();
}

//按下查找按钮
void MainWindow::on_ButtonFind_clicked()
{
   QString e=ui->lineEditinPut->text();
   ui->textEditMean->clear();
   QString c=myDictionary->Find(e);
   if(!c.isEmpty())
   {
       ui->textEditMean->setText(c);
       if(history.contains(e))
       {
           history.removeAll(e);
       }
       history.append(e);
   }else
       QMessageBox::information(this,"提示","词库无此单词");

}
//查看历史
void MainWindow::on_actionHistory_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->listWidgetHistory->clear();
    ui->listWidgetHistory->addItems(history);
}
//设置，用于增加、删除、更新单词
void MainWindow::on_actionset_triggered()
{
     ui->stackedWidget->setCurrentIndex(3);
}
//读单词
void MainWindow::on_ButtonRead_clicked()
{
     QString e=ui->lineEditinPut->text();

     Textspeak->say(e);
}
//背单词
void MainWindow::on_actionRemember_triggered()
{
    ui->lineEditHint->clear();
    ui->lineEditSure->clear();
    ui->stackedWidget->setCurrentIndex(4);
    QTime time;
    time= QTime::currentTime();
    srand(time.msec()+time.second()*1000);
    i = rand() % myDictionary->Englishwords.size();    //产生的随机数
    QString e=myDictionary->Englishwords[i];
    qDebug()<<e;
    int j= rand()%e.size();
    QString s="_";
    e.replace(j,1,s);
    ui->labelShow->setText(e);

}
//背单词填写好的确定
void MainWindow::on_ButtonSure_clicked()
{
    QString answer=ui->lineEditSure->text();
    if(answer==myDictionary->Englishwords[i])
    {
      //  qDebug()<<"正确";

        QMediaPlayer *myPlayer= new QMediaPlayer;
        myPlayer->setSource(QUrl::fromLocalFile("music/正确.mp3"));
        myPlayer->play();
        this->on_actionRemember_triggered();
    }else
    {
        QMediaPlayer *myPlayer= new QMediaPlayer;
        myPlayer->setSource(QUrl::fromLocalFile("music/错误.mp3"));
        myPlayer->play();
    }

}
//提示中文
void MainWindow::on_Buttonhint_clicked()
{
    QString c=myDictionary->Chinesewords[i];
    ui->lineEditHint->setText(c);
}
//对要背的英语单词进行读
void MainWindow::on_ButtonReadHint_clicked()
{
    QString e=myDictionary->Englishwords[i];
    Textspeak->say(e);
}

//逐条浏览时点出单词的详细界面
void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
    QString e=item->text();
    QString c=myDictionary->Find(e);
    wordWidget->display(e,c);
    wordWidget->show();
}

//查看历史时点出单词的详细界面
void MainWindow::on_listWidgetHistory_itemPressed(QListWidgetItem *item)
{
    QString e=item->text();
    QString c=myDictionary->Find(e);
    wordWidget->display(e,c);
    wordWidget->show();
}

//设置时进行查看,可以查看单词的主要信息
void MainWindow::on_Button_3_clicked()
{
    QString e=ui->textEditEnglish->toPlainText();
    QString c=myDictionary->Find(e);
    if(!c.isEmpty())
       QMessageBox::information(this,"提示","词库无此单词");
    else
    {
        wordWidget->display(e,c);
        wordWidget->show();
    }
}
//插入时可以通过文本插入
void MainWindow::on_ButtonFile_clicked()
{
  QString  fileName = QFileDialog::getOpenFileName(this,
          tr("Open Image"), "E:/", tr("Text files (*.txt)"));
  //qDebug()<<fileName;
 // myDictionary->insertFile(fileName);
  ui->lineEditFile->setText(fileName);
}
//背单词界面下一个按键
void MainWindow::on_ButtonNext_clicked()
{
    this->on_actionRemember_triggered();
}
