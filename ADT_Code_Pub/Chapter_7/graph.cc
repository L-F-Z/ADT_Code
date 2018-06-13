//OO_nvertexDT_Code Project
//https://github.com/L-F-Z/ADT_Code
//https://github.com/AugustusWillisWang/Notes/tree/master/DataStructure/ooadt
//Developed by AugustusWillisWang

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>

#include <string.h>
#include <stdio.h>

#include "adt.h"
#include "dbg.h"

// #define MAGIC_MAX 23333

//图模板定义----------------------------------------------------------------

template <class T>
struct GetedgeResult
{
    T data;
    bool exist;
}; //use auto to simplify your code;

#include <vector>

// template <class T>
struct TraverseNode
{
    int vertex;
    std::vector<std::pair<int, int>> edge;
};

template <class T>
class Graph
{
    //父类, 提供图所用到的各种接口

  public:
    Graph()
    {
        std::cout << "Init graph: " << this << std::endl;
    }
    ~Graph()
    {
        std::cout << "Destruct graph: " << this << std::endl;
    }

    virtual GetedgeResult<T> getedge(int tail, int head) //查找某条边的权值
    {
        std::cout << "Called pure virtual func getedge." << std::endl;
        throw("Called pure virtual func getedge.");
    }

    virtual int setedge(int tail, int head, T val) //写入某条边的权值
    {
        std::cout << "Called pure virtual func setedge." << std::endl;
        throw("Called pure virtual func setedge.");
    }

    virtual bool haveedge(int vertex) //查找某个顶点是否存在出边
    {
        std::cout << "Called pure virtual func haveedge." << std::endl;
        throw("Called pure virtual func haveedge.");
    }

    virtual int degree(int vertex)
    {
        std::cout << "Degree func undefined." << std::endl;
    }

    virtual int vertex()
    {
        std::cout << "Vertex func undefined." << std::endl;
    }

    virtual std::vector<std::pair<int, int>> getedge_around(int vertex)
    {
        std::cout << "Getedge_around func undefined." << std::endl;
        throw("Getedge_around func undefined.");
    }

    virtual std::vector<int> vertex_around(int vertex)
    {
        std::cout << "vertex_around func undefined." << std::endl;
        throw("vertex_around func undefined.");
    }
    // int _nvertex;
};

//有向图的邻接矩阵表示
template <class T>
class GraphArray : public Graph<T>
{
  public:
    GraphArray(int vertex)
    {
        int i = vertex * vertex;
        _data = new T[i];
        _mark = new int[i];
        _exist = new bool[i];
        _nvertex = vertex;
        while (i-- > 0)
        {
            _mark[i] = 0;
            _exist[i] = false;
        }
    }
    ~GraphArray()
    {
        delete[] _data;
        delete[] _mark;
        delete[] _exist;
    }

    GraphArray<T>(const GraphArray<T> &src)
    {
        _nvertex = src._nvertex;
        for (int i = 0; i < _nvertex * _nvertex; i++)
        {
            *(_data + i) = *(src._data + i);
            *(_mark + i) = *(src._mark + i);
            *(_exist + i) = *(src._exist + i);
        }
    }

    struct GetedgeResult<T> getedge(int tail, int head)
    {
        struct GetedgeResult<T> result;
        result.data = *(_data + sizeof(T) * tail * _nvertex + head);
        result.exist = *(_exist + sizeof(T) * tail * _nvertex + head);
        return result;
    }

    int
    setedge(int tail, int head, T value)
    {
        *(_data + tail * _nvertex + head) = value;
        *(_exist + tail * _nvertex + head) = true;
    }

    int setedgemark(int tail, int head, int value)
    {
        *(_mark + tail * _nvertex + head) = value;
    }

    int setedgeexist(int tail, int head, bool value)
    {
        *(_exist + tail * _nvertex + head) = value;
    }

    bool haveedge(int vertex)
    {
        bool result = false;
        for (int i = 0; i < _nvertex; i++)
        {
            if (*(_exist + vertex * _nvertex + i))
            {
                result = true;
                break;
            }
        }
        return result;
    }

    int vertex()
    {
        return _nvertex;
    }

    std::vector<std::pair<int, int>> getedge_around(int vertex)
    {
        std::vector<std::pair<int, int>>  result;
        std::pair<int, int> p;
        for (int i = 0; i < _nvertex; i++)
        {
            if (*(_exist + vertex * _nvertex + i))
            {
                p.first = vertex;
                p.second = i;
                result.push_back(p);
            }
        }
        return result;
    }

    virtual std::vector<int> vertex_around(int vertex)
    {
        std::vector<int> result;
        for (int i = 0; i < _nvertex; i++)
        {
            if (*(_exist + vertex * _nvertex + i))
            {
                result.push_back(i);
            }
        }
        return result;
    }

        int zero()
        {
            for (int i = 0; i < _nvertex * _nvertex; i++)
            {
                *(_data + i) = 0;
                *(_mark + i) = 0;
            }
        }

        int init()
        {
            for (int i = 0; i < _nvertex * _nvertex; i++)
            {
                *(_exist + i) = false;
            }
        }

        int _nvertex;
        T *_data;
        int *_mark;
        bool *_exist;
};

//有向图的邻接表表示
template <class T>
struct ArcAdjlist
{
    int head;
    int tail;
    struct ArcAdjlist *nextarc;
    int mark;
    T data;
};

template <class T>
struct PointAdjlist
{
    T data;
    int mark;
    struct ArcAdjlist<T> *firstarc;
};

template <class T>
class GraphAdjlist : public Graph<T>
{
  public:
    GraphAdjlist(int nvertix)
    {
        _data = new struct PointAdjlist<T>[nvertix];
        _nvertex = nvertix;
        while (nvertix-- > 0)
        {
            _data[nvertix].firstarc = 0;
            _data[nvertix].data = 0;
            _data[nvertix].mark = 0;
        }
    }
    ~GraphAdjlist()
    {
        delete[] _data;
    }
    int setedge(int tail, int head, T val)
    {
        struct ArcAdjlist<T> *now = new ArcAdjlist<T>;
        now->head = head;
        now->tail = tail;
        now->data = val;
        now->mark = 0;
        now->nextarc = _data[tail].firstarc;
        _data[tail].firstarc = now;
    }

    struct GetedgeResult<T> getedge(int tail, int head)
    {
        struct GetedgeResult<T> result;
        struct ArcAdjlist<T> *now = _data[tail].firstarc;
        while (now && now->head != head)
            now = now->nextarc;
        if (now)
        {
            result.data = now->data;
            result.exist = true;
            return result;
        };
        {
            result.exist = false;
            return result;
        }
    }

    bool
    haveedge(int vertex)
    {
        return _data[vertex].firstarc != 0;
    }

    int vertex()
    {
        return _nvertex;
    }

    int _nvertex;
    struct PointAdjlist<T> *_data;
};

//有向图的十字链表表示

template <class T>
struct ArcOrthgonal
{
    int head;
    int tail;
    struct ArcOrthgonal *headarc;
    struct ArcOrthgonal *tailarc;
    int mark;
    T data;
};

template <class T>
struct PointOrthogonal
{
    T data;
    int mark;
    struct ArcOrthgonal<T> *firsthead;
    struct ArcOrthgonal<T> *firsttail;
};

template <class T>
class GraphOrthgonal : public Graph<T>
{
  public:
    GraphOrthgonal(int nvertix)
    {
        _data = new struct PointOrthogonal<T>[nvertix];
        _nvertex = nvertix;
        while (nvertix-- > 0)
        {
            _data[nvertix].firsthead = 0;
            _data[nvertix].firsttail = 0;
            _data[nvertix].data = 0;
            _data[nvertix].mark = 0;
        }
    }
    ~GraphOrthgonal()
    {
        delete[] _data;
    }

    int setedge(int tail, int head, T val)
    {
        //是否允许相同的边被重复设置?
        auto p = new struct ArcOrthgonal<T>;
        p->data = val;
        p->tail = tail;
        p->head = head;
        p->mark = 0;
        p->headarc = _data[head].firsthead;
        p->tailarc = _data[tail].firsttail;

        _data[tail].firsttail = p;
        _data[head].firsthead = p;
    }

    struct GetedgeResult<T> getedge(int tail, int head)
    {
        struct GetedgeResult<T> result;
        result.exist = true;

        if (auto p = _data[tail].firsttail)
        {
            while (p && p->head != head)
            {
                p = p->tailarc;
            }
            if (p)
            {
                result.data = p->data;
                return result;
            }
            {
                result.exist = false;
                return result;
            }
        }
        {
            result.exist = false;
            return result;
        }
    }

    bool
    haveedge(int vertex)
    {
        return _data[vertex].firsttail != 0;
    }

    int vertex()
    {
        return _nvertex;
    }

    int _nvertex;
    struct PointOrthogonal<T> *_data;
};

//邻接多重表单向图
//感觉这个定义就很睿智

template <class T>
struct ArcAdjmullist
{
    int head;
    int tail;
    struct ArcAdjmullist *headarc;
    struct ArcAdjmullist *tailarc;
    int mark;
    T data;
};

template <class T>
struct PointAdjmullist
{
    T data;
    int mark;
    struct ArcAdjmullist<T> *firstarc;
};

template <class T>
class GraphAdjmullist : public Graph<T>
{
  public:
    GraphAdjmullist(int nvertix)
    {
        _data = new struct PointAdjmullist<T>[nvertix];
        _nvertex = nvertix;
        while (nvertix-- > 0)
        {
            _data[nvertix].firstarc = 0;
            _data[nvertix].data = 0;
            _data[nvertix].mark = 0;
        }
    }
    ~GraphAdjmullist()
    {
        delete[] _data;
    }
    int setedge(int tail, int head, T val)
    {
        auto p = new ArcAdjmullist<T>;
        p->tail = tail;
        p->head = head;
        p->data = val;
        p->mark = 0;
        p->headarc = _data[head].firstarc;
        p->tailarc = _data[tail].firstarc;
        _data[head].firstarc = p;
        _data[tail].firstarc = p;
    }

    struct GetedgeResult<T> getedge(int tail, int head)
    {
        struct GetedgeResult<T> result;
        struct ArcAdjmullist<T> *now = _data[tail].firstarc;
        while (now)
        {

            if (now->tail == tail)
            {
                if (now->head == head)
                    break;
                now = now->headarc;
            }
            else
            {
                if (now->tail == head)
                    break;
                now = now->tailarc;
            }
        }
        if (now)
        {
            result.data = now->data;
            result.exist = true;
            return result;
        };
        {
            result.exist = false;
            return result;
        }
    }

    bool
    haveedge(int vertex)
    {
        return _data[vertex].firstarc != 0;
    }

    int vertex()
    {
        return _nvertex;
    }

    int _nvertex;
    struct PointAdjmullist<T> *_data;
};

//图算法定义----------------------------------------------------------------

//todo:还有3种图的getaround没写

#include <queue>
template <class T>
int BFS(Graph<T> G, int src, void func(T))
{
    std::queue<int>Q;
    if(src>=G.vertex()||src<0)
    {
        return -1;
        //BFS falled;
    }

    Q.push_back(src);

    while(!Q.empty())
    {
        auto t=Q.top();
        func(t);
        Q.pop();
        auto V = G.vertex_around(t);
        Q.push_back(V);
    }
}

template <class T>
int DFS(Graph<T> G, int src, void func(T))
{
    //先序DFS
    std::stack<int>S;
    if(src>=G.vertex()||src<0)
    {
        return -1;
        //DFS falled;
    }

    S.push_back(src);

    while(!S.empty())
    {
        auto t=S.top();
        func(t);
        S.pop();
        auto V = G.vertex_around(t);
        S.push_back(V);
    }
}

template <class T>
std::vector<std::pair<int, int>> Prim(Graph<T> G, int src)
{

}

template <class T>
std::vector<std::pair<int, int>> Kruskal()
{

}

template <class T>
int Tarjan(Graph<T> G)//ArticulationPoint
{

}

template <class T>
bool isBiconnected(Graph<T> G)
{

}

template <class T>
int TopologicalSort(Graph<T> G)
{

}

template <class T>
std::vector<std::pair<int,int>>CriticalPath(Graph<T> G)
{

}

template <class T>
std::vector<int> Dijkstra(Graph<T> G, int src, int dst)
{
    
}

template <class T>
std::vector<int> Flod(Graph<T> G, int src, int dst)
{

}

template <class T>
struct ResultFloyd
{
    std::vector<std::vector<int>> path;
    std::vector<T> length;
};

template <class T>
struct ResultFloyd<T> Floyd(Graph<T> G)
{

}

int main()
{
    using namespace std;
    GraphArray<int> G(3);
    G.zero();
    G.setedge(0, 0, 3);
    G.setedge(0, 1, 2);
    cout << G.getedge(0, 1).data << endl;

    GraphOrthgonal<int> S(5);
    S.setedge(0, 0, 3);
    S.setedge(0, 1, 2);
    cout << S.getedge(0, 1).data << endl;
    cout << S.getedge(0, 0).data << endl;

    GraphAdjmullist<int> Q(5);
    Q.setedge(1, 2, 3);
    Q.setedge(0, 1, 2);
    for (int j = 0; j < Q._nvertex; j++)
    {
        auto i = Q._data[j];
        cout << i.firstarc << endl;
    }
    cout << Q.getedge(0, 1).data << endl;
    cout << Q.getedge(2, 1).data << endl;
    cout << Q.getedge(0, 0).exist << endl;
    Q.getedge(3, 4);
    cout << Q.getedge(3, 4).exist << endl;
    Graph<int> *sp = &Q;
    sp->degree(0);
    cout << sp->vertex() << endl;
    }