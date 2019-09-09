#include "bits-to-ints.h"
#include "errors.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

//@TODO: auxiliary definitions

/** This function should be called with inFile set to an input FILE
 *  stream corresponding to a file named inName.  This FILE should
 *  contain a stream of '0' or '1' bit-value characters optionally
 *  separated by whitespace (as determined by isspace()) characters.
 *  The function should return the next unsigned integer value given
 *  by the next next nBits bit characters read from in.
 *
 *  The nBits argument (which should be > 0) will specify the number
 *  of bits from FILE stream inFile which are to be grouped to form an
 *  unsigned integer value.
 *
 *  The bytes within the bit-stream are assumed to be in big-endian
 *  order (with the most significant byte first), and the bits within
 *  each byte are ordered little-endian with the least-significant bit
 *  first.
 *
 *  For example, assume that nBits is 16 and the least significant bit
 *  in the result is at index 0, and most significant bit in the
 *  result at index 15; i.e., the bits in the BitsValue result are
 *  indexed 15-14-...-1-0.  The order of the corresponding bits in the
 *  input stream will be 8-9-10-11-12-13-14-15 - 0-1-2-3-4-5-6-7.  So
 *  the bit-stream "1101 0101 1011 0011" will result in the BitsValue
 *  0xabcd (which has binary representation 1010_1011_1100_1101).
 *
 *  When the function returns, *isEof should be set to true if
 *  end-of-file is encountered on inFile.  If EOF is encountered
 *  within a partial value, then a suitable error message should be
 *  printed before returning with *isEof true.
 *
 *  If any character other than '0', '1' or whitespace is encountered
 *  in inFile, then a suitable error message should be printed and the
 *  function should return with *isEof set to true.
 */

 int getBit(FILE *inFile, const char *inName){
   char c = ' ';
   while(isspace(c)){
     c = fgetc(inFile);
     if(c == '1'){
       return 1;
     } else if(c == '0'){
       return 0;
     }
     // if(!isspace(c) && c != '0' && c != '1'){
     //   error("unexpected character %c in file %s", c, inName);
     //   return 0;
     // }
   }
   return 0;
 }

 int getByte(FILE *inFile, const char *inName){
   unsigned char byte = 0;
   char c[CHAR_BIT];

   for(int i = 0; i < CHAR_BIT; i++){
     c[i] = getBit(inFile, inName);
     byte = byte | c[i] << i;
   }
   return byte;
 }



BitsValue
bits_to_ints(FILE *inFile, const char *inName, int nBits, bool *isEof)
{
  //nBits value should make sense
  assert(0 < nBits && nBits <= CHAR_BIT*sizeof(BitsValue));
  BitsValue value = 0;
  //@TODO

  for(int i = 0; i < nBits; i++){
    value = getByte(inFile, inName);
    value = value << CHAR_BIT | getByte(inFile, inName);
    printf("%llx\n", value);
  }

  *isEof = true;
  return value;
}
/*
while(1){
  char c;
  c = fgetc(inFile);
  unsigned mask = 0x1; //1000
  c = (mask & value) ? '1' : '0';
  mask >>= 1;
  printf("test value: %c\n", c);
  if(feof(inFile)){
    *isEof = true;
    break;
  }
}
*/
/*if(!isspace(c) && c != '0' && c != '1'){
  *isEof = true;
  error("unexpected character %c in file", c);
  return value;
} else*/
/*if(!isspace(c) && c != '0' && c != '1'){
  *isEof = true;
  error("unexpected character %c in file", c);
  return value;
} else*/
////////////////////////////////////////////////////
// unsigned char val;
// val = fgetc(inFile);
// nBits = CHAR_BIT * sizeof(val);
// if(!isspace(val)){
  //   unsigned mask = 0x1 << (nBits - 1); //gets set to int
  //   for(int i = 0; i < nBits; i++){
    //     char c = (mask & val) ? '1' : '0';
    //     mask >>= 1;
    //     printf("test %c ", c);
    //   }
    // } else{
      //   //
      // }
      ////////////////////////////////////////////////////////////
//unsigned int printVal = 0;

// unsigned char c = fgetc(inFile);
// unsigned char c1 = fgetc(inFile);
// unsigned char c2 = fgetc(inFile);
// printf("%c", c);
// printf("%c", c1);
// printf("%c", c2);
// printf("///////////////////");
//for(unsigned int i = nBits; i > 0; i--){
  //printf(fgetc(inFile));
  // char digit = (char)fgetc(inFile);
  // if(digit == '0'){
  //   printVal >>
  //
  // } else if (digit == '1'){
  //
  // }
////////////////////////////////////////
  //for(unsigned int i = 0; i <= nBits * 2 - 1; i++){
////////////////////////////////////////
/*      if(c == '1'){
            int one = 1;


            printf("test successful for %c\n", c);
            printf("counter%ld ", counter);
          }
          if(c == (char)'0'){
            printf("test successful for 0 \n");
          }
          printf("current c: %c ", c);
          printf("\n");
          counter = counter + 1;
*/
