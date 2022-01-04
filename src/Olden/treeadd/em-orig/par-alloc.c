




#ifndef TORONTO
#include "mem-ref.h"
#include "future-cell.h"
#endif

#include "tree.h"
extern void *malloc(unsigned);

tree_t *TreeAlloc (int level, int lo, int proc) {
  if (level == 0)
    return ((void*)0);
  else {
    struct tree *new;
    struct tree *right;
    struct tree *left;
    new = (struct tree *) malloc(sizeof(tree_t));
    left = TreeAlloc(level -1, lo+proc/2, proc/2);
    right=TreeAlloc(level-1,lo,proc/2);
    new->val = 1;
    new->left = (struct tree *) left;
    new->right = (struct tree *) right;
    return new;
  }
}
