

#include "tsp.h"

#pragma CHECKED_SCOPE ON
#define conquer_thresold 150  
extern int flag;

void print_tree(Tree t)
{
  Tree left = ((void*)0);
  Tree right = ((void*)0);

  double x,y;

  if (!t) return;
  x = t->x; y = t->y;
  _Unchecked { printf("x=%f,y=%f\n",x,y); };
  left = t->left; right=t->right;
  print_tree(left);
  print_tree(right);
}

void print_list(Tree t)
{
  Tree tmp = ((void*)0);
  double x,y;

  if (!t) return;
  x = t->x; y = t->y;
  _Unchecked { printf("%f %f\n",x,y); };
  for (tmp=t->next; tmp!=t; tmp=tmp->next)
    {
    x = tmp->x; y = tmp->y;
    _Unchecked { printf("%f %f\n",x,y); };
    }
}

int main(int argc,_Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
  Tree t = ((void*)0);
  int num;

  num=dealwithargs(argc,argv);

  _Unchecked { printf("Building tree of size %d\n",num); };
  t=build_tree(num,0,0,NumNodes,0.0,1.0,0.0,1.0);
  if (!flag) _Unchecked { printf("Past build\n"); };
  if (flag) _Unchecked { printf("newgraph\n"); };
  if (flag) _Unchecked { printf("newcurve pts\n"); };

  _Unchecked { printf("Call tsp(t, %d, %d)\n", 150, NumNodes); };
  tsp(t,150, NumNodes);

  if (flag) print_list(t);
  if (flag) _Unchecked { printf("linetype solid\n"); };

  return 0;
}
