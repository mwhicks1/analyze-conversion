

#include <stdlib.h>
#include "hash.h"

#define assert(num,a) if (!(a)) {printf("Assertion failure:%d in hash\n",num); exit(-1);}

static int remaining = 0;
static char *temp;



















#define localfree(sz)

Hash MakeHash(int size, int (*map)(unsigned int))
{
  Hash retval;
  int i;

  retval = (Hash) malloc(sizeof(*retval));
  retval->array = (HashEntry *) malloc(size*sizeof(HashEntry));
  for (i=0; i<size; i++)
    retval->array[i]=((void*)0);
  retval->mapfunc = map;
  retval->size = size;
  return retval;
}

void *HashLookup(unsigned int key, Hash hash)
{
  int j;
  HashEntry ent;

  j = (hash->mapfunc)(key);
  if (!(j>=0)) {printf("Assertion failure:%d in hash\n",1); exit(-1);};
  if (!(j<hash->size)) {printf("Assertion failure:%d in hash\n",2); exit(-1);};
  for (ent = hash->array[j];
       ent &&
           ent->key!=key;
       ent=ent->next);
  if (ent) return ent->entry;
  return ((void*)0);
}

void HashInsert(void *entry,unsigned int key,Hash hash)
{
  HashEntry ent;
  int j;

  if (!(!HashLookup(key,hash))) {printf("Assertion failure:%d in hash\n",3); exit(-1);};

  j = (hash->mapfunc)(key);
  ent = (HashEntry) malloc(sizeof(*ent));
  ent->next = hash->array[j];
  hash->array[j]=ent;
  ent->key = key;
  ent->entry = entry;
}

void HashDelete(unsigned key, Hash hash) {
  HashEntry tmp;
  int j = (hash->mapfunc)(key);
  HashEntry *ent = &hash->array[j];

  while (*ent && (*ent)->key != key) {
    ent = &(*ent)->next;
  }

  if (!(*ent)) {printf("Assertion failure:%d in hash\n",4); exit(-1);};

  tmp = *ent;
  *ent = (*ent)->next;
                ;
}




