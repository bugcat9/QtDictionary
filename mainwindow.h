#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"dictionary.h"
#include<QCompleter>
#include<QButtonGroup>
#include<QStringList>
#include<QTextToSpeech>
#include<QListWidgetItem>
#include<QMediaPlayer>
#include"showword.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonBox_accepted();//设置中的确定按键，ok

    void on_buttonBox_rejected();//设置中的取消案件，会返回查询界面

    void on_actionall_triggered();//查询所有单词，进行逐条查询

    void on_actionFind_triggered();//用于跳到查询

    void on_ButtonFind_clicked();//填写好英文单词后的的确定，接着会查询

    void on_actionHistory_triggered();//跳转到历史记录界面

    void on_actionset_triggered();//跳转到设置界面

    void on_ButtonRead_clicked();//用于查询界面的发出声音，即读单词

    void on_actionRemember_triggered();//跳转到记单词界面

    void on_ButtonSure_clicked();//用于记单词界面的确定按键

    void on_Buttonhint_clicked();//用于记单词界面的提示按键

    void on_ButtonReadHint_clicked();//记单词中读单词按键

    void on_ButtonNext_clicked();//用于记单词界面选择下一个单词

    void on_listWidget_itemPressed(QListWidgetItem *item);//用于可以在所有单词界面中点击单词就可以查询

    void on_listWidgetHistory_itemPressed(QListWidgetItem *item);//用于可以在历史记录界面点单词就可以查询

    void on_Button_3_clicked();//用于设置界面查看单词

    void on_ButtonFile_clicked();//用于设置界面选择文本



private:
    Ui::MainWindow *ui;
    Dictionary *myDictionary;   //字典类
    QCompleter *completer;      //自动补全，实现模糊查询
    QButtonGroup *group;        //用于单选框
    QStringList  history;       //用于历史记录
    QTextToSpeech *Textspeak;   //用于发声音
    int i;//用于背单词
    ShowWord *wordWidget;       //显示详细单词用，在所有单词，历史界面中都有用

};

#endif // MAINWINDOW_H
