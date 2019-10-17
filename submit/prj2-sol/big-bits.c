#include "big-bits.h"
#include "hex-util.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/** Provide concrete definition for struct BigBits to flesh out
 *  abstract BigBits data type.
 */
struct BigBits {
  //@TODO
  char *hexString;
  unsigned long long size_hex_str;
};
/*
size_t size;
size_t index;
char hexChar;
int hexet;
*////////////////////////////////////////////////////////////


/** Return a pointer to a representation of a big integer with value
 *  corresponding to the non-empty hexadecimal string hex.  Note that
 *  hex will only contain hexadecimal characters '0' - '9', 'a' - 'f'
 *  and 'A' - 'F' terminated by a NUL '\0' char.
 *
 *  The string hex may not remain valid after this function returns.
 *
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
newBigBits(const char *hex)
{
  assert(CHAR_BIT == 8);
  //@TODO
  /*
    - create a bigBits that is the size of the structure
    - initialize pointer within bigBits using string.h
  */
  BigBits *bigBits = (BigBits *)calloc(1, sizeof(BigBits));
  bigBits->hexString = (char *)malloc(strlen(hex) + 1); //use + 1 for terminating null char
  strcpy(bigBits->hexString, hex);
  bigBits->size_hex_str = (unsigned long long)strlen(bigBits->hexString);
  //free(hex);
  //int x = atoi(bigBits->hexString);
  //printf("test x %d\n", x );
  /*
  for(size_t i = 0; i < strlen(hex) + 1; i++){
    printf("%d \n", hex[i]);
  }
  */
  return bigBits;
}

/*
set the *hex parameter to the bigBits *hexString
for(size_t i = 0; i < sizeof(hex); i++){
  bigBits->hexString[i] = hex[i];
}
*/
//free(hex);
/*
if(bigBits != NULL){
  bigBits->hexString = NULL;
}
*///////////////////////////////////////////////////////////////////


/** Frees all resources used by currently valid bigBits.  bigBits
 *  is not valid after this function returns.
 */
void
freeBigBits(BigBits *bigBits)
{
  //@TODO
  /*
    free pointer, free struct itself
  */
  free(bigBits->hexString);
  free(bigBits);
}


/** Return a lower-case hex string representing bigBits. Returned
 *  string should not contain any non-significant leading zeros.
 *  Returns NULL on error with errno set "appropriately".  (Note that
 *  there is no call to free the corresponding string).
 */
const char *
stringBigBits(const BigBits *bigBits)
{
  //@TODO
  char *c = (char *)malloc(strlen(bigBits->hexString) + 1);
  strcpy(c, bigBits->hexString);
  return c;
}
/*
want to create dynamically allocated array (char *)
*******FIGURE OUT SIZE**********
size = (NUMBER_OF_ELEMENTS * size()
char *c = malloc(sizeof(char) * sizeof(bigBits));
int size_c = sizeof(char) * sizeof(bigBits);

if the size of *c > bigBits->size (hexString size) then we allocate more
memory to big bits
if(size_c > bigBits->size){
  bigBits = realloc(bigBits, sizeof(c) * sizeof(bigBits));
}

loop through and set our bigBits string equal to the returned string
for(size_t i = 0; i < size_c; i++){
  c[i] = bigBits->hexString[i];
}
*/
//freeBigBits(bigBits);
///////////////////////////////////////////////////////////////////////
/*
            stringBigBits compared to stack adt attempt
if(bigBits->index >= bigBits->size){
  bigBits->size = bigBits->size + 1;
  bigBits->unit = realloc(bigBits->unit, bigBits->size*sizeof(void *));
  if(!bigBits->unit) return NULL;
}
assert(bigBits->index < bigBits->size);
bigBits->unit[bigBits->index++] = hexChar;

for(int i = 0; i < bigBits->size - 1; i++){
  bigBits->
}
*/


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  BigBits *tempBigBits = (BigBits *)malloc(sizeof(BigBits));
  unsigned int temp = 0;
  size_t offset = 0;

  if(bigBits1->size_hex_str >= bigBits2->size_hex_str){
    tempBigBits->hexString = (char*)calloc(bigBits1->size_hex_str, sizeof(char));
    offset = bigBits1->size_hex_str - bigBits2->size_hex_str;
    for(size_t i = 0; i < bigBits1->size_hex_str; i++){
      unsigned int val1 = charToHexet(bigBits1->hexString[i]);
      unsigned int val2 = charToHexet(bigBits2->hexString[i-offset]);
      val2 = (i < offset) ? 0 : val2;
      temp = (val1 & val2);
      tempBigBits->hexString[i] = hexetToChar(temp);
    }
  } else{
    tempBigBits->hexString = (char*)calloc(bigBits2->size_hex_str, sizeof(char));
    offset = bigBits2->size_hex_str - bigBits1->size_hex_str;
    for(size_t i = 0; i < bigBits2->size_hex_str; i++){
      unsigned int val1 = charToHexet(bigBits2->hexString[i]);
      unsigned int val2 = charToHexet(bigBits1->hexString[i-offset]);
      val2 = (i < offset) ? 0 : val2;
      temp = (val1 & val2);
      tempBigBits->hexString[i] = hexetToChar(temp);
    }
  }
  return tempBigBits;
}

/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  BigBits *tempBigBits = (BigBits *)malloc(sizeof(BigBits));
  unsigned int temp = 0;
  size_t offset = 0;

  if(bigBits1->size_hex_str >= bigBits2->size_hex_str){
    tempBigBits->hexString = (char*)calloc(bigBits1->size_hex_str, sizeof(char));
    offset = bigBits1->size_hex_str - bigBits2->size_hex_str;
    for(size_t i = 0; i < bigBits1->size_hex_str; i++){
      unsigned int val1 = charToHexet(bigBits1->hexString[i]);
      unsigned int val2 = charToHexet(bigBits2->hexString[i-offset]);
      val2 = (i < offset) ? 0 : val2;
      temp = (val1 | val2);
      tempBigBits->hexString[i] = hexetToChar(temp);
    }
  } else{
    tempBigBits->hexString = (char*)calloc(bigBits2->size_hex_str, sizeof(char));
    offset = bigBits2->size_hex_str - bigBits1->size_hex_str;
    for(size_t i = 0; i < bigBits2->size_hex_str; i++){
      unsigned int val1 = charToHexet(bigBits2->hexString[i]);
      unsigned int val2 = charToHexet(bigBits1->hexString[i-offset]);
      val2 = (i < offset) ? 0 : val2;
      temp = (val1 | val2);
      tempBigBits->hexString[i] = hexetToChar(temp);
    }
  }
  return tempBigBits;
}
/*
BigBits *bigBits3 = (BigBits*)malloc(sizeof(bigBits3));
for(size_t i = 0; i < sizeof(bigBits1); i++){
  bigBits3->hexString[i] = (bigBits1->hexString[i] & bigBits2->hexString[i]);
}
return bigBits3;
*/

/** Return a new BigBits which is the bitwise-^ of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
xorBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  BigBits *tempBigBits = (BigBits *)malloc(sizeof(BigBits));
  unsigned int temp = 0;
  size_t offset = 0;

  if(bigBits1->size_hex_str >= bigBits2->size_hex_str){
    tempBigBits->hexString = (char*)calloc(bigBits1->size_hex_str, sizeof(char));
    offset = bigBits1->size_hex_str - bigBits2->size_hex_str;
    for(size_t i = 0; i < bigBits1->size_hex_str; i++){
      unsigned int val1 = charToHexet(bigBits1->hexString[i]);
      unsigned int val2 = charToHexet(bigBits2->hexString[i-offset]);
      val2 = (i < offset) ? 0 : val2;
      temp = (val1 ^ val2);
      tempBigBits->hexString[i] = hexetToChar(temp);
    }
  } else{
    tempBigBits->hexString = (char*)calloc(bigBits2->size_hex_str, sizeof(char));
    offset = bigBits2->size_hex_str - bigBits1->size_hex_str;
    for(size_t i = 0; i < bigBits2->size_hex_str; i++){
      unsigned int val1 = charToHexet(bigBits2->hexString[i]);
      unsigned int val2 = charToHexet(bigBits1->hexString[i-offset]);
      val2 = (i < offset) ? 0 : val2;
      temp = (val1 ^ val2);
      tempBigBits->hexString[i] = hexetToChar(temp);
    }
  }
  return tempBigBits;
}
