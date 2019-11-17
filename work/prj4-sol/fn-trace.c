
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
  FnInfo info[16]; //each FnInfo is 24-bytes
} FnsData;

typedef unsigned char Byte;

  /*  Class notes
      - declare pointer as char* and keep adding length to it
      - byte pointed to by char* is opcode
      - every 4bytes after call are treated as an integer and
  */
  /*  Hints
  //returns address of function being called
    Using the x86-64_lde module, have the new_fns_data() function
    print out the length of each instruction in the root function being traced.
    Your code should be setup to terminate when any RET opcode is seen.
  */


  Byte *
  get_callee_address(Byte * p)
  {
    Byte* next_byte_p = p + 1; //get opcode without E8(call)
    int offset = *(int *)next_byte_p; //offset to calculate next address
    Byte *next_op_p = p + get_op_length(p);
    return next_op_p + offset;
  }


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
    Byte op = *(Byte *)rootFn;
    int op_length = get_op_length(rootFn);

    printf("%x\n", op);
	  printf("op l %x\n",op_length);


    Byte *p = rootFn; //op_code_byte

    //int i = 0;
    for(int i = 0; i < 15; i++){
      //will use temp_op when function returns to get instruction after call
      Byte *temp_op = p;
      while(!(is_ret(op))){
          op_length = get_op_length(p); //get op_length
          p = p + op_length; //get next instructions address

          //check if address is 0
          if(is_call(*p)){
            if(fns_data->info[i].address == 0){
              fns_data->info[i].address = get_callee_address(p);
              fns_data->info[i].length = get_op_length((Byte *)p);
              fns_data->info[i].nInCalls++;
              printf("fns test: %x, %d, %d, %d\n",
                fns_data->info[i].address,
                fns_data->info[i].length,
                fns_data->info[i].nInCalls,
                fns_data->info[i].nOutCalls
              );
            } else {
              p = get_callee_address(p);
            }
          }

        op = *p + 1;
        printf("temp op: %x \n", temp_op);
      }

      op = temp_op + 1;
      fns_data->info[i].nOutCalls++;
    }

    for(int i = 0; i < 15; i++){
      printf("fns test: %x, %d, %d, %d\n",
      fns_data->info[i].address,
      fns_data->info[i].length,
      fns_data->info[i].nInCalls,
      fns_data->info[i].nOutCalls
      );
    }

    return fns_data;
  }

  /*
  for(int i = 0; i < 15; i++){
    printf("fns test: %d, %d, %d, %d\n",
    *(Byte *)fns_data->info[i].address,
    fns_data->info[i].length, fns_data->info[i].nInCalls,
    fns_data->info[i].nOutCalls
    );
  }
  */

    /*
    for(int i = 0; i < ; i++){
	     fns_data->info[i].address = op;
	      printf("fns test %d\n", fns_data->info[i].address);
    }



    for(int i = 0; i < 1; i++){
	      fns_data->info[i].address = &rootFn;
        fns_data-xx>info[i].length = get_op_length(fns_data->info[i].address);
	      if(is_call(CALL_OP)){
		        fns_data->info[i].nInCalls += fns_data->info[i].nInCalls;
	      }
	      if(is_ret(RET_NEAR_OP || RET_NEAR_WITH_POP_OP || RET_FAR_OP || RET_FAR_WITH_POP_OP)){
		        break;
	      }
   }
   */


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
