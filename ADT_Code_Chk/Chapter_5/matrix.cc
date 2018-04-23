//OO_ADT_Code Project
//https://github.com/L-F-Z/ADT_Code
//https://github.com/AugustusWillisWang/Notes/tree/master/DataStructure/ooadt
//Developed by AugustusWillisWang

//remark: have not been tested yet!
//the definition of col and row for SMatrix and OMatrix is different, and the author is too lazy to change it.

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

// const int MAX_ROW_NUM = 233;

class Matrix
{
public:
  Matrix();
  ~Matrix();
  virtual int print();
  virtual int updatecnt();
  Matrix transpose();
  friend Matrix operator+(Matrix tgt);
  friend Matrix operator-(Matrix tgt);
  friend Matrix operator*(Matrix tgt);

  int col_ = 0;
  int row_ = 0;
  int elem_ = 0;

private:
  std::vector<int> rpos;
  std::vector<std::vector<int>> data;
};

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

int Matrix::print() {}
int Matrix::updatecnt() {}
Matrix Matrix::transpose() {}

//Sparse Matrix
//----------------------------------------------------

class Matrix_Sparse : public Matrix //todo : fix a->col b->row
{
public:
  Matrix_Sparse();
  Matrix_Sparse(const Matrix_Sparse &src);
  Matrix_Sparse(const int *src, int row, int col);
  Matrix_Sparse(std::vector<int> src);
  ~Matrix_Sparse();
  int print();
  virtual int updatecnt();
  Matrix_Sparse transpose_sparse();
  friend Matrix_Sparse operator+(Matrix_Sparse tgt, Matrix_Sparse tgt2);
  friend Matrix_Sparse operator-(Matrix_Sparse tgt, Matrix_Sparse tgt2);
  friend Matrix_Sparse operator*(Matrix_Sparse tgt, Matrix_Sparse tgt2);
  struct MSdot //todo : fix a->col b->row
  {
    int a;
    int b;
    int data;
    struct MSdot operator=(int i)
    {
      this->data = i;
    }
  };

  int addline(std::vector<int> src); //addline
  int findpoint(int a, int b);       //get the value of a point;
  int setup_row_position();          //reset row_position_
  int set(int a, int b, int data);   //get a point to given value
  int sort();                        //sort the elements by row, update row_position_ , will not merge the same term at the same time;
  int merge();                       //merge the same term; should be called after every add-in operation.

private:
  std::vector<MSdot> data_;
  std::vector<int> row_position_;
  std::vector<int> row_cnt_;
};

int Matrix_Sparse::addline(std::vector<int> src) //addline
{
  int t;
  struct Matrix_Sparse::MSdot tmpstr;
  if (src.size() > col_)
  {
    col_ = src.size();
  }
  while (!src.empty())
  {
    if (t = src.back() == 0)
    {
    }
    else
    {
      {
        tmpstr.a = row_ + 1, tmpstr.b = src.size() - 1, tmpstr.data = t;
      }
      data_.push_back(tmpstr);
      elem_++;
    }
    src.pop_back();
  }
  ++row_;
}

Matrix_Sparse::Matrix_Sparse(const int *src, int row, int col)
{
  if (!src)
    throw("Nullptr for initialzing Matrix_Sparse.");
  int t;
  struct Matrix_Sparse::MSdot tmpstr;
  if (col > col_)
  {
    col_ = col;
  }
  if (row > row_)
  {
    row_ = row;
  }

  for (int a = 0; a < row; a++)
  {
    for (int b = 0; b < col; b++)
    {
      if (t = *(src + a * col + b) == 0)
      {
        continue;
      }
      else
      {
        {
          tmpstr.a = a, tmpstr.b = b, tmpstr.data = t;
        }
        data_.push_back(tmpstr);
        elem_++;
      }
    }
  }
}

int Matrix_Sparse::findpoint(int a, int b)
{
  int s = data_.size();
  for (int i = 0; i < s; i++)
  {
    if (data_[i].a == a && data_[i].b == b)
      return data_[i].data;
  }
  return 0;
}

int Matrix_Sparse::print()
{
  //printbyline
  for (int a = 0; a < row_; a++)
  {
    for (int b = 0; b < col_; b++)
    {
      std::cout << this->findpoint(a, b) << " ";
    }
    std::cout << std::endl;
  }
}

int Matrix_Sparse::updatecnt()
{
  elem_ = data_.size();
}

int Matrix_Sparse::setup_row_position() //can be used only in ordered data_;
{
  row_position_.clear();
  row_cnt_.clear();
  int s = data_.size();
  int rowcnt = -1;
  int i = 0;
  while (i < s)
  {
    if (data_[i].a > rowcnt)
    {
      rowcnt = data_[i].a;
      row_position_.push_back(i);
    }
    ++i;
  }
  return 0;
}

Matrix_Sparse Matrix_Sparse::transpose_sparse()
{
  int s = data_.size();
  int i = 0;
  int t;
  while (i < s)
  {
    t = data_[i].a;
    data_[i].a = data_[i].b;
    data_[i].b = t;
    ++i;
  }
}

int Matrix_Sparse::set(int a, int b, int data)
{
  struct Matrix_Sparse::MSdot tmpstr;
  if ((b + 1) > col_)
  {
    col_ = (b + 1);
  }
  if ((a + 1) > row_)
  {
    row_ = (a + 1);
  }
  {
    tmpstr.a = a, tmpstr.b = b, tmpstr.data = data;
  }
  data_.push_back(tmpstr);
  elem_++;
}

int Matrix_Sparse::sort()
{
  row_cnt_.clear();
  row_position_.clear();
  std::vector<int> temp(row_, 0);
  row_cnt_ = temp;
  //traverse and get row_cnt_
  //use temp to save how many point has been moved
  int s = data_.size();
  for (int i = 0; i < s; i++)
  {
    ++row_cnt_[data_[i].a];
  }
  int pc = 0;
  for (int i = 0; i < row_; i++)
  {
    row_position_[i] = pc;
    pc += row_cnt_[i];
  }

  std::vector<int> datatemp(s, 0);
  int ta, tb;

  for (int i = 0; i < s; i++)
  {
    ta = data_[i].a;
    datatemp[row_position_[ta] + temp[ta]] = data_[i].data;
    temp[ta] += 1;
  }

  data_.assign(datatemp.begin(), datatemp.end());
}

int Matrix_Sparse::merge()
{
  int l = data_.size();
  int todelete[l];
  for (int i = 0; i < l; i++)
  {
    todelete[l] = 0;
  }
  for (int a = 0; a < l; a++)
  {
    if (!todelete[l])
    {
      for (int b = a + 1; b < l; b++)
      {
        if (!todelete[l])
        {
          if (data_[a].a == data_[b].a && data_[a].b == data_[b].b)
          {
            data_[a].data += data_[b].data;
            todelete[b] = 1;
          }
        }
      }
    }
  }
  for (int i = l; i >= 0; i--)
  {
    if (todelete[l])
    {
      data_.erase(data_.begin() + l);
    }
  }

  elem_ = data_.size();
}

Matrix_Sparse::Matrix_Sparse(const Matrix_Sparse &src)
{
  this->data_.assign(src.data_.begin(), src.data_.end());
  this->row_position_.assign(src.row_position_.begin(), src.row_position_.end());
  this->row_cnt_.assign(src.row_cnt_.begin(), src.row_cnt_.end());
}

Matrix_Sparse::~Matrix_Sparse()
{
}

Matrix_Sparse operator+(Matrix_Sparse tgt, Matrix_Sparse tgt2)
{
  Matrix_Sparse res = tgt;

  if (tgt2.row_ > tgt.row_)
    tgt.row_ = tgt2.row_;
  if (tgt2.col_ > tgt.col_)
    tgt.col_ = tgt2.col_;

  int l = tgt2.data_.size();
  for (int i = 0; i < l; i++)
  {
    res.data_.push_back(tgt2.data_.back());
  }

  res.merge();
  res.sort();
  res.elem_ = res.data_.size();
  return res;
}

Matrix_Sparse operator-(Matrix_Sparse tgt, Matrix_Sparse tgt2) {}
Matrix_Sparse operator*(Matrix_Sparse tgt, Matrix_Sparse tgt2) {}

// Orthogonal Matrix
//----------------------------------------------------

class Matrix_Orthogonal : public Matrix
{
public:
  Matrix_Orthogonal();
  Matrix_Orthogonal(const Matrix_Orthogonal &src);
  Matrix_Orthogonal(int col, int row);
  Matrix_Orthogonal(const int *src, int row, int col);
  Matrix_Orthogonal(std::vector<int> src);
  ~Matrix_Orthogonal();
  int print();
  // virtual int updatecnt();
  Matrix_Orthogonal transpose_orthogonal();
  friend Matrix_Orthogonal operator+(Matrix_Orthogonal tgt, Matrix_Orthogonal tgt2);
  friend Matrix_Orthogonal operator-(Matrix_Orthogonal tgt, Matrix_Orthogonal tgt2);
  friend Matrix_Orthogonal operator*(Matrix_Orthogonal tgt, Matrix_Orthogonal tgt2);

  typedef struct MONode
  {
    int col;
    int row;
    int data;
    struct MONode *colnext;
    struct MONode *rownext;
  } * pMON;

  // int Matrix_Orthogonal::addline(std::vector<int> src); //addline
  int findpoint(int col, int row);     //get the value of a point;
  int set(int col, int row, int data); //get a point to given value
  int resize(int col, int row);        //resize the shape of the matrix

private:
  // std::vector<MSdot> data_;
  // std::vector<int> row_position_;
  // std::vector<int> row_cnt_;
  std::vector<pMON> rowhead_;
  std::vector<pMON> colhead_;
  int row_ = 0;
  int col_ = 0;
};

Matrix_Orthogonal::Matrix_Orthogonal()
{
  row_ = 0;
  col_ = 0;
}

Matrix_Orthogonal::Matrix_Orthogonal(int col, int row)
{
  col_ = col;
  row_ = row;
  std::vector<pMON> temp1(col, nullptr);
  std::vector<pMON> temp2(row, nullptr);
  colhead_.assign(temp1.begin(), temp1.end());
  rowhead_.assign(temp2.begin(), temp2.end());
}

Matrix_Orthogonal::Matrix_Orthogonal(const Matrix_Orthogonal &src)
{
  // copy according to row
  this->row_ = rowhead_.size();
  this->rowhead_.assign(src.rowhead_.begin(), src.rowhead_.end());
  std::vector<pMON> temp(src.colhead_);
  this->colhead_.assign(temp.begin(), temp.end());
  for (int a = 0; a < row_; a++)
  {
    if (rowhead_[a])
    {
      // copynode
      // update colhead_
    }
  }
}

Matrix_Orthogonal::Matrix_Orthogonal(const int *src, int row, int col)
{
  // todo
}

// Matrix_Orthogonal::Matrix_Orthogonal(std::vector<int> src);

Matrix_Orthogonal::~Matrix_Orthogonal() //will free memory
{
  row_ = rowhead_.size();
  for (int i = 0; i < row_; i++)
  {
    while (rowhead_[i])
    {
      auto ptr = rowhead_[i];
      rowhead_[i] = rowhead_[i]->rownext;
      delete ptr;
    }
  }
}

int Matrix_Orthogonal::print()
{
  for (int a = 0; a < row_; a++)
  {
    for (int b = 0; b < col_; b++)
    {
      std::cout << findpoint(b, a) << " ";
    }
    std::cout << std::endl;
  }
}
// virtual int updatecnt();
Matrix_Orthogonal Matrix_Orthogonal::transpose_orthogonal()
{
  row_ = rowhead_.size();
  for (int i = 0; i < row_; i++)
  {
    auto tmp = rowhead_[i];
    while (tmp)
    {
      auto ptr = tmp;
      tmp = tmp->rownext;
      auto tmpptr = ptr->colnext;
      ptr->colnext = ptr->rownext;
      ptr->rownext = tmpptr;
    }
  }

  int t = col_;
  col_ = row_;
  row_ = t;

  std::vector<pMON> swp(colhead_);
  colhead_.assign(rowhead_.begin(), rowhead_.end());
  rowhead_.assign(swp.begin(), swp.end());
}

Matrix_Orthogonal operator+(Matrix_Orthogonal tgt, Matrix_Orthogonal tgt2)
{
  Matrix_Orthogonal result(tgt);
  for (int a = 0; a < result.col_;a++){
    for (int b = 0;b<result.row_;b++){
      result.set(a, b, tgt2.findpoint(a, b));
    }
  }
  return result;
}

Matrix_Orthogonal
operator-(Matrix_Orthogonal tgt, Matrix_Orthogonal tgt2)
{
  Matrix_Orthogonal result(tgt);
  for (int a = 0; a < result.col_; a++)
  {
    for (int b = 0; b < result.row_; b++)
    {
      result.set(a, b, -tgt2.findpoint(a, b));
    }
  }
  return result;
}

Matrix_Orthogonal operator*(Matrix_Orthogonal tgt, Matrix_Orthogonal tgt2)
{
  
  Matrix_Orthogonal result(tgt.col_,tgt2.row_);
  int ct = tgt.row_;
  for (int a = 0; a < result.col_; a++)
  {
    for (int b = 0; b < result.row_; b++)
    {
      for (int c = 0; c < ct;c++)
      {
        result.set(a, b, tgt.findpoint(a, c) * tgt2.findpoint(c, b));
      }
    }
  }
  return result;
}

int Matrix_Orthogonal::findpoint(int col, int row) //get the value of a point;
{
  auto tmp = rowhead_[row];
  while (tmp)
  {
    if (tmp->col == col)
      return tmp->data;
    tmp = tmp->rownext;
  }
  return 0;
}

int Matrix_Orthogonal::set(int col, int row, int data) //get a point to given value
{
  if (row_ <= row || col_ <= col)
    throw("Insert out of range.");
  pMON pnewnode = new struct MONode;
  pnewnode->col = col;
  pnewnode->row = row;
  pnewnode->rownext = 0;
  pnewnode->colnext = 0;
  pnewnode->data = data;

  if(data==0)
    return 0;
  pMON temp = colhead_[col];
  if (!colhead_[col] || colhead_[col]->row > row)
  {
    pnewnode->colnext = colhead_[col];
    colhead_[col] = pnewnode;
  }
  else
  {
    {
      while (temp->colnext && temp->colnext->row < row)
      {
        temp = temp->colnext;
      }
      if (temp->colnext->row == row)
      {
        temp->colnext->data += data;
      }
      else
      {
        pnewnode->colnext = temp->colnext;
        temp->colnext = pnewnode;
      }
    }

    if (!rowhead_[row] || rowhead_[row]->col > col)
    {
      pnewnode->rownext = rowhead_[row];
      rowhead_[row] = pnewnode;
    }
    else
    {
      {
        while (temp->rownext && temp->rownext->col < col)
        {
          temp = temp->rownext;
        }
        //if the node already exists, it has been dealed in the col part;
        if (temp->rownext->col == col)
        {
          // temp->colnext->data += data;
        }
        else
        {
          pnewnode->rownext = temp->rownext;
          temp->rownext = pnewnode;
        }
      }
    }
  }
}

  // int Matrix_Orthogonal::resize(int a, int b) {} //resize the shape of the matrix

  int main()
  {
  }
