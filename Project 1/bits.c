/* 
 * CS:APP Data Lab 
 * 
 *
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#include "btest.h"

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
id_struct studentID =
{
  /* UID number: */
  ,
  /* Last Name: */
  ,
  /* First Name: */
  ,
};

#if 0
/*
 * Instructions to Students:
 *
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest harness to check your solutions for correctness.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
	//Notice that odd numbers have a 1 as its last bit (i.e. 1 = 0001, 5 = 0101, 9 = 1001, etc.).
	//When we XOR (^) two numbers, we end up getting a number with the same bit parity.
	//So, in order to get the correct bit parity, we need to keep right-shifting
	//by half of the bit-width until we are down to the 1 bit case.  We then AND (&)
	//it to 1 (0001) in order to compare the last bit, which tells us whether it is
	//true or false.

	x = (x >> 16) ^ x;
	x = (x >> 8) ^ x;
	x = (x >> 4) ^ x;
	x = (x >> 2) ^ x;
	x = (x >> 1) ^ x;
	return (x & 1);
}

/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
	//One of our first concerns is we need to find a way in order to save certain bits
	//before we perform the rotation.  To do so, we save it into a local variable.
	//We left shift the bits since we are shifting by 32 - n bits.
	int savedBits = (x << (32 + (1 + ~n)));
	
	//We now create a mask of Tmax that will remove the bits where the new bits will be.
	int mask = (~(1 << 31) >> (n + ~0));
	
	//Next, we shift x by n to move the number over.  We AND (&) it in order to create space for the rotating bits.
	//Lastly, we OR (|) the results and we get the solution.
	return (savedBits | ((x >> n) & mask));
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
	//We first save the number of bits we need to shift by for each variable.
	int nShift = n << 3;
	int mShift = m << 3;

	//We now set a new variable to a constant of all 1's in order to mask.
	int t = 0xff;

	//We then AND (&) the constant with the shift in order to get the portion we want.
	int savedBits = t & ((x >> nShift) ^ (x >> mShift));

	//We then shift back the bits into the number to obtain the result.
	x = (x ^ (savedBits << nShift));
	x = (x ^ (savedBits << mShift));
	return x;
}

/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
	//The short data type ranges from -32,768 to 32,767.
	//The binary code has 16 significant bits. So, we only care about
	//the top 16 bits.  If we shift it and the top number is 0, then it
	//should be true (1), otherwise it should return false (0). 
	return !( x >> 15 ) | !((~x >> 15));
}

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	//Based on DeMorgan's Law, we can relate the logical operators & and |.
	//The law states that the ~(x & y) is equivalent to ~x | ~y.
	//Thus, in order to get x and y, we need to ~ the whole expression to work.
	return ~(~x | ~y);
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
	//Overflow is defined is the operation performed creates a result that is greater than
	//the max value or less than the min value.  The definition gives me the idea that the first bit
	//is probably important.  So I will grab the first bit of each variable.
	int firstBit_x = (x >> 31);
	int firstBit_y = (y >> 31);

	//In this scenario, overflow will occur in two cases:
	//	If x is negative and y is positive, the sum of the sign bit will be 0.
	//	If x is postive and y is negative, the sum of the sign bit will be 1.
	int sub_firstBit = ((x + (~y + 1)) >> 31);

	return (!((firstBit_x ^ firstBit_y) & (firstBit_x ^ sub_firstBit)));
}

/*
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
	//First, we need to get the bit that indicates whether or not the
	//integer is positive or negative.  To do so, we right shift both varialbes
	//by 31 positions to create a mask.  The book tells us that 1 is negative and 0 is positive.
	int mask_x = (x >> 31);
	int mask_y = (y >> 31);

	//If the signs are the same, then we get two cases:
	//	If mask_x is larger, the sign bit of (~y + x) is 0.
	//	If mask_y is larger, the sign bit of (~y + x) is 1.
	int sameSign = ((!(mask_x ^ mask_y)) & ((~y + x) >> 31));

	//If the signs are not equal, then we get the reverse.
	int differentSign = (mask_x & (!mask_y));

	//This | will return 0 when firstBit_x is greater, so we need to negate it.
	return (!(differentSign | sameSign));
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	//Our first concern in this puzzle is to figure out how to consider the sign.
	//First, we need to make a mask in order to get the highest bit.  We then use AND (&) in order
	//to extract the highest bit.
	int mask = (x >> 31);

	//Once we do so, we right-shift by n - 1, in order to see if it will fit between 1 - 32.
	//We then NOT (!) the whole expression because if it fits, the bit should be 0, so the !
	//would make it 1 and vice versa.
	return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	//A negative integer begins with a 1 in the left-most bit position.
	//So, to negate a number, we take the bit NOT (~), which gives us the one's complement.
	//Then, we add 1 in order to get the two's complement.
	return ~x + 1;
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	//From the book, we know that Tmax + 1 = Tmin and that
	//2Tmax + 1 = Tmax + Tmax + 1 = Umax, which has the same bit pattern as -1 (page 62).
	//When we create Umax, we need to NOT (~) it in order to get 0.  On the other side, we use 
	//the logical NOT (!) since that creates Tmin, which gives us 0.
	//When we ! the whole expression, we get our check to see if x = Tmax..
	return !(~(x + x + 1) | !(x + 1));
}
