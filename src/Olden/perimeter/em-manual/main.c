


#include "perimeter.h"
#include <stdio.h>
#include <stdlib.h>

#define printf(...) _Unchecked { (printf)(__VA_ARGS__); }

#pragma CHECKED_SCOPE ON

static int adj(Direction d, ChildType ct)
{
  switch (d)
    {
    case north:
      return ((ct==northeast) || (ct==northwest));
    case south:
      return ((ct==southeast) || (ct==southwest));
    case east:
      return ((ct==northeast) || (ct==southeast));
    case west:
      return ((ct==southwest) || (ct==northwest));
    }
}

static ChildType reflect(Direction d, ChildType ct)
{
  if ((d==west) || (d==east))
    {
      switch(ct)
 {
 case northwest:
   return northeast;
 case northeast:
   return northwest;
 case southeast:
   return southwest;
 case southwest:
   return southeast;
#ifdef DEBUG



#endif
 }
    }
  switch(ct)
    {
    case northwest:
      return southwest;
    case northeast:
      return southeast;
    case southeast:
      return northeast;
    case southwest:
      return northwest;
#ifdef DEBUG



#endif
    }
}

int CountTree(QuadTree tree)
{
  QuadTree nw = tree->nw;
  QuadTree ne = tree->ne;
  QuadTree sw = tree->sw;
  QuadTree se = tree->se;

  if (nw==((void*)0) && ne==((void*)0) && sw==((void*)0) && se==((void*)0))
    return 1;
  else
    return CountTree(nw) + CountTree(ne) + CountTree(sw) +
      CountTree(se);
}

static QuadTree child(QuadTree tree, ChildType ct)
{
  switch(ct)
    {
    case northeast:
      return tree->ne;
    case northwest:
      return tree->nw;
    case southeast:
      return tree->se;
    case southwest:
      return tree->sw;
    default:
#ifdef DEBUG


#endif
      return 0;
    }
}

static QuadTree gtequal_adj_neighbor(QuadTree tree, Direction d)
{
  QuadTree q = ((void*)0);
  QuadTree parent = tree->parent;
  ChildType ct;

  ct=tree->childtype;
  if ((parent!=((void*)0)) && adj(d,ct))
    q=gtequal_adj_neighbor(parent,d);
  else q=parent;
  if (q && q->color==grey) {
    return child(q,reflect(d,ct));
  }
  else return q;
}

static int sum_adjacent(QuadTree p, ChildType q1, ChildType q2, int size)
{
  if (p->color==grey)
    {
      return sum_adjacent(child(p,q1),q1,q2,size/2) +
 sum_adjacent(child(p,q2),q1,q2,size/2);
    }
  else if (p->color==white)
    {
      return size;
    }
  else return 0;
}

int perimeter(QuadTree tree, int size)
{
  int retval = 0;
  QuadTree neighbor = ((void*)0);

  if (tree->color==grey)
    {
      QuadTree child = ((void*)0);
#ifdef FUTURES

#endif

#ifndef FUTURES
      child = tree->sw;
      retval += perimeter(child,size/2);
      child = tree->se;
      retval += perimeter(child,size/2);
      child = tree->ne;
      retval += perimeter(child,size/2);
      child = tree->nw;
      retval += perimeter(child,size/2);
#else












#endif
    }
  else if (tree->color==black)
    {

      neighbor=gtequal_adj_neighbor(tree,north);
      if ((neighbor==((void*)0)) || (neighbor->color==white)) retval+=size;
      else if (neighbor->color==grey)
 retval+=sum_adjacent(neighbor,southeast,southwest,size);

      neighbor=gtequal_adj_neighbor(tree,east);
      if ((neighbor==((void*)0)) || (neighbor->color==white)) retval+=size;
      else if (neighbor->color==grey)
 retval+=sum_adjacent(neighbor,southwest,northwest,size);

      neighbor=gtequal_adj_neighbor(tree,south);
      if ((neighbor==((void*)0)) || (neighbor->color==white)) retval+=size;
      else if (neighbor->color==grey)
 retval+=sum_adjacent(neighbor,northwest,northeast,size);

      neighbor=gtequal_adj_neighbor(tree,west);
      if ((neighbor==((void*)0)) || (neighbor->color==white)) retval+=size;
      else if (neighbor->color==grey)
 retval+=sum_adjacent(neighbor,northeast,southeast,size);
    }
  return retval;
}

extern int dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));

int main(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
  QuadTree tree = ((void*)0);
  int count;
  int level;

#ifndef TORONTO
#ifdef FUTURES

#else

#endif
#endif

#ifdef DEBUG

#endif

  level = dealwithargs(argc,argv);

#ifndef TORONTO


#else
  _Unchecked { (printf)("Perimeter with %d levels on %d processors\n",level,NumNodes); };
  tree=MakeTree(2048*1024,0,0,0,NumNodes-1,((void*)0),southeast,level);
#endif

#ifdef DEBUG

#endif

  count=CountTree(tree);
  _Unchecked { (printf)("# of leaves is %d\n",count); };

#ifndef TORONTO




#endif

#ifndef TORONTO

#else
  count=perimeter(tree,4096);
#endif

#ifndef TORONTO

#endif

  _Unchecked { (printf)("perimeter is %d\n",count); };

#ifndef TORONTO

#ifdef FUTURES

#endif
#endif

  exit(0);
}







