

#include "stdio.h"

struct hash_entry {
  unsigned int key;
  void *entry;
  _Ptr<struct hash_entry> next;
};
typedef _Ptr<struct hash_entry> HashEntry;

struct hash {
  _Array_ptr<HashEntry> array : count(size);
  _Ptr<int (unsigned int)> mapfunc;
  int size;
};
typedef _Ptr<struct hash> Hash;

Hash MakeHash(int size, _Ptr<int (unsigned int)> map);
void *HashLookup(unsigned int key, Hash hash);
void HashInsert(void *entry, unsigned int key, Hash hash);
void HashDelete(unsigned int key, Hash hash);