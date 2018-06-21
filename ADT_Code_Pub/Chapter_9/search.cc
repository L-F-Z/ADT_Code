//https://github.com/L-F-Z/ADT_Code
//https://github.com/AugustusWillisWang/Notes/tree/master/DataStructure/ooadt
//Developed by AugustusWillisWang

// #include "dbg.h"
#include <cstdlib>
#include <iostream>

template <class T>
int search_sequential_lineararray(T *array, int size, T tgt)
{
    int found = -1;
    while (size-- > 0)
    {
        if (*(array + size) == tgt)
            return size;
    }
    return found;
}

template <class T>
int search_sequential_lineararray_withscout(T *array, int size, T tgt)
{
    *(array) = tgt;
    while ((array + size) != tgt)
    {
        size--;
    }
    return size;
    //Do be aware that array[0] should be preserved.
}

template <class T>
int search_binary_lineararray(T *array, int size, T tgt)
{
    int low = 0;
    int high = size - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) >> 1; // (low+high)/2
        T temp = *(array + mid);
        if (temp == tgt)
        {
            return mid;
        }
        if (temp > tgt)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int testdata[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
int weight[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

template <class T>
struct bintree_node_for_search
{
    T value;
    struct bintree_node_for_search *left;
    struct bintree_node_for_search *right;
    int mark;
    struct bintree_node_for_search *addleft(T newvalue, int mark = 0)
    {
        this->left = new struct bintree_node_for_search<T>;
        this->left->value = newvalue;
        this->left->left = 0;
        this->left->right = 0;
        this->left->mark = mark;
        return left;
    }
    struct bintree_node_for_search *addright(T newvalue, int mark = 0)
    {
        this->right = new struct bintree_node_for_search<T>;
        this->right->value = newvalue;
        this->right->left = 0;
        this->right->right = 0;
        this->right->mark = mark;
        return right;
    }
    int print(int indent = 0)
    {
        for (int i = 0; i < indent; i++)
        {
            std::cout << " ";
        }
        std::cout << this->value << std::endl;
        if (this->left)
            this->left->print(2 + indent);
        if (this->right)
            this->right->print(2 + indent);
    }
};

template <class T>
bool search_bintree(bintree_node_for_search<T> *pbintree, T tgt)
{
    while (pbintree)
    {
        if (pbintree->value == tgt)
            return 1;
        if (pbintree->value < tgt)
            pbintree = pbintree->right;
        else
            pbintree = pbintree->left;
    }
    return 0;
}

template <class T, class W>
bintree_node_for_search<T> *setup_nearly_optimal_bintree(T *src, W *src_weight, int size)
{
    if (size < 1)
        return nullptr;
    // if(size==1)
    // {
    //     bintree_node_for_search<T> *result = new bintree_node_for_search<T>;
    //     result->value = src[0];
    //     result->left = 0;
    //     result->right =0;
    //     return result;
    // }

    W weight_sum[size + 2];       //added 0 and 0 at the beginning and the end
    W weight_sum_delta[size + 2]; //added 0 and 0 at the beginning and the end
    weight_sum[0] = 0;
    weight_sum[size + 1] = 0;
    for (int i = 1; i < size + 1; i++)
    {
        weight_sum[i] = src_weight[i - 1] + weight_sum[i - 1];
    }

    // for (int i = 0; i < size + 1; i++)
    // {
    //     std::cout << weight_sum[i] << std::endl;
    // }

    for (int i = 0; i < size + 1; i++)
    {
        weight_sum_delta[i] = abs(weight_sum[size] - weight_sum[i + 1] - weight_sum[i]);
    }

    // for (int i = 0; i < size; i++)
    // {
    //     std::cout<<weight_sum_delta[i]<<std::endl;
    // }

    int min = weight_sum_delta[0];
    int minfound = 0;
    for (int i = 0; i < size; i++)
    {
        if (weight_sum_delta[i] < min)
        {
            min = weight_sum_delta[i];
            minfound = i;
        }
    }

    //spilt at minfound;
    int spilt = minfound;
    bintree_node_for_search<T> *result = new bintree_node_for_search<T>;
    result->value = src[spilt];
    result->left = setup_nearly_optimal_bintree<T, W>(src, src_weight, spilt);
    result->right = setup_nearly_optimal_bintree<T, W>(src + spilt + 1, src_weight + spilt + 1, size - spilt - 1);

    return result;
}

// template <class T, class W>
// bintree_node_for_search<T> *addto_balanced_bintree(T src, bintree_node_for_search<T> &*pbintree_root, int size)
// {
//     auto pbintree = pbintree_root;
//     // pbintree_root may be changed;
//     if (!pbintree)
//     {
//         auto p = new bintree_node_for_search<T>;
//         p->value = src;
//         p->left = 0;
//         p->right = 0;
//         p->mark = 0;
//         return p;
//     }

//     bintree_node_for_search<T> *father = 0;
//     bintree_node_for_search<T> *grandfather = 0;

//     enum move
//     {
//         left,
//         right
//     };

//     enum move lastmove;

//     while (1)
//     {
//         if (src == pbintree->value)
//         {
//             //already exist in the tree;
//             //do nothing;
//             return pbintree;
//         }

//         if (src < pbintree->value)
//         {
//             //to left
//             if (pbintree->left)
//             {
//                 grandfather = father;
//                 father = pbintree;
//                 lastmove = left;
//                 pbintree = pbintree->left;
//                 continue;
//             }
//             else
//             {
//                 //AVL rotate TODO
//             }
//         }
//         else
//         {
//             //to right
//             if (pbintree->right)
//             {
//                 grandfather = father;
//                 father = pbintree;
//                 lastmove->right;
//                 pbintree = pbintree->right;
//                 continue;
//             }
//             else
//             {
//                 // AVL rotate TODO
//             }
//         }
//     }
// }

// {
//     //AVL rotate, add to left
//     pbintree->left = new bintree_node_for_search<T>;
//     pbintree = pbintree->left;
//     pbontree->left->value = src;
//     pbontree->left->left = 0;
//     pbontree->left->right = 0;
//     pbontree->left->mark = 0;
//     if (pbintree->right) //have another side, do nothing but change the mark.
//     {
//         pbintree->mark++;
//         return pbintree->left;
//     }
//     else //added a new level, may need rotate
//     {
//         pbintree->mark++;
//         if (father)
//         {
//             father->mark++;
//             if(lastmove==left)
//             {
//                 father->mark++;
//             }
//             else //lastmove==right
//             {
//                 father->mark--;
//             }

//             //judge if rotate is needed
//             if(abs(father->mark)>1)
//             {
//                 //need rotate
//                 if (father->mark==2)
//                 {
//                     // 0-l-l
//                     if(father==pbintree_root)
//                     {
//                         pbinrtee_root = now;//root changed
//                         now->right = father;
//                         now->mark = 0;
//                         father->mark = 0;
//                     }else
//                     {
//                         // have grandfather
//                         grandfather->
//                     }
//                 }
//                 else //(father->mark==-2)
//                 {
//                     // 0-r-l
//                 }
//             }else
//             {
//                 //no rotate, just return;
//                 return pbintree->left;
//             }
//         }
//     }
// }

int taller = 0;

template <class T>
bintree_node_for_search<T> *addto_balanced_bintree(T src, bintree_node_for_search<T> *&pnode, int &taller)
{
    //use global var taller to help with recursion.
    //init taller as 0 before start.

    if (!pnode) //if call addto_balanced_bintree to a nullptr, add a new node, change the ptr and mark taller as 1;
    {
        //init new bintree_node_for_search
        auto pnode = new bintree_node_for_search<T>;
        pnode->value = src;
        pnode->left = 0;
        pnode->right = 0;
        pnode->mark = 0;
        taller = 1;
        return pnode;
    }

    if (pnode->value == src)
    {
        //already have it
        taller = 0;
        return nullptr;
    }

    if (src < pnode->value) //go to left
    {
        auto m = addto_balanced_bintree(src, pnode->left, taller);
        if (!m)
            return 0;
        if (taller)
        {
            if (pnode->mark == 1)
            {
                avl_rotate_left(pnode);
                taller = 0;
                pnode->mark = 0;
            }
            else if (pnode->mark == 0)
            {
                pnode->mark = 1;
                taller = 1;
            }
            else if (pnode->mark == -1)
            {
                pnode->mark == 0;
                taller = 0;
            }
        }
        else
        {
            //do nothing
        }
    }
    else //src>pnode->value: go to right
    {
        auto m = addto_balanced_bintree(src, pnode->right, taller);
        if (!m)
            return 0;
        if (taller)
        {
            if (pnode->mark == -1)
            {
                avl_rotate_right(pnode);
                taller = 0;
                pnode->mark = 0;
            }
            else if (pnode->mark == 0)
            {
                pnode->mark = -1;
                taller = 1;
            }
            else if (pnode->mark == 1)
            {
                pnode->mark == 0;
                taller = 0;
            }
        }
        else
        {
            //do nothing
        }
    }
}

template <class T>
int avl_rotate_left(bintree_node_for_search<T> *&pnode)
{
    auto F = pnode;
    auto L = pnode->left;
    auto R = pnode->right;
    auto LL = pnode->left->left;
    auto LR = pnode->left->right;

    //L->mark=1/-1 controlled how to rotate
    if (L->mark == 1) //LL
    {
        pnode = L;
        L->left = LL;
        L->right = F;
        F->left = LR;
        F->right = R;
        L->mark = 0;
        F->mark = 0;
    }
    else //LR
    {
        auto LRL = pnode->left->right->left;
        auto LRR = pnode->left->right->right;
        pnode = LR;
        LR->left = L;
        LR->right = F;
        L->left = LL;
        L->right = LRL;
        F->left = LRR;
        F->right = R;
        LR->mark = 0;
        L->mark = 0;
        F->mark = -1;
    }
}

template <class T>
int avl_rotate_right(bintree_node_for_search<T> *&pnode)
{
    auto F = pnode;
    auto L = pnode->left;
    auto R = pnode->right;
    auto RL = pnode->right->left;
    auto RR = pnode->right->right;

    //R->mark=1/-1 controlled how to rotate
    if (R->mark == -1) //RR
    {
        pnode = R;
        R->right = RR;
        R->left = F;
        F->right = RL;
        F->left = L;
        R->mark = 0;
        F->mark = 0;
    }
    else //RL
    {
        auto RLR = pnode->right->left->right;
        auto RLL = pnode->right->left->left;
        pnode = RL;
        RL->right = R;
        RL->left = F;
        R->right = RR;
        R->left = RLR;
        F->right = RLL;
        F->left = L;
        RL->mark = 0;
        R->mark = -1;
        F->mark = 0;
    }
}

//AVL del?

//B

template <class Keyword_type, int node_size>
struct B_tree_node
{
    Keyword_type keyword[node_size];
    struct B_tree_node<Keyword_type, node_size> *point[node_size + 1];
    int size;
};

//B+

//Key

struct digital_search_tree_node
{
    char value;
    struct digital_search_tree_node *next;
    struct digital_search_tree_node *child;
};

struct digital_search_tree_node *search_digital_search_tree(char *src, struct digital_search_tree_node *pdstree)
{
    int i = 0;
    while (src[i] != 0)
    {
        if (!pdstree)
            return 0;
        if (pdstree->value == 0)
            return 0;
        while (pdstree && pdstree->value != src[i])
        {
            pdstree = pdstree->next;
        }
        if (pdstree)
        {
            //found
            i++;
            pdstree = pdstree->child;
            continue;
        }
        return 0;
    }
    if (pdstree->value == 0)
        return pdstree;
    return 0;
}

struct digital_search_tree_node *addto_digital_search_tree(char *src, struct digital_search_tree_node *&pdstree)
{
    auto now = pdstree;
    struct digital_search_tree_node *last = 0;
    int i = 0;

    if (src[i] == 0)
    {
        if (pdstree->value == 0)
            return 0;
        auto a = new struct digital_search_tree_node;
        a->value = 0;
        a->next = pdstree;
        a->child = 0;
        pdstree = a;
    }

    if (!now)
    {
        pdstree = new struct digital_search_tree_node;
        pdstree->value = src[i];
        pdstree->next = 0;
        pdstree->child = 0;
        addto_digital_search_tree(src + 1, pdstree->child);
    }
    while (now && now->value < src[i])
    {
        last = now;
        now = now->next;
    }
    if (now)
    {
        if (last == 0)
        {
            auto a = new struct digital_search_tree_node;
            a->next = pdstree;
            a->value = src[i];
            pdstree = a;
        }
        else
        {
            if (now->value == src[i])
            {
                addto_digital_search_tree(src + 1, now->child);
            }
            else
            {
                //now->value>src[i];
                //insert a node here
                auto a = new struct digital_search_tree_node;
                a->next = now;
                a->value = src[i];
                last->next = a;
                a->child = 0;
                addto_digital_search_tree(src + 1, a->child);
            }
        }
    }
    last->next = new struct digital_search_tree_node;
    now = last->next;
    now->value = src[i];
    now->next = 0;
    now->child = 0;
    addto_digital_search_tree(src + 1, now->child);
}

//Trie

enum trie_type
{
    type_node,
    type_str
};

template <int node_size>
struct trie_node
{
    bool type[node_size];
    union {
        struct trie_node *pnode;
        char *str;
    } point[node_size];

    void init()
    {
        for (int i = 0; i < node_size; i++)
        {
            type[i] = type_node;
            point[i] = 0;
        }
    }
};

int map_char_to_trie_int(char src)
{
    return src - 'a';
}

template <int node_size>
int addto_trie_tree(const char *str, struct trie_node<node_size> *&pnode, int map_char_to_trie_int(char))
{
    auto now = pnode;
    if (!now)
    {
        pnode = new struct trie_node<node_size>;
        pnode->init();
        return addto_trie_tree<node_size>(str, pnode);
    }
    int i = 0;
    auto a = map_char_to_trie_int(str[i]);
    while (str[i])
    {
        switch (now->type[a])
        {
        case type_node:
            if (now->point[a])
            {
                //already have something
                i++;
                now = now->point[a];
                continue;
            }
            else
            {
                //add to empty position
                now->type[a] = type_str;
                now->point[a] = str;
                return 0;
            }
            break;
        case type_str:
            if (!strcmp(str, now->point[i]))
            {
                //add new node;
                //combine the original str;
                auto n = new struct trie_node<node_size>;
                n->init();
                n->type[now->point[a][i + 1]] = type_str;
                n->point[now->point[a][i + 1]] = now->point[a];
                n->type[now->str[i + 1]] = type_str;
                n->point[now->str[i + 1]] = str;

                //....
                now->point[a] = n;
                now->type[a] = type_node;
                return 0;
            }
            else
            {
                //do nothing
            }
            break;
        }
    }
}

template <int node_size>
bool findin_trie_tree(const char *str, struct trie_node<node_size> *pnode, int map_char_to_trie_int(char))
{
    int i=0;
    while(1)
    {
        auto a = map_char_to_trie_int(str[i]);
        if(pnode->type[a]==type_str)
        {
            if(!strcmp(pnode->point[a],str))
            {
                return true;
            }else
            {
                return false;
            }
        }else
        {
            if(pnode->point[a])
            {
                pnode=pnode->point[a];
                i++;
                continue;
            }else{
                return false;
            }
        }
    }
}

    //RedBlackTree

    int main()
    {
        using namespace std;
        cout << search_binary_lineararray<int>(testdata, 10, 12) << endl;
        cout << search_sequential_lineararray<int>(testdata, 10, 12) << endl;
        auto p = setup_nearly_optimal_bintree<int, int>(testdata, weight, 10);
        p->print();
        cout << search_bintree<int>(p, 12);
    }