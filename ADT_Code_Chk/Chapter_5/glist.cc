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

enum GlistType
{
    element,
    head
};

template <class T>
class Glist
{
  public:
    Glist();
    Glist(std::string srcstr);
    Glist(int num, T *dataarray);
    ~Glist();
    Glist(const Glist<T> &src);
    int length();
    int empty();
    int depth(int upperdepth = 1);
    // Glist *head();
    // Glist *tail();
    Glist<T> *next();
    int push_head(T src);
    int push_head(Glist<T> &srclist);
    int push_back(T src);
    int push_back(Glist<T> &src);
    int pop_head();
    int pop_back();
    Glist<T> *begin();
    Glist<T> *end();
    T head();
    T back();
    Glist<T> headlist();
    Glist<T> backlist();
    int traverse(void func(T));
    int print(int level = 0);        //利用缩进区分表的层次
    int insert(T src, int position); //start from 0;
    int insert(Glist<T> &srclist, int position);
    int erase(int position);
    T operator[](int p);
    //Do be aware that this insert and push implemention will add the origin structure to the father list.
    //If you need to protect the origin list, use copy function to make a copy of the origin list;
  private:
    Glist<T> *nextelement_;
    union {
        Glist<T> *sublist_;
        T data_;
    };
    GlistType type_;
    // friend Glist<T> InitGlist();
};

typedef Glist<int> *pGlist;

template <class T>
Glist<T>::Glist()
{
    type_ = element;
    nextelement_ = nullptr;
}

template <class T>
Glist<T>::Glist(std::string srcstr)
{
}

template <class T>
Glist<T>::Glist(int num, T *dataarray)
{
    // Glist<T> result;
    Glist<T> *p = this;
    for (int i = 0; i < num; i++)
    {
        p.nextelement_ = new Glist<T>;
        p = p.nextelement_;
        p.nextelement_ = nullptr;
        p.data_ = dataarray[i];
        p.type_ = element;
    }
    // return result;
}

template <class T>
Glist<T>::~Glist()
{
    Glist<T> *p = this->nextelement_;
    Glist<T> *bef;

    while (p)
    {
        if (p->type_ == element)
        {
            bef = p;
            p = p->nextelement_;
            delete p;
        }
        else //(p->type_==head)
        {
            p->sublist_.~Glist();
            bef = p;
            p = p->nextelement_;
            delete p;
        }
    }
}

#include <stack>
template <class T>
Glist<T>::Glist(const Glist<T> &src)
{
    std::stack<Glist<T> *> older;
    std::stack<Glist<T> *> newer;
    older.push(&src);
    newer.push(this);
    Glist<T> *past = &src;
    Glist<T> *now = this;
    while (!older.empty())
    {
        past = older.top();
        now = newer.top();
        older.pop();
        newer.pop();
        if (past->type == element)
        {
            now->data_ = past->data_;
            now->type_ = element;
        }
        else
        {
            now->type_ = head;
            now->sublist_ = new Glist<T>;
            older.push(past->sublist_);
            newer.push(now->sublist_);
        }
        if (past->nextelement_)
        {
            now->nextelement_ = new Glist<T>;
            older.push(past->nextelement_);
            newer.push(now->nextelement_);
        }
    }
}

template <class T>
int Glist<T>::length()
{
    int cnt = 0;
    Glist<T> *now = this->nextelement_;
    while (now)
    {
        ++cnt;
        now = now->nextelement_;
    }
    return cnt;
}

template <class T>
int Glist<T>::empty()
{
    return this->nextelement_ == nullptr;
}

template <class T>
int Glist<T>::depth(int upperdepth)
{
    int maxdepth = 0;
    return upperdepth + maxdepth;
}

// template <class T>
// Glist *Glist::head() {}

// template <class T>
// Glist *Glist::tail() {}

template <class T>
Glist<T> *Glist<T>::next()
{
    return this->nextelement_;
}

template <class T>
int Glist<T>::push_head(T src)
{
    this->insert(src, 0);
}

template <class T>
int Glist<T>::push_head(Glist<T> &srclist)
{
    this->insert(srclist, 0);
}

template <class T>
int Glist<T>::push_back(T src)
{
    Glist<T> *now = this;
    while (now->nextelement_)
    {
        now = now->nextelement_;
    }
    now->nextelement_ = new Glist<T>;
    now->nextelement_->data_ = src;
}

template <class T>
int Glist<T>::push_back(Glist<T> &src)
{
    Glist<T> *now = this;
    while (now->nextelement_)
    {
        now = now->nextelement_;
    }
    now->nextelement_ = src.nextelement_;
    // now->nextelement_->data_ = src;
    return 0;
}

template <class T>
int Glist<T>::pop_head()
{
    if (this->nextelement_)
    {
        this->erase(0);
    }
    return 0;
}

template <class T>
int Glist<T>::pop_back()
{
    int x = 0;
    Glist<T> *now = this;
    if (now->nextelement_)
    {
        now = now->nextelement_;
        ++x;
    }
    this->erase(x - 1);
    return 0;
}

template <class T>
Glist<T> *Glist<T>::begin()
{
    return this->nextelement_;
}

template <class T>
Glist<T> *Glist<T>::end()
{
    Glist<T> *now = this;
    if (now->nextelement_)
    {
        now = now->nextelement_;
    }
    return now;
}

template <class T>
T Glist<T>::head() {
    return this->nextelement_->data_;
}

template <class T>
T Glist<T>::back() 
{
    Glist<T> *now = this;
    if (now->nextelement_)
    {
        now = now->nextelement_;
    }
    return now->data_;
}

template <class T>
Glist<T> Glist<T>::headlist() {
    return this->nextelement_->sublist_;
}

template <class T>
Glist<T> Glist<T>::backlist()
{
    Glist<T> *now = this;
    if (now->nextelement_)
    {
        now = now->nextelement_;
    }
    return now->sublist_;
}

#include<stack>
template <class T>
int Glist<T>::traverse(void func(T)) 
{
    std::stack<Glist*> s;
    Glist<T> *now;
    s.push(this->nextelement_);
    while(!s.empty())
    {
        now=s.top();
        if (now)
        {
            if(now->type==element)
            {
                func(now->data_);
                s.pop();
            }
            else
            {
                s.pop();
                s.push(now->sublist_->nextelement_);
            }
        }
        if(now->nextelement_)
        {
            push(now->nextelement_);
        }
    }
    return 0;
}

template <class T>
int Glist<T>::print(int level)
{
    Glist<T> *p = this->nextelement_;
    // int level=0;
    while (p)
    {
        if (p->type_ == element)
        {
            std::cout << std::string(level, ' ')
                      << std::string(level, ' ')
                      << p->data_ << std::endl;
        }
        else
        {
            p->sublist_->print(level + 1);
        }
        p = p->nextelement_;
    }
} //利用缩进区分表的层{}

template <class T>
int Glist<T>::insert(T src, int position)
{
    int cnt = 0;
    Glist<T> *p = this;
    while (cnt < position)
    {
        ++cnt;
        p = p->nextelement_;
    }
    Glist<T> *temp = p->nextelement_;
    p->nextelement_ = new Glist<T>;
    p = p->nextelement_;
    p->data_ = src;
    p->nextelement_ = temp;
    return 0;
} //start from 0{}

template <class T>
int Glist<T>::erase(int position)
{
    Glist<T> *now = this;
    for (int i = 0; i < position; i++)
    {
        now = now->nextelement_;
    }
    Glist<T> *temp = now->nextelement_->nextelement_;
    if (now->nextelement_->type == element)
    {
    }
    else
    {
        now->nextelement_->sublist_->~Glist();
        delete now->nextelement_->sublist_;
    }
    delete now->nextelement_;
    now->nextelement_ = temp;
}

template <class T>
int Glist<T>::insert(Glist<T> &srclist, int position)
{
    int cnt = 0;
    Glist<T> *p = this;
    while (cnt < position)
    {
        ++cnt;
        p = p->nextelement_;
    }
    Glist<T> *temp = p->nextelement_;
    p->nextelement_ = srclist.nextelement_;
    while (p->nextelement_)
    {
        p = p->nextelement_;
    }
    p->nextelement_ = temp;
    return 0;
}

template <class T>
T Glist<T>::operator[](int p)
{
    Glist<T> *now;
    for (int i = 0; i < p; i++)
    {
        now = now->nextelement_;
    }
    return now->data_;
}

int main()
{
    return 0;
}