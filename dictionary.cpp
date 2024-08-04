#include "dictionary.h"
#include<iostream>

//字典的数据从path中读取，也就是说字典主要的数据都存在path对应的txt中，
//其后加入的单词也都会存储在里面，删除单词也将删除掉里面的单词
//其实最好的办法还是使用数据库
Dictionary::Dictionary(QString path)
{

    QFile file(path);
    savePath=path;
    DicTree=new RBTree;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString English;
    QString Chinese;

    while(!in.atEnd())
    {

       English= in.readLine();
       Chinese=in.readLine();
       Englishwords.append(English);
       Chinesewords.append(Chinese);
       DicTree->insert(English,Chinese);

    }
    file.close();

}
//析构函数会对单词进行储存，储存在读进来的文本当中
Dictionary::~Dictionary()
{
    //写入方式有待改进
    this->setWords();
    QFile file(savePath);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    QString e;
    QString c;
    QByteArray a;
    for(int i=0;i<Englishwords.size();i++)
    {

      out<<Englishwords[i];
      out<<Qt::endl;
      out<<Chinesewords[i];
      out<<Qt::endl;
    }
    file.close();
    delete DicTree;
}

//插入函数，一个通过单个单词插入，一个通过文件插入,需要考虑重复插入
//需要注意的是出入进去的单词要最终写在txt上
bool Dictionary::insert(QString Englishword, QString Chineseword)
{
   if(DicTree->insert(Englishword,Chineseword))
       return true;
   return false;
}
//文本插入
void Dictionary::insertFile(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString English;
    QString Chinese;

    while(!in.atEnd())
    {

       English= in.readLine();
       Chinese=in.readLine();
       Englishwords.append(English);
       Chinesewords.append(Chinese);
       DicTree->insert(English,Chinese);

    }
    file.close();
}
//删除单词
bool Dictionary::remove(QString Englishword)
{
    if(DicTree->remove(Englishword))
        return true;
    return false;
}
//更新单词
bool Dictionary::update(QString Englishword, QString Chineseword)
{
     RBTreeNode *node=DicTree->iterativeSearch(Englishword);
     if(node==NULL)
       return false;

    node->ChineseWord=Chineseword;
    return true;
}
//查询
QString Dictionary::Find(QString Englishword)
{
    RBTreeNode *node=DicTree->iterativeSearch(Englishword);
    if(node==NULL)
      return NULL;
    else
        return node->ChineseWord;
}
//得到英文和中文集合
void Dictionary::setWords()
{
    Englishwords.clear();
    Chinesewords.clear();
    DicTree->inorder(Englishwords,Chinesewords);
}














