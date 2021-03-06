/*
 *
 * assign.h
 *
 */


/*
 *
 * Includes.
 *
 */

#include "types.h"
#include "vcg.h"
#include "hcg.h"

#ifndef ASSIGN_H
#define ASSIGN_H

#pragma CHECKED_SCOPE ON
/*
 *
 * Defines.
 *
 */

#define	LOW		1
#define	MEDIUM		100
#define	HIGH		10000
#define	INFINITY	1000000


/*
 *
 * Types.
 *
 */

struct costMatrixRow {
    _Array_ptr<long> row : count(len);
    ulong len;
};


/*
 *
 * Globals.
 *
 */

extern ulong channelNets;
extern ulong channelTracks;

extern _Array_ptr<struct costMatrixRow>			costMatrix : count(channelNets + 1); // 2dim, second dim is (channelTracks + 2)
extern _Array_ptr<ulong>			tracksNoHCV : count(channelTracks+2);
extern _Array_ptr<ulong>			tracksNotPref : count(channelTracks+2);
extern _Array_ptr<ulong>			tracksTopNotPref : count(channelTracks+2);
extern _Array_ptr<ulong>			tracksBotNotPref : count(channelTracks+2);
extern ulong				cardNotPref;
extern ulong				cardTopNotPref;
extern ulong				cardBotNotPref;
extern _Array_ptr<ulong>			tracksAssign : count(channelTracks+2);
extern _Array_ptr<ulong>			netsAssign : count(channelNets + 1);
extern _Array_ptr<ulong>			netsAssignCopy : count(channelNets + 1);


/*
 *
 * Prototypes.
 *
 */

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
Assign(_Array_ptr<nodeVCGType> : count(channelNets + 1),       _Array_ptr<ulong> : count(channelNets + 1),       ulong);

void
Select(_Array_ptr<nodeVCGType> : count(channelNets + 1),       _Array_ptr<nodeHCGType> : count(channelNets + 1),       _Array_ptr<ulong> : count(channelNets + 1),       _Ptr<ulong>,       _Array_ptr<ulong> : count(channelNets + 1));

void
BuildCostMatrix(_Array_ptr<nodeVCGType> : count(channelNets + 1),        _Array_ptr<nodeHCGType> : count(channelNets + 1),        _Array_ptr<ulong> : count(channelNets + 1),        _Array_ptr<ulong> : count(channelNets + 1));

void
IdealTrack(ulong,	   ulong,	   ulong,	   _Ptr<ulong>);

#pragma CHECKED_SCOPE OFF
#endif	/* ASSIGN_H */

