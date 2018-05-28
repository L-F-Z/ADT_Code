//OO_ADT_Code Project
//https://github.com/L-F-Z/ADT_Code
//https://github.com/AugustusWillisWang/Notes/tree/master/DataStructure/ooadt
//Developed by AugustusWillisWang

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

#include <string.h>
#include <stdio.h>

#include "adt.h"
#include "dbg.h"

template <class T>
class Tree
{
  //基本的树结构, 可以使用vector表示树的各个分支节点, 这是一个树节点的定义
public:
  Tree()
  {
    // T data_;
    // subtree_;
    // Tree *nexttree;   //or right child point
    emptynode_ = true;
    Tree *parent_ = 0; //parent_ point
  }

  Tree(T data)
  {
    emptynode_ = false;
    Tree *parent_ = 0; //parent_ point
    data_ = data;
  }

  // Tree(std::vector<T> vector);

  Tree(const Tree<T> &src)
  {
    data_ = src.data_;
    // union {
    // Tree *subtree; //or left child point
    int subtreecnt = subtree_.size();
    while (subtreecnt-- > 0)
    {
      subtree_.push_back(&Tree(subtree_[subtreecnt]));
    }
    // };
    // Tree *nexttree; //or right child point
    *parent_ = 0; //parent_ point
    emptynode_ = src.emptynode_;
  }

  virtual ~Tree()
  {
    int size = subtree_.size();
    while (size-- > 0)
    {
      subtree_[size]->~Tree();
    }
    emptynode_ = true;
  }

  virtual int set(T data)
  {
    data_ = data;
    emptynode_ = false;
  }

  virtual int clear()
  {
    emptynode_ = true;
  }

  virtual bool empty()
  {
    return emptynode_;
  }

  virtual int update_parent()
  {
    // parent_=nullptr;
    //will not change the parent of the root.
    int size = subtree_.size();
    while (size-- > 0)
    {
      subtree_[size]->parent_ = this;
      subtree_[size]->update_parent();
    }
  }

  virtual int depth()
  {
    //使用前请确认, parent指针已经指定, 使用update_parent()函数设置parent;
    if (parent_)
    {
      return 1 + parent_->depth();
    }
    return 1;
  }

  virtual int height()
  {
    int size = subtree_.size();
    int max = 0;
    if (size)
    {
      while (size-- > 0)
      {
        int t = subtree_[size]->height();
        if (t > max)
          max = t;
      }
    }
    else
    {
      return 1;
    }

    return max + 1;
  }

  virtual Tree<T> *root()
  {
    if (parent_)
      return parent_->root();
    return this;
  }

  virtual T value()
  {
    return data_;
  }

  virtual T data()
  {
    return data_;
  }

  virtual Tree<T> *parent()
  {
    return parent_;
  }

  virtual Tree<T> *leftchild()
  {
    throw("leftchild undefined in basic tree.");
  }
  virtual Tree<T> *rightsibling()
  {
    throw("rightsibling undefined in basic tree.");
  }

  virtual int addto(Tree<T> &tree)
  {
    parent_ = &tree;
    tree.subtree_.push_back(this);
  }

  virtual int addto(Tree<T> *tree)
  {
    parent_ = tree;
    tree->subtree_.push_back(this);
  }

  virtual int insertchild(Tree<T> &tree)
  {
    subtree_.push_back(&tree);
    tree.parent_ = this;
  }

  virtual int insertchild(Tree<T> *tree)
  {
    if (tree)
    {
      subtree_.push_back(tree);
      tree->parent_ = this;
    }
  }

  virtual int deletechild()
  {
    for(auto i: subtree_)
    {
      i->~Tree();
    }
    subtree_.clear();
  }

  virtual int deletechild(int i)
  {
    subtree_[i]->~Tree();
    subtree_.erase(subtree_.begin() + i);
  }

  virtual int erase()
  {
    deletechild();
  }
  virtual int erase(int i)
  {
    deletechild(i);
  }

  virtual int cutchild()
  {
    for(auto i: subtree_)
    {
      i->parent_=0;
    }
    subtree_.clear();
  }

  virtual int cutchild(int i)
  {
    subtree_[i]->parent_=0;
    subtree_.erase(subtree_.begin() + i);
  }

  virtual int cut()
  {
    cutchild();
  }
  virtual int cut(int i)
  {
    cutchild(i);
  }

  virtual int traverse(void func(T))
  {
    throw("use BFS or DFS instead.");
  }

  virtual int degree()
  {
    //out degree only
    return subtree_.size();
  }

  virtual int print(int now = 0)
  {
    for (int i = 0; i < now; i++)
      std::cout << "  ";
    std::cout << data_ << std::endl;
    for (auto i : subtree_)
    {
      i->print(now + 1);
    }
  }

  virtual int operator+(T data)
  {
    if (emptynode_)
    {
      data_ = data;
      return 0;
    }
    data_ += data;
  }

  virtual Tree<T>* operator[](int i)
  {
    return subtree_[i];
  }

  virtual int push_back(Tree<T> &tree)
  {
    subtree_.push_back(&tree);
  }
  virtual int push_back(Tree<T> *tree)
  {
    subtree_.push_back(tree);
  }
  virtual int push_back(T data)
  {
    subtree_.push_back(new Tree<T>(data));
    subtree_.back()->parent_ = this;
  }

  // virtual int push_head(Tree<T> &tree)
  // {
  //   subtree_.push_head(&tree);
  // }
  // virtual int push_head(Tree<T> *tree)
  // {
  //   subtree_.push_head(tree);
  // }

  virtual Tree<T> *pop_back()
  {
    auto t = subtree_[subtree_.size() - 1];
    subtree_.pop_back();
    return t;
  }

  // virtual Tree<T> *pop_head()
  // {
  //   auto t = subtree_[0];
  //   subtree_.pop_head();
  //   return t;
  // }

  virtual Tree<T> operator&(Tree<T> tgt)
  {
    throw("undefined behavior.");
  }
  virtual Tree<T> operator|(Tree<T> tgt)
  {
    throw("undefined behavior.");
  }
  

protected:
  T data_;
  // union {
  std::vector<Tree<T> *> subtree_;
  // };

  Tree *parent_; //parent_ point
  bool emptynode_;
};

template <class T>
class Trees : public Tree<T>
{
public:
  Trees();
  ~Trees();

protected:
  Trees *nexttree_; //or right child point
  Trees *subtree_;  //or left child point
};

template <class T>
class Bintree : public Tree<T>
{
public:
  Bintree();
  Bintree(int num, T *data);
  Bintree(const Tree<T> &src);
  Bintree(const Bintree<T> &src);
  virtual ~Bintree();
  virtual int clear();
  virtual int empty();
  virtual int depth();
  virtual int root();
  virtual T value();
  virtual Tree<T> *parent_();
  virtual Tree<T> *leftchild();
  virtual Tree<T> *delete_leftchild();
  virtual Tree<T> *rightchild();
  virtual Tree<T> *delete_rightchild();
  virtual Tree<T> *leftsibling();
  virtual Tree<T> *rightsibling();
  virtual Tree<T> *operator[](int p);
  virtual int insertchild();
  virtual int insert_leftchild();
  virtual int insert_rightchild();
  virtual int delete_child();
  virtual int traverse();
  virtual int preorder_traverse();
  virtual int inorder_traverse();
  virtual int postorder_traverse();
  virtual int level_traverse();
  virtual int degree();
  virtual int print();
  virtual int operator+(T data);
  virtual int push_back();
  virtual int push_head();
  virtual T pop_back();
  virtual T pop_head();

private:
};

template <class T>
class Arrayed_Bintree : public Bintree<T>
{
public:
  Arrayed_Bintree();
  Arrayed_Bintree(int num, T *data);
  Arrayed_Bintree(const Tree<T> &src);
  Arrayed_Bintree(const Bintree<T> &src);
  virtual ~Arrayed_Bintree();
  virtual int clear();
  virtual int empty();
  virtual int depth();
  virtual int root();
  virtual T value();
  virtual int parent_();
  virtual int leftchild();
  virtual int delete_leftchild();
  virtual int rightchild();
  virtual int delete_rightchild();
  virtual int leftsibling();
  virtual int rightsibling();
  virtual int operator[](int p);
  virtual int insertchild();
  virtual int insert_leftchild();
  virtual int insert_rightchild();
  virtual int delete_child();
  virtual int traverse();
  virtual int preorder_traverse();
  virtual int inorder_traverse();
  virtual int postorder_traverse();
  virtual int degree();
  virtual int print();
  virtual int operator+(T data);
  virtual int push_back();
  virtual int push_head();
  virtual T pop_back();
  virtual T pop_head();

private:
  std::vector<T> bintree;
  std::vector<T> valid;
};

template <class T>
class Threading_bintree : public Bintree<T>
{
public:
  Threading_bintree();
  Threading_bintree(int num, T *data);
  Threading_bintree(const Tree<T> &src);
  Threading_bintree(const Bintree<T> &src);
  virtual ~Threading_bintree();
  virtual int clear();
  virtual int empty();
  virtual int depth();
  virtual int root();
  virtual T value();
  virtual Tree<T> *parent_();
  virtual Tree<T> *leftchild();
  virtual Tree<T> *delete_leftchild();
  virtual Tree<T> *rightchild();
  virtual Tree<T> *delete_rightchild();
  virtual Tree<T> *leftsibling();
  virtual Tree<T> *rightsibling();
  virtual Tree<T> *operator[](int p);
  virtual int insertchild();
  virtual int insert_leftchild();
  virtual int insert_rightchild();
  virtual int delete_child();
  virtual int traverse();
  virtual int preorder_traverse();
  virtual int inorder_traverse();
  virtual int postorder_traverse();
  virtual int level_traverse();
  virtual int degree();
  virtual int print();
  virtual int operator+(T data);
  virtual int push_back();
  virtual int push_head();
  virtual T pop_back();
  virtual T pop_head();

private:
};

template <class T>
class Huffman_Bintree : public Bintree<T>
{
public:
  Huffman_Bintree();
  Huffman_Bintree(int num, T *data);
  Huffman_Bintree(const Tree<T> &src);
  Huffman_Bintree(const Bintree<T> &src);

  virtual ~Huffman_Bintree();
  virtual int clear();
  virtual int empty();
  virtual int depth();
  virtual int root();
  virtual T value();
  virtual Tree<T> *parent_();
  virtual Tree<T> *leftchild();
  virtual Tree<T> *delete_leftchild();
  virtual Tree<T> *rightchild();
  virtual Tree<T> *delete_rightchild();
  virtual Tree<T> *leftsibling();
  virtual Tree<T> *rightsibling();
  virtual Tree<T> *operator[](int p);
  virtual int insertchild();
  virtual int insert_leftchild();
  virtual int insert_rightchild();
  virtual int delete_child();
  virtual int traverse();
  virtual int preorder_traverse();
  virtual int inorder_traverse();
  virtual int postorder_traverse();
  virtual int level_traverse();
  virtual int degree();
  virtual int print();
  virtual int operator+(T data);
  virtual int push_back();
  virtual int push_head();
  virtual T pop_back();
  virtual T pop_head();

private:
};

template <class T>
class Sorted_Bintree : public Bintree<T>
{
public:
  Sorted_Bintree();
  Sorted_Bintree(int num, T *data);
  Sorted_Bintree(const Tree<T> &src);
  Sorted_Bintree(const Bintree<T> &src);
  virtual ~Sorted_Bintree();
  virtual int clear();
  virtual int empty();
  virtual int depth();
  virtual int root();
  virtual T value();
  virtual Tree<T> *parent_();
  virtual Tree<T> *leftchild();
  virtual Tree<T> *delete_leftchild();
  virtual Tree<T> *rightchild();
  virtual Tree<T> *delete_rightchild();
  virtual Tree<T> *leftsibling();
  virtual Tree<T> *rightsibling();
  virtual Tree<T> *operator[](int p);
  virtual int insertchild();
  virtual int insert_leftchild();
  virtual int insert_rightchild();
  virtual int delete_child();
  virtual int traverse();
  virtual int preorder_traverse();
  virtual int inorder_traverse();
  virtual int postorder_traverse();
  virtual int level_traverse();
  virtual int degree();
  virtual int print();
  virtual int operator+(T data);
  virtual int push_back();
  virtual int push_head();
  virtual T pop_back();
  virtual T pop_head();

private:
};

template <class T>
class Avltree : public Bintree<T>
{
public:
  Avltree();
  Avltree(int num, T *data);
  Avltree(const Tree<T> &src);
  Avltree(const Bintree<T> &src);
  virtual ~Avltree();
  virtual int clear();
  virtual int empty();
  virtual int depth();
  virtual int root();
  virtual T value();
  virtual Tree<T> *parent_();
  virtual Tree<T> *leftchild();
  virtual Tree<T> *delete_leftchild();
  virtual Tree<T> *rightchild();
  virtual Tree<T> *delete_rightchild();
  virtual Tree<T> *leftsibling();
  virtual Tree<T> *rightsibling();
  virtual Tree<T> *operator[](int p);
  virtual int insertchild();
  virtual int insert_leftchild();
  virtual int insert_rightchild();
  virtual int delete_child();
  virtual int traverse();
  virtual int preorder_traverse();
  virtual int inorder_traverse();
  virtual int postorder_traverse();
  virtual int level_traverse();
  virtual int degree();
  virtual int print();
  virtual int operator+(T data);
  virtual int push_back();
  virtual int push_head();
  virtual T pop_back();
  virtual T pop_head();

private:
};

template <class T>
class Btree
{
};

template <class T>
class Bplustree
{
};

template <class T>
class Tiretree
{
};

int main()
{
  LICENSE;
  Tree<int> tt(99);

  using namespace std;
  cout << tt.data();
  L;
  tt.push_back(66);
  tt.push_back(33);
  tt.push_back(22);
  tt.push_back(11);
  tt[0]->push_back(1);
  tt[0]->push_back(2);
  tt[0]->push_back(3);
  tt[2]->push_back(1);
  tt[2]->push_back(1);
  tt[2]->push_back(1);
  tt[2]->push_back(2);
  tt[2]->push_back(3);
  tt.print();

  return 0;
}