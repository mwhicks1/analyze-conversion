/* For copyright information, see olden_v1.0/COPYRIGHT */


#include <stdlib.h>
#include "hash.h"
#pragma CHECKED_SCOPE ON

#define printf(...) _Unchecked { (printf)(__VA_ARGS__); }
#define assert(num,a) if (!(a)) {printf("Assertion failure:%d in hash\n",num); exit(-1);}

/*
static int remaining = 0;
static char *temp;

static char *localmalloc(int size) 
{
  char *blah;
  
  if (size>remaining) 
    {
      temp = (char *) malloc(32768);
      if (!temp) printf("Error! malloc returns null\n");
      remaining = 32768;
    }
  blah = temp;
  temp += size;
  remaining -= size;
  return blah;
}

#define localfree(sz)
*/

Hash MakeHash(int size, _Ptr<int(unsigned int)> map)
{
  Hash retval = NULL;
  int i;

  retval = malloc<struct hash>(sizeof(struct hash));
  retval->size = size,
    retval->array = malloc<HashEntry>(size*sizeof(HashEntry));
  for (i=0; i<size; i++)
    retval->array[i] = NULL;
  retval->mapfunc = map;
  return retval;
}

int HashLookup(unsigned int key, Hash hash)
{
  int j;
  HashEntry ent = NULL;

  j = (hash->mapfunc)(key);        /* 14% miss in hash->mapfunc */  
  assert(1,j>=0);
  assert(2,j<hash->size);
  for (ent = hash->array[j];       /* 17% miss in hash->array[j] */ /* adt_pf can't detect :( */
       ent &&                      /* 47% miss in ent->key */       /* adt_pf can detect :) */
           ent->key!=key; 
       ent=ent->next);             /* 8% miss in ent->next */       /* adt_pf can detect :) */
  if (ent) return ent->entry;
  return NULL;
}

void HashInsert(int entry,unsigned int key,Hash hash)
{
  HashEntry ent = NULL;
  int j;
  
  assert(3,!HashLookup(key,hash));
  
  j = (hash->mapfunc)(key);
  ent = malloc<struct hash_entry>(sizeof(*ent));
  ent->next = hash->array[j];
  hash->array[j]=ent;
  ent->key = key;
  ent->entry = entry;
}

void HashDelete(unsigned key, Hash hash) {
  HashEntry tmp = NULL;
  int j = (hash->mapfunc)(key);
  int size = hash->size;
  _Dynamic_check(j <= size);
  _Ptr<HashEntry> ent = 0; 
  _Unchecked { ent = &hash->array[j]; }

  while (*ent && (*ent)->key != key) {
    ent = &(*ent)->next;
  }

  assert(4, *ent);

  tmp = *ent;
  HashEntry temp_entry = (*ent)->next;
  *ent = temp_entry;
  free<struct hash_entry>(tmp);
}

  
  


