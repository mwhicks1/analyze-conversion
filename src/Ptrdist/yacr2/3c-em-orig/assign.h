












#include "types.h"
#include "vcg.h"
#include "hcg.h"

#ifndef ASSIGN_H
#define ASSIGN_H








#define	LOW		1
#define	MEDIUM		100
#define	HIGH		10000
#define	INFINITY	1000000















extern unsigned long * * costMatrix;
extern _Array_ptr<unsigned long> tracksNoHCV;
extern _Array_ptr<unsigned long> tracksNotPref;
extern _Array_ptr<unsigned long> tracksTopNotPref;
extern _Array_ptr<unsigned long> tracksBotNotPref;
extern unsigned long cardNotPref;
extern unsigned long cardTopNotPref;
extern unsigned long cardBotNotPref;
extern _Array_ptr<unsigned long> tracksAssign;
extern _Array_ptr<unsigned long> netsAssign;
extern _Array_ptr<unsigned long> netsAssignCopy;








void
AllocAssign(void);

void
FreeAssign(void);

void
NetsAssign(void);

void
MaxNetsAssign(void);

void
RightNetsAssign(void);

void
LeftNetsAssign(void);

void
Assign(_Array_ptr<nodeVCGType> VCG : count(select + 1), _Array_ptr<unsigned long> assign, unsigned long select);

void
Select(_Array_ptr<nodeVCGType> VCG, _Array_ptr<nodeHCGType> HCG, _Array_ptr<unsigned long> netsAssign, _Ptr<unsigned long> netSelect, _Array_ptr<unsigned long> CROSSING);

void
BuildCostMatrix(_Array_ptr<nodeVCGType> VCG, _Array_ptr<nodeHCGType> HCG, _Array_ptr<unsigned long> netsAssign, _Array_ptr<unsigned long> CROSSING);

void
IdealTrack(unsigned long tracks, unsigned long top, unsigned long bot, _Ptr<unsigned long> ideal);


#endif	
