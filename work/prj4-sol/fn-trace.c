#include "fn-trace.h"
#include "x86-64_lde.h"

#include "memalloc.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  CALL_OP = 0xE8,
  RET_FAR_OP = 0xCB,
  RET_FAR_WITH_POP_OP = 0xCA,
  RET_NEAR_OP = 0xC3,
  RET_NEAR_WITH_POP_OP = 0xC2
};

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}

typedef struct FnsData{
  FnInfo *info[128]; //each FnInfo is 24-bytes
} FnsData;

/** Return pointer to opaque data structure containing collection of
 *  FnInfo's for functions which are callable directly or indirectly
 *  from the function whose address is rootFn.
 */
const FnsData *
new_fns_data(void *rootFn)
{
  //verify assumption used when decoding call address
  assert(sizeof(int) == 4);
  //@TODO
  FnsData *fns_data = (FnsData *)calloc(1, sizeof(FnsData));  
  //declar pointer as char* and keep adding length to it
  // byte pointed to by char* is opcode
  //every 4bytes after call are treated as an integer and
for(int i = 0; i < 128; i++){
	fns_data->info[i].address = &rootFn;
	fns_data->info[i].length = fns_data->info[i].get_op_length(fns_data->info[i].address);
	if(is_call(CALL_OP)){
		fns_data->info[i].nInCalls += fns_data->info[i].nInCalls;
	}
	if(is_ret(RET_NEAR_OP || RET_NEAR_WITH_POP_OP || RET_FAR_OP || RET_FAR_WITH_POP_OP)){
		break;		
	}
  }  


  return fns_data;
}

/** Free all resources occupied by fnsData. fnsData must have been
 *  returned by new_fns_data().  It is not ok to use to fnsData after
 *  this call.
 */
void
free_fns_data(FnsData *fnsData)
{
  //@TODO
}

/** Iterate over all FnInfo's in fnsData.  Make initial call with NULL
 *  lastFnInfo.  Keep calling with return value as lastFnInfo, until
 *  next_fn_info() returns NULL.  Values must be returned sorted in
 *  increasing order by fnInfoP->address.
 *
 *  Sample iteration:
 *
 *  for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;
 *       fnInfoP = next_fn_info(fnsData, fnInfoP)) {
 *    //body of iteration
 *  }
 *
 */
const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
  //@TODO
  return NULL;
}
