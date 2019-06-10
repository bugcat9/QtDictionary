#include "rbtree.h"

RBTree::RBTree()
{
    root=NULL;
}

RBTree::~RBTree()
{
    this->destroy();
}

//非递归查询
RBTreeNode *RBTree::iterativeSearch(QString EnglishWord)
{
    return   iterativeSearch(root, EnglishWord);
}

RBTreeNode *RBTree::iterativeSearch(RBTreeNode *x, QString EnglishWord) const
{
    while ((x!=NULL) && (x->EnglishWord!=EnglishWord))
      {
          if (EnglishWord < x->EnglishWord)
               x = x->left;
           else
               x = x->right;
      }

      return x;
}

bool RBTree::insert(QString EnglishWord, QString ChinaWord)
{
       RBTreeNode *z=NULL;
       // 如果新建结点失败，则返回。
       if ((z=new RBTreeNode(EnglishWord)) == NULL)
            return false;
       z->ChineseWord=ChinaWord;
       insert(z);
       return true;
}

bool RBTree::remove(QString EnglishWord)
{
       RBTreeNode *node=NULL;
      // 查找key对应的节点(node)，找到的话就删除该节点
     if ((node = iterativeSearch(root, EnglishWord)) == NULL)
             return false;

    remove(node);
    return true;
}

void RBTree::destroy()
{
    this->destroy(root);
}

void RBTree::inorder(QStringList &Englishwords,QStringList &Chinesewords)
{
    QStack<RBTreeNode*> s;
    RBTreeNode *p=root;
    while(p!=NULL||!s.empty())
    {
        while(p!=NULL)
        {
           s.push(p);
           p=p->left;
        }

        if(!s.empty())
        {
           p=s.top();
          //cout<<p->data<<" ";
           Englishwords.append(p->EnglishWord);
           Chinesewords.append(p->ChineseWord);
           s.pop();
           p=p->right;
        }

    }

}

void RBTree::destroy(RBTreeNode *&tree)
{
    if (tree==NULL)
          return ;

    if (tree->left != NULL)
            return destroy(tree->left);
    if (tree->right != NULL)
           return destroy(tree->right);

    delete tree;
    tree=NULL;
}

void RBTree::leftRotate(RBTreeNode *x)
{
        // 设置x的右孩子为y
        RBTreeNode*y = x->right;

        // 将 “y的左孩子” 设为 “x的右孩子”；
        // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
        x->right = y->left;
        if (y->left != NULL)
            y->left->parent = x;

        // 将 “x的父亲” 设为 “y的父亲”
        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
        }
        else
        {
            if (x->parent->left == x)
                x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
            else
                x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        }

        // 将 “x” 设为 “y的左孩子”
        y->left = x;
        // 将 “x的父节点” 设为 “y”
        x->parent = y;
}

void RBTree::rightRotate(RBTreeNode *y)
{
         // 设置x是当前节点的左孩子。
        RBTreeNode *x = y->left;

        // 将 “x的右孩子” 设为 “y的左孩子”；
        // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
        y->left = x->right;
        if (x->right != NULL)
            x->right->parent = y;

        // 将 “y的父亲” 设为 “x的父亲”

        x->parent = y->parent;

        if (y->parent == NULL)
        {
            root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
        }
        else
        {
            if (y == y->parent->right)
                y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
            else
                y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
        }

        // 将 “y” 设为 “x的右孩子”
        x->right = y;

        // 将 “y的父节点” 设为 “x”
        y->parent = x;
}

void RBTree::insert(RBTreeNode *node)
{
    RBTreeNode *y = NULL;
    RBTreeNode *x = root;
        // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
        while (x != NULL)
        {
            y = x;
            if (node->EnglishWord < x->EnglishWord)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y!=NULL)
        {
            if (node->EnglishWord < y->EnglishWord)
                y->left = node;
            else
                y->right = node;
        }
        else
        {
            root = node;
            root->Color=COLOR_BLACK;
        }
        // 2. 设置节点的颜色为红色
       // node->Color = COLOR_RED;

        // 3. 将它重新修正为一颗二叉查找树
        insertFixup(node);
}
/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *        node 插入的结点
 */
void RBTree::insertFixup(RBTreeNode *node)
{
        RBTreeNode *parent, *gparent;
        parent=node->parent;

        // 若“父节点存在，并且父节点的颜色是红色”
        while (node->parent!=NULL && node->parent->Color==COLOR_RED)
        {
            gparent = node->parent->parent;

            if(gparent==NULL)
                break;
            //若“父节点”是“祖父节点的左孩子”
            if (parent == gparent->left)
            {

                RBTreeNode *uncle = gparent->right;
                if (uncle && uncle->Color==COLOR_RED)// Case 1条件：叔叔节点是红色
                {

                    uncle->Color=COLOR_BLACK;

                    parent->Color=COLOR_BLACK;

                    gparent->Color=COLOR_RED;
                    node = gparent;

                }
                else if (parent->right == node) // Case 2条件：叔叔是黑色，且当前节点是右孩子
                {
                    RBTreeNode *tmp;
                    leftRotate(parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                else// Case 3条件：叔叔是黑色，且当前节点是左孩子。
                {


                         parent->Color=COLOR_BLACK;

                         gparent->Color=COLOR_RED;
                         rightRotate( gparent);
                }
            }
            else//若“z的父节点”是“z的祖父节点的右孩子”
            {
                // Case 1条件：叔叔节点是红色

                  RBTreeNode *uncle = gparent->left;
                  if (uncle && uncle->Color==COLOR_RED)
                  {
                      //rb_set_black(uncle);
                      uncle->Color=COLOR_BLACK;
                      //rb_set_black(parent);
                      parent->Color=COLOR_BLACK;
                     // rb_set_red(gparent);
                      gparent->Color=COLOR_RED;
                      node = gparent;

                  }
                else  if (parent->left == node)// Case 2条件：叔叔是黑色，且当前节点是左孩子
                {
                    RBTreeNode *tmp;
                    rightRotate( parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                else
                {
                      // Case 3条件：叔叔是黑色，且当前节点是右孩子。

                      parent->Color=COLOR_BLACK;
                      gparent->Color=COLOR_RED;
                      leftRotate( gparent);
                }

            }
        }

        // 将根节点设为黑色
        root->Color=COLOR_BLACK;
}

void RBTree::remove(RBTreeNode *node)
{
       RBTreeNode *child, *parent;
       Color_t color;

       // 被删除节点的"左右孩子都不为空"的情况。
       if ((node->left!=NULL) && (node->right!=NULL) )
       {
           // 被删节点的后继节点。(称为"取代节点")
           // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
          RBTreeNode *replace = node;

           // 获取后继节点
           replace = replace->right;
           while (replace->left != NULL)
               replace = replace->left;

           // "node节点"不是根节点(只有根节点不存在父节点)
           if (node!=root)
           {
               if (node->parent->left == node)
                   node->parent->left = replace;
               else
                   node->parent->right = replace;
           }
           else
               // "node节点"是根节点，更新根节点。
               root = replace;

           // child是"取代节点"的右孩子，也是需要"调整的节点"。
           // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
           child = replace->right;
           parent = replace->parent;
           // 保存"取代节点"的颜色
           color = replace->Color;

           // "被删除节点"是"它的后继节点的父节点"
           if (parent == node)
           {
               parent = replace;
           }
           else
           {
               // child不为空
               if (child!=NULL)
                   child->parent=parent;
               parent->left = child;

               replace->right = node->right;
               node->right->parent=replace;
               //rb_set_parent(node->right, replace);
           }

           replace->parent = node->parent;
           replace->Color= node->Color;
           replace->left = node->left;
           node->left->parent = replace;
           if (color == COLOR_BLACK)
                removeFixup(child, parent);
           delete node;
           return ;
       }
       if (node->left !=NULL)
           child = node->left;
       else
           child = node->right;

       parent = node->parent;
       // 保存"取代节点"的颜色
       color = node->Color;

       if (child)
           child->parent = parent;

       // "node节点"不是根节点
       if (parent)
       {
           if (parent->left == node)
               parent->left = child;
           else
               parent->right = child;
       }
       else
           root = child;
       if (color == COLOR_BLACK)
           removeFixup(child,parent);
       delete node;
}

void RBTree::removeFixup(RBTreeNode *node,RBTreeNode *parent)
{
    RBTreeNode *other;

        while ((!node || node->Color==COLOR_BLACK) && node != root)
        {
            if (parent->left == node)
            {
                other = parent->right;
                if (other->Color==COLOR_RED)
                {
                    // Case 1: x的兄弟w是红色的
                   // rb_set_black(other);
                    other->Color=COLOR_BLACK;
                  //  rb_set_red(parent);
                    parent->Color=COLOR_RED;
                    leftRotate( parent);
                    other = parent->right;
                }
                if ((!other->left || other->left->Color==COLOR_BLACK) &&
                    (!other->right || other->right->Color==COLOR_BLACK))
                {
                    // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                  //  rb_set_red(other);
                    other->Color=COLOR_RED;
                    node = parent;
                    parent = node->parent;
                }
                else
                {
                    if (!other->right || other->right->Color==COLOR_BLACK)
                    {
                        // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                       // rb_set_black(other->left);
                        other->left->Color=COLOR_BLACK;
                       // rb_set_red(other);
                        other->Color=COLOR_RED;
                        rightRotate( other);
                        other = parent->right;
                    }
                    // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                    //rb_set_color(other, rb_color(parent));
                    //rb_set_black(parent);
                    //rb_set_black(other->right);
                    other->Color=parent->Color;
                    parent->Color=COLOR_BLACK;
                    other->right->Color=COLOR_BLACK;
                    leftRotate(parent);
                    node = root;
                    break;
                }
            }
            else
            {
                other = parent->left;
                if (other->Color==COLOR_RED)
                {
                    // Case 1: x的兄弟w是红色的
                   // rb_set_black(other);
                    //rb_set_red(parent);
                    other->Color=COLOR_BLACK;
                    parent->Color=COLOR_RED;
                    rightRotate( parent);
                    other = parent->left;
                }
                if ((!other->left || other->left->Color==COLOR_BLACK) &&
                    (!other->right || other->right->Color==COLOR_BLACK))
                {
                    // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                    //rb_set_red(other);
                    other->Color=COLOR_RED;
                    node = parent;
                    parent =node->parent;
                }
                else
                {
                    if (!other->left || other->left->Color==COLOR_BLACK)
                    {
                        // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                        //rb_set_black(other->right);
                        //rb_set_red(other);
                        other->right->Color=COLOR_BLACK;
                        other->Color=COLOR_RED;
                        leftRotate(other);
                        other = parent->left;
                    }
                    // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                    //rb_set_color(other, rb_color(parent));
                    //rb_set_black(parent);
                    //rb_set_black(other->left);
                    other->Color=parent->Color;
                    parent->Color=COLOR_BLACK;
                    other->left->Color=COLOR_BLACK;
                    rightRotate(parent);
                    node = root;
                    break;
                }
            }
        }
        if (node)
          // rb_set_black(node);
            node->Color=COLOR_BLACK;
}


