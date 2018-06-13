// #include "dbg.h"
#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct malloc_boundry_struct
{
    union {
        struct malloc_boundry_struct *last;
        struct malloc_boundry_struct *head;
    };
    int tag;
    int size;
    struct malloc_boundry_struct *next;
} word;

#define foot(p) (p + p->size - 1)
#define lastfoot(p) (p - 1)
//Do remember that the point p is a word*, which means p-1 is p-4(int*);

typedef struct malloc_boundry_struct *Space;

Space init_memory(int size)
{
    Space r = (Space)malloc(sizeof(int) * 4 * size);
    r->last = 0;
    r->next = 0;
    r->tag = 0;
    r->size = size;
    foot(r)->head = r;
    foot(r)->tag = 0;
    return r;
}

//The memory is divided into a double link table. 

Space malloc_firstmatch(int size, Space &memory)
{
    auto now = memory;

    do
    {
        if (!now->tag)
        {
            int size_remain = now->size - size;
            if (size_remain >= 3)
            {
                //new block
                Space block_new = now + size;
                block_new->tag = 0;
                block_new->size = size_remain;
                block_new->last = now;
                block_new->next = now->next;
                foot(block_new)->head = block_new;

                //malloced block
                now->size = size;
                now->tag = 1;
                now->next = block_new;
                foot(now)->head = now;
                foot(now)->tag = 1;

                //return
                memory = foot(now);
                return now;
            }
            else if (size_remain >= 0)
            {
                //just use this block;
                now->tag = 1;
                foot(now)->tag = 1;
                memory = now->next;
                return now;
            }
            continue;
        }
        else
            now = now->next;
    } while (now != memory);
    return nullptr;
    //when using best malloc or worst malloc, a resort with complexity of O(n) should be added.
}

void* mmalloc(int size,Space &memory)
{
    //a size is 4*sizeof(int);
    return (void *)malloc_firstmatch(size + 2, memory);
}

Space mfree(Space &memory)
{
    //case 1: the only block
    if(memory->last==memory)
    {
        memory->tag = 0;
        return memory;
    }

    //case last is used
    if(memory->last->tag)
    {

        //case next is used
        if(memory->next->tag)
        {//this only
            memory->tag = 0;
            return memory;
        }else
        //case last is unused 
        {//this and last
            memory->last->size += memory->size;
            memory->last->next = memory->next;

            foot(memory)->tag = 0;
            foot(memory)->head= memory->last;

            memory->next->last = memory->last;
             memory=memory->last;
             return memory;
        }
    }else
    //case next is unused
    {
        if(memory->last->tag)
        //case last is used
        {//this and next merged
            memory->next->next->last = memory;

            memory->size += memory->next->size;
            memory->tag = 0;
            memory->next = memory->next->next;

            foot(memory)->tag = 0;
            foot(memory)->head = memory;

            return memory;
        }else
        //case last is unused
        {//this last and next is merged
            memory->last->size += memory->size;
            memory->last->size += memory->next->size;

            memory->last->next = memory->next->next;

            memory->last = memory->last->last;

            //next
            memory->next->next->last = memory->last;
            memory = memory->last;
            return memory;
        }
    }
    return nullptr;
}

#include<vector>

struct buddy_node
{
    struct buddy_node* last;
    struct buddy_node* next;
    int tag;
    int size;
};

struct buddy_table
{
    int size;
    struct buddy_node* baseptr;
    vector<struct buddy_node *> list;
};

#include<algorithm>
#include<cmath>

int fastpow(int base, int index)
{
    if(!index)
        return 1;
    int sigindex = index & 1;
    int temp = base;
    while (index > 1)
    {
        index >>= 1;
        temp *= temp;
    }
    if(sigindex)
        return temp * base;
    return temp;
}

struct buddy_table init_buddy_system(int size)
{
    auto r = (struct buddy_node *)malloc(fastpow(2, size)*sizeof(buddy_node));
    if(r)
    {
        struct buddy_table result;
        result.size = size;
        while(size-->0)
        {
            result.list.push_back(nullptr);
        }
        result.list.push_back(r);
        //list[0] is useless and list[i] is size i;
        result.baseptr = r;
        return result;
    }
}

struct buddy_node *malloc_buddy(int size, struct buddy_table &buddy_table)
{
    //there is an error in the book's code, the inserting process for the remain block in ti the blank table is wrong.
    if(size>buddy_table.size)
        return nullptr;
    if(buddy_table.list[size])
    {
        auto a = buddy_table.list[size];
        if (buddy_table.list[size]->next == buddy_table.list[size])
            buddy_table.list[size] = nullptr;
        else
        {
            buddy_table.list[size]->last->next = buddy_table.list[size]->next;
            buddy_table.list[size]->next->last = buddy_table.list[size]->last;
            buddy_table.list[size] = buddy_table.list[size]->next;
        }
        return a;
    }
    if(size<buddy_table.size)
    {
        struct buddy_node *result;
        if (result=malloc_buddy(size, buddy_table))
        {
            //use the first half;
            int realsize = fastpow(2, size);

            result->size = realsize;
            result->tag = 1;

            auto n = result->next;
            result->next = result + realsize;
            result->next->next = n;
            result->next->last = result;
            result->next->size = size;
            result->next->tag = 0;

            //add the other half to the table;
            if(buddy_table.list[size])
            {
                result->next->next = buddy_table.list[size];
                result->next->last = buddy_table.list[size];
                buddy_table.list[size]->next = result;
            }
            else
            {
                buddy_table.list[size] = result->next;
                result->next->next = result->next;
            }

            return result;
        }
    }
    return nullptr;
}

struct buddy_node* merge_buddy(struct buddy_node* tgt, struct buddy_table buddy_table)
{
    //merge two node with the same size and tag == 0;
    //return the point of merged node;
    //only merge one level;
    //if failed, return nullptr;

    //find buddy node
    auto rsize = tgt - buddy_table.baseptr;
    struct buddy_node *buddy;
    auto p = rsize % fastpow(2, tgt->size + 1);
    if (p)
    {
        //this is upper half;
        buddy=tgt+fastpow(2,tgt->size);
    }
    else
    {
        //this is the back half
        buddy=tgt-fastpow(2,tgt->size);
    }

    if(tgt->tag||buddy->tag)
    {
        return nullptr;
    }

    //del tgt

    if (tgt->next == tgt)
    {
        buddy_table.list[tgt->size] = nullptr;
    }
    else
    {
        tgt->last->next = tgt->next;
        tgt->next->last = tgt->last;
    }

    //del buddy
    if(buddy->next == buddy)
    {
        buddy_table.list[buddy->size] = nullptr;
    }
    else
    {
        buddy->last->next = buddy->next;
        buddy->next->last = buddy->last;
    }

    //merge
    struct buddy_node *head = (struct buddy_node *)(p - rsize % fastpow(2, tgt->size + 1));
    head->tag = 0;
    head->size = tgt->size+1;

    //add merge result
    if(buddy_table.list[head->size])
    {
        head->last = buddy_table.list[head->size];
        head->next = buddy_table.list[head->size]->next;
        buddy_table.list[head->size]->next = head;
    }else
    {
        buddy_table.list[head->size] = head;
        head->next = head;
    }

    //return
    return head;
}

struct buddy_node* free_buddy(struct buddy_node* tgt, struct buddy_table& table)
{
    tgt->tag = 0;
    while(tgt=merge_buddy(tgt,table))
    {
        //loop;
    }
    return tgt;
}

int
main()
{
    auto memory = init_memory(400);
    auto p=malloc_firstmatch(200,memory);
    auto b = init_buddy_system(10);

}

//did not work on garbage collect and storage shrink.
//have not been tested