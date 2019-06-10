#ifndef RBTREE_H
#define RBTREE_H
#include<QString>
#include<QStack>
#include<QStringList>
#include<QList>
enum Color_t
{
    COLOR_BLACK,
    COLOR_RED
};


struct RBTreeNode
{
    RBTreeNode(QString data)
    {
        left=NULL;
        right=NULL;
        parent=NULL;
        Color=COLOR_RED;
        EnglishWord=data;
    }
    RBTreeNode *left,*right,*parent;
    Color_t Color;
    QString EnglishWord;    //英语单词
    QString ChineseWord;      //中文意思
};

class RBTree
{

public:
    RBTree();
   ~RBTree();
    // (非递归实现)查找"红黑树"中键值为key的节点
    RBTreeNode* iterativeSearch(QString EnglishWord);
    // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
    RBTreeNode* successor(RBTreeNode*x);
    // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
    RBTreeNode* predecessor(RBTreeNode *x);
    // 将结点(key为节点键值)插入到红黑树中
    bool insert(QString EnglishWord,QString ChinaWord);
    // 删除结点(key为节点键值)
    bool remove(QString EnglishWord);
   // 销毁红黑树
    void destroy();
    //中序遍历得到中英文的组合
    void inorder(QStringList &Englishwords,QStringList &Chinesewords);
protected:
    // 左旋
    void leftRotate(RBTreeNode* x);
    // 右旋
    void rightRotate(RBTreeNode* y);
    // 插入函数
   void insert(RBTreeNode* node);
    // 插入修正函数
    void insertFixup(RBTreeNode* node);
    //删除函数
    void remove(RBTreeNode *node);
    // 删除修正函数
    void removeFixup(RBTreeNode* node,RBTreeNode *parent);

    // (非递归实现)查找"红黑树x"中键值为key的节点
    RBTreeNode* iterativeSearch(RBTreeNode* x, QString EnglishWord) const;
    // 销毁红黑树
     void destroy(RBTreeNode* &tree);

private:
    RBTreeNode *root;       //根节点

};

#endif // RBTREE_H
