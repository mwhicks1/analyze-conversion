













#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "types.h"
#include "hcg.h"
#include "channel.h"

_Array_ptr<nodeHCGType> HCG = ((void *)0);
_Array_ptr<unsigned long> storageRootHCG = ((void *)0);
_Array_ptr<unsigned long> storageHCG = ((void *)0);
unsigned long storageLimitHCG;








void
AllocHCG(void)
{
    HCG = (_Array_ptr<nodeHCGType>)malloc<nodeHCGType>((channelNets + 1) * sizeof(nodeHCGType));
    storageRootHCG = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelNets + 1) * (channelNets + 1) * sizeof(unsigned long));
    storageHCG = storageRootHCG;
    storageLimitHCG = (channelNets + 1) * (channelNets + 1);
}

void
FreeHCG(void)
{
    free<nodeHCGType>(HCG);
    free<unsigned long>(storageRootHCG);
    storageLimitHCG = 0;
}

void
BuildHCG(void)
{
    unsigned long net;
    unsigned long which;
    unsigned long constraint;
    unsigned long first;
    unsigned long last;
    unsigned long check;
    unsigned long add;




    AllocHCG();




    for (net = 1; net <= channelNets; net++) {
 first = FIRST[net];
 last = LAST[net];
 constraint = 0;
 HCG[net].netsHook = storageHCG;
 for (which = 1; which <= channelNets; which++) {
     if (((FIRST[which] < first) && (LAST[which] < first)) || ((FIRST[which] > last) && (LAST[which] > last))) {



     }
     else {






  add = 1;
  for (check = 0; check < constraint; check++) {
      if (HCG[net].netsHook[check] == which) {
   add = 0;
   break;
      }
  }
  ((void) sizeof ((add) ? 1 : 0), __extension__ ({ if (add) ; else __assert_fail ("add", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/hcg.c", 95, __extension__ __PRETTY_FUNCTION__); }));




  ((void) sizeof ((storageLimitHCG > 0) ? 1 : 0), __extension__ ({ if (storageLimitHCG > 0) ; else __assert_fail ("storageLimitHCG > 0", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/hcg.c", 100, __extension__ __PRETTY_FUNCTION__); }));
  HCG[net].netsHook[constraint] = which;
  storageHCG++;
  storageLimitHCG--;
  constraint++;
     }
 }
 HCG[net].nets = constraint;
    }
}

void
DFSClearHCG(_Array_ptr<nodeHCGType> HCG)
{
    unsigned long net;

    for (net = 1; net <= channelNets; net++) {
 HCG[net].netsReached = 0;
    }
}

void
DumpHCG(_Array_ptr<nodeHCGType> HCG)
{
    unsigned long net;
    unsigned long which;

    for (net = 1; net <= channelNets; net++) {
 printf("[%d]\n", net);
 for (which = 0; which < HCG[net].nets; which++) {
     printf("%d ", HCG[net].netsHook[which]);
 }
 printf("\n\n");
    }
}

void
NoHCV(_Array_ptr<nodeHCGType> HCG, unsigned long select, _Array_ptr<unsigned long> netsAssign, _Array_ptr<unsigned long> tracksNoHCV)
{
    unsigned long track;
    unsigned long net;
    unsigned long which;
    unsigned long ok;

    for (track = 1; track <= channelTracks; track++) {




 ok = 1;
 for (net = 1; net <= channelNets; net++) {
     if (netsAssign[net] == track) {



  for (which = 0; which < HCG[select].nets; which++) {
      if (HCG[select].netsHook[which] == net) {



   ok = 0;
   break;
      }
  }




  if (! ok) {
      break;
  }
     }
 }




 tracksNoHCV[track] = ok;
    }
}
