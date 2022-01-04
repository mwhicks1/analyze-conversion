

#include "mst.h"




#define CONST_m1 10000
#define CONST_b 31415821
#define RANGE 2048
static int HashRange;

static int mult(int p, int q)
{
   int p1, p0, q1, q0;

   p1=p/10000; p0=p%10000;
   q1=q/10000; q0=q%10000;
   return (((p0*q1+p1*q0) % 10000)*10000 +p0*q0);
}

static int random2(int seed)
{
  int tmp;
  tmp = (mult(seed,31415821)+1);
  return tmp;
}

static int compute_dist(int i,int j, int numvert)
{
  int less, gt;
  if (i<j) {less = i; gt = j;} else {less = j; gt = i;}
  return (random2(less*numvert+gt) % 2048)+1;
}

static int hashfunc(unsigned int key)
{
  return ((key>>3) % HashRange);
}

static void AddEdges(int count1, Graph retval, int numproc, int perproc, int numvert, int j)
{
  Vertex tmp = ((void*)0);
  VertexArray helper [1] = {0};
  int i;

  for (i=0; i<numproc; i++) {
    helper[i] = retval->vlist[i];
  }

   { tmp = retval->vlist[j].starting_vertex; }
  for (; tmp; tmp=tmp->next)
    {
      for (i=0; i<numproc*perproc; i++)
        {
          int pn,offset,dist;
          Vertex dest = ((void*)0);
          Hash hash = ((void*)0);

          if (i!=count1)
            {
              dist = compute_dist(i,count1,numvert);
              pn = i/perproc;
              offset = i % perproc;
               { dest = ((helper[pn].block)+offset); }
              hash = tmp->edgehash;
              HashInsert(dist,(unsigned int) dest,hash);

            }
        }
      count1++;
    }
}

Graph MakeGraph(int numvert, int numproc)
{
  int perproc = numvert/numproc;
  int i,j;
  int count1;
  Vertex v = ((void*)0);
  Vertex tmp = ((void*)0);
  struct vert_st * block  = ((void*)0);
  Graph retval = ((void*)0);

  retval = calloc(1, sizeof(*retval));
  for (i=0; i<1; i++)
    {
      retval->vlist[i].starting_vertex = ((void*)0);
    }
  chatting("Make phase 2\n");
  for (j=numproc-1; j>=0; j--)
    {
      block = calloc(perproc, sizeof(*tmp));
      v = ((void*)0);
      for (i=0; i<perproc; i++)
        {
           { tmp = block+(perproc-i-1); }
          HashRange = numvert/4;
          tmp->mindist = 9999999;
          tmp->edgehash = MakeHash(numvert/4,hashfunc);
          tmp->next = v;
          v = tmp;
        }
       { retval->vlist[j].block = block; }
      retval->vlist[j].len = perproc;
       { retval->vlist[j].starting_vertex = v; }
    }

  chatting("Make phase 3\n");
  for (j=numproc-1; j>=0; j--)
    {
      count1 = j*perproc;
      AddEdges(count1, retval, numproc, perproc, numvert, j);
    }
  chatting("Make phase 4\n");

  chatting("Make returning\n");
  return retval;
}

void chatting(char * str) {
   { (printf)("%s", str); };
}




