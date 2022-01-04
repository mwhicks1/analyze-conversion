











#include <stdlib.h>
#include "power.h"

Root build_tree(void)
{
  int i;
  Root t = ((void *)0);
  Lateral l = ((void *)0);

  t = (_Ptr<struct root>) malloc<struct root>(sizeof(*t));

  for (i=0; i<11; i++) {

    l = build_lateral(i*21,21);
    t->feeders[i]=l;
  }
  t->theta_R = 0.8;
  t->theta_I = 0.16;
  return t;
}

Lateral  build_lateral(int i, int num)
{
  Lateral l = ((void *)0);
  Branch b = ((void *)0);
  Lateral next = ((void *)0);

  if (num == 0) return ((void*)0);
  l = (_Ptr<struct lateral>) malloc<struct lateral>(sizeof(*l));

  next = build_lateral(i,num-1);
  b = build_branch(i*6,(num-1)*6,
    6);

  l->next_lateral = next;
  l->branch = b;
  l->R = 1/300000.0;
  l->X = 0.000001;
  l->alpha = 0.0;
  l->beta = 0.0;
  return l;
}

Branch  build_branch(int i, int j, int num)
{
  Leaf l = ((void *)0);
  Branch b = ((void *)0);

  if (num == 0) return ((void*)0);

  b = (_Ptr<struct branch>) malloc<struct branch>(sizeof(*b));


  b->next_branch= build_branch(i,j,num-1);

  for (i=0; i<12; i++) {
    l = build_leaf();
    b->leaves[i] = l;
  }


  b->R = 0.0001;
  b->X = 0.00002;
  b->alpha = 0.0;
  b->beta = 0.0;
  return b;
}

Leaf build_leaf(void) {
  Leaf l = ((void *)0);

  l = (_Ptr<struct leaf>) malloc<struct leaf>(sizeof(*l));
  l->D.P = 1.0;
  l->D.Q = 1.0;
  return l;
}
