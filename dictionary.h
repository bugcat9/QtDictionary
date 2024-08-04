#ifndef DICTIONARY_H
#define DICTIONARY_H
#include"rbtree.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QStringList>
class Dictionary
{
public:
    //构造和析构函数
    Dictionary(QString path);
    ~Dictionary();

    bool insert(QString Englishword,QString Chineseword);   //插入单词
    void insertFile(QString path);                          //插入文本文件
    bool remove(QString Englishword);                       //删除单词
    bool update(QString Englishword,QString Chineseword);   //修改单词
    QString Find(QString Englishword);                      //寻找单词

    void setWords();                                        //得到英文单词、中文单词集合，利用了中序遍历
    QStringList Englishwords;
    QStringList Chinesewords;
protected:
private:
    RBTree *DicTree;   //红黑树，字典需要用到
    QString savePath;   //最后单词存储路径

};

#endif // DICTIONARY_H
