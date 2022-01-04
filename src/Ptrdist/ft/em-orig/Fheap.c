





































#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Fheap.h"
#include "Fstruct.h"

#ifdef DO_INLINE
#define INLINE inline
#else
#define INLINE
#endif

static HeapP * hTable[10000];

void CombineLists(HeapP *h1, HeapP *h2);
void AddEntry(HeapP *h1, HeapP *h2);
HeapP * RemoveEntry(HeapP *h);
HeapP * NewHeap(Item *i);
void RemoveChild(HeapP *i);
void FixRank(HeapP *h, int delta);

       void
InitFHeap()
{
  int j;

  for(j = 0; j < 10000; j++)
  {
    hTable[j] = ((void*)0);
  }
}

       HeapP *
MakeHeap()
{
  return(((void*)0));
}

       Item *FindMin(HeapP * h)
{
  if(h == ((void*)0))
  {
    return(((void*)0));
  }
  else
  {
    return(((*(h)).item));
  }
}

       HeapP *Insert(HeapP * * h, Item * i)
{
  HeapP * h1;

  h1 = NewHeap(i);
  *h = Meld(*h, h1);
  return(h1);
}

       HeapP *Meld(HeapP * h1, HeapP * h2)
{
  if(h2 == ((void*)0))
  {
    return(h1);
  }
  if(h1 == ((void*)0))
  {
    return(h2);
  }
  CombineLists(h1, h2);
  if(LessThan(((*(h1)).item), ((*(h2)).item)))
  {
    return(h1);
  }
  else
  {
    return(h2);
  }
}




       HeapP *DeleteMin(HeapP * h)
{
  int r, rMax, j;
  HeapP * h1;
  HeapP * h2;
  HeapP * h3;
  HeapP * min;

  rMax = 0;

  if(h == ((void*)0))
  {
    return(((void*)0));
  }

  h1 = RemoveEntry(h);

  if(h1 == ((void*)0))
  {
    free(h);
    return(((void*)0));
  }




  if(h1 == ((*(h)).child))
  {
    ((*(h)).child) = ((void*)0);
  }




  h2 = h1;
  do
  {
    h3 = ((*(h2)).forward);

    ((*(h2)).forward) = h2;
    ((*(h2)).backward) = h2;
    ((*(h2)).parent) = ((void*)0);

    r = ((*(h2)).rank);
    ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 166, __extension__ __PRETTY_FUNCTION__); }));
    while(hTable[r] != ((void*)0))
    {
      if(LessThan(((*(hTable[r])).item), ((*(h2)).item)))
      {
        AddEntry(hTable[r], h2);
        h2 = hTable[r];
      }
      else
      {
        AddEntry(h2, hTable[r]);
      }
      hTable[r] = ((void*)0);
      r = ((*(h2)).rank);
      ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 180, __extension__ __PRETTY_FUNCTION__); }));
    }
    hTable[r] = h2;
    if(r > rMax)
    {
      rMax = r;
    }

    h2 = h3;
  }
  while(h2 != h1);




  if(((*(h)).child) != ((void*)0))
  {
    h2 = ((*(h)).child);
    do
    {
      h3 = ((*(h2)).forward);

      ((*(h2)).forward) = h2;
      ((*(h2)).backward) = h2;
      ((*(h2)).parent) = ((void*)0);

      r = ((*(h2)).rank);
      ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 207, __extension__ __PRETTY_FUNCTION__); }));
      while(hTable[r] != ((void*)0))
      {
        if(LessThan(((*(hTable[r])).item), ((*(h2)).item)))
        {
          AddEntry(hTable[r], h2);
          h2 = hTable[r];
        }
        else
        {
          AddEntry(h2, hTable[r]);
        }
        hTable[r] = ((void*)0);
        r = ((*(h2)).rank);
        ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 221, __extension__ __PRETTY_FUNCTION__); }));
      }
      hTable[r] = h2;
      if(r > rMax)
      {
        rMax = r;
      }

      h2 = h3;
    }
    while(h2 != ((*(h)).child));
  }





  for(j = 0; j <= rMax; j++)
  {
    if(hTable[j] != ((void*)0))
    {
      break;
    }
  }
  h1 = hTable[j];
  min = h1;
  hTable[j] = ((void*)0);
  j++;
  for(; j <= rMax; j++)
  {
    if(hTable[j] != ((void*)0))
    {
      CombineLists(h1, hTable[j]);
      if(LessThan(((*(hTable[j])).item), ((*(min)).item)))
      {
        min = hTable[j];
      }
      hTable[j] = ((void*)0);
    }
  }

  free(h);

  return(min);
}

       HeapP *DecreaseKey(HeapP * h, HeapP * i, int delta)
{
  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 269, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((i != ((void*)0)) ? 1 : 0), __extension__ ({ if (i != ((void*)0)) ; else __assert_fail ("i != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 270, __extension__ __PRETTY_FUNCTION__); }));

  if(!(((*(i)).parent) == ((void *)0)))
  {
    RemoveChild(i);
    CombineLists(h, i);
  }
  ((*(i)).item) = Subtract(((*(i)).item), delta);
  if(LessThan(((*(i)).item), ((*(h)).item)))
  {
    return(i);
  }
  else
  {
    return(h);
  }
}




       void
RemoveChild(HeapP * i)
{
  HeapP * parent;

  ((void) sizeof ((i != ((void*)0)) ? 1 : 0), __extension__ ({ if (i != ((void*)0)) ; else __assert_fail ("i != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 296, __extension__ __PRETTY_FUNCTION__); }));

  parent = ((*(i)).parent);

  ((void) sizeof ((parent != ((void*)0)) ? 1 : 0), __extension__ ({ if (parent != ((void*)0)) ; else __assert_fail ("parent != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 300, __extension__ __PRETTY_FUNCTION__); }));

  if((((*(parent)).child) == (i)))
  {
    if(((i) == ((*(i)).forward)))
    {
      ((*(parent)).child) = ((void*)0);
    }
    else
    {
      ((*(parent)).child) = ((*(i)).forward);
    }
  }
  (void)RemoveEntry(i);
  FixRank(parent, ((*(i)).rank) + 1);

  ((*(i)).forward) = i;
  ((*(i)).backward) = i;
  ((*(i)).parent) = ((void*)0);
}

       void
FixRank(HeapP * h, int delta)
{
  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 324, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((delta > 0) ? 1 : 0), __extension__ ({ if (delta > 0) ; else __assert_fail ("delta > 0", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 325, __extension__ __PRETTY_FUNCTION__); }));

  do
  {
    ((*(h)).rank) = ((*(h)).rank) - delta;
    h = ((*(h)).parent);
  }
  while(h != ((void*)0));
}

       HeapP *Delete(HeapP * h, HeapP * i)
{
  HeapP * h1;
  HeapP * h2;

  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 340, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((i != ((void*)0)) ? 1 : 0), __extension__ ({ if (i != ((void*)0)) ; else __assert_fail ("i != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 341, __extension__ __PRETTY_FUNCTION__); }));

  if(h == i)
  {
    return(DeleteMin(h));
  }

  if((((*(i)).parent) == ((void *)0)))
  {
     (void)RemoveEntry(i);
  }
  else
  {
    RemoveChild(i);
  }
  h1 = ((*(i)).child);
  if(h1 != ((void*)0))
  {
    do
    {
      h2 = ((*(h1)).forward);

      ((*(h1)).forward) = h1;
      ((*(h1)).backward) = h1;
      ((*(h1)).parent) = ((void*)0);

      CombineLists(h, h1);




      if(LessThan(((*(h1)).item), ((*(h)).item)))
      {
        h = h1;
      }

      h1 = h2;
    }
    while(h1 != ((*(i)).child));
  }

  free(i);
  return(h);
}














       void
CombineLists(HeapP * h1, HeapP * h2)
{
  HeapP * h;

  ((void) sizeof (((h1 != ((void*)0)) && (h2 != ((void*)0))) ? 1 : 0), __extension__ ({ if ((h1 != ((void*)0)) && (h2 != ((void*)0))) ; else __assert_fail ("(h1 != NULL) && (h2 != NULL)", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 404, __extension__ __PRETTY_FUNCTION__); }));

  h = h1;

  ((*(((*(h1)).forward))).backward) = h2;
  ((*(((*(h2)).forward))).backward) = h1;
  h = ((*(h1)).forward);
  ((*(h1)).forward) = ((*(h2)).forward);
  ((*(h2)).forward) = h;
}














       void
AddEntry(HeapP * h1, HeapP * h2)
{
  ((void) sizeof (((h1 != ((void*)0)) && (h2 != ((void*)0))) ? 1 : 0), __extension__ ({ if ((h1 != ((void*)0)) && (h2 != ((void*)0))) ; else __assert_fail ("(h1 != NULL) && (h2 != NULL)", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 431, __extension__ __PRETTY_FUNCTION__); }));

  if(((*(h1)).child) == ((void*)0))
  {
    ((*(h1)).child) = h2;
  }
  else
  {
    CombineLists(((*(h1)).child), h2);
  }
  ((*(h2)).parent) = h1;
  ((*(h1)).rank) = ((*(h1)).rank) + ((*(h2)).rank) + 1;
}















       HeapP *RemoveEntry(HeapP * h)
{
  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/Fheap.c", 461, __extension__ __PRETTY_FUNCTION__); }));

  if(((h) == ((*(h)).forward)))
  {
    return(((*(h)).child));
  }

  ((*(((*(h)).forward))).backward) = ((*(h)).backward);
  ((*(((*(h)).backward))).forward) = ((*(h)).forward);

  return(((*(h)).forward));
}














       HeapP *NewHeap(Item * i)
{
  HeapP * h;

  h = (HeapP *)malloc(sizeof(HeapP));

  if(h == ((void*)0))
  {
    fprintf(stderr, "Oops, could not malloc\n");
    exit(1);
  }
  ((*(h)).item) = i;
  ((*(h)).parent) = ((void*)0);
  ((*(h)).child) = ((void*)0);
  ((*(h)).forward) = h;
  ((*(h)).backward) = h;
  ((*(h)).rank) = 0;
  ((*(h)).marked) = 0;

  return(h);
}

       Item *ItemOf(HeapP * h)
{
  return(((*(h)).item));
}

       HeapP *Find(HeapP * h, Item * item)
{
  HeapP * h1;
  HeapP * h2;

  if(h == ((void*)0))
  {
    return(((void*)0));
  }

  h1 = h;
  do
  {
    if(Equal(((*(h1)).item), item))
    {
      return(h1);
    }
    else if(LessThan(((*(h1)).item), item))
    {
      h2 = Find(((*(h1)).child), item);
      if(h2 != ((void*)0))
      {
        return(h2);
      }
    }
    h1 = ((*(h1)).forward);
  }
  while(h1 != h);

  return(((void*)0));
}

