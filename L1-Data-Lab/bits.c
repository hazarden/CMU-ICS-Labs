/*
 * CS:APP Data Lab
 * <Please put your name and userid here>
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

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
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
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    
    return ~(~x|~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    /**
     * 1. n << 3 shift by byte
     * 2. x >> remove the right part
     * 3. & 0xFF get the requested byte
     */
    return (x >> (n << 3)) & 0xFF;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
    /**
     * 1. Shift right for 1 if n!=0
     * 2. Mask the left part if n!=0
     * 3. Shift right for n-1 if n!=0
     */
    int a = x >> n;
    int b = ~(0x1<<31>>n<<1);
    int c = b & a;
    return c;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    /**
     * Refer to http://stackoverflow.com/questions/3815165/how-to-implement-bitcount-using-only-bitwise-operators
     */
    int a = 0x55+(0x55<<8)+(0x55<<16)+(0x55<<24);
    int b = 0x33+(0x33<<8)+(0x33<<16)+(0x33<<24);   
    int c = 0x0F+(0x0F<<8)+(0x0F<<16)+(0x0F<<24);
    x = (x&a)+((x>>1)&a);
    x = (x&b)+((x>>2)&b);
    x = (x&c)+((x>>4)&c);
    x = (x+(x>>8)+(x>>16)+(x>>24))&0xFF;
    return x;
}
    
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
   int a = 0;
   a = x | (x >> 16);
   a = a | (a >> 8);
    a = a | (a >> 4);
    a = a | (a >> 2);
    a = a | (a >> 1);
    return (~a)&0x1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    // just 0x80000000
    return 1 << 31;
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
    // x >> 31 == 1 if x is positive, just a mask
    //return !((~x & ((x >> 31) >> 31)  + ((x & ~(x >> 31) >> 31))) >> (n + (-1)));
    return !(x ^ ((x << (32 + ~n + 1)) >> (32 + ~n + 1)));
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    // if x is negative, make x exceed the perfect 2-power.
    return (x + (((x>>31)&1)<<n)+(x>>31)) >> n;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return (~x) + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    // &(!!x) let isPositive(0) = 0
    //return !(x >> 31) & (!!x);
    return !!(x & ~(x>>31));
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // if x = 0x80000000, ~x+1 becomes itself. => if x = 0x80000000, return 1
    // if y = 0x80000000, ~y+1 becomes itself. simple_check = 1, ok actually

    //int simple_check = (((~x + 1) + y) >> 31 & 0x1); // = 1 if x > y
    //int is_bound = (( (x & (1 << 31)) ^ (y & (1 << 31)) ) >> 31) & 1;
    //return (!is_bound & !simple_check) | (is_bound & ( (x & (1 << 31)) >> 31 ) );
    int c=y+~x+1;
    int d=x>>31&0x1;
    int e=y>>31&0x1;
    return ((d^e)&d )| ((!(d^e))&(!(c>>31&0x1)));
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int a16, a8, a4, a2, a1, b16, b8, b4, b2;
	a16 = !(!(x >> 16));
	b16 = a16 << 4;
	a8 = !(!(x >> (8 + b16)));
	b8 = (a8 << 3) + b16;
	a4 = !(!(x >> (4 + b8)));
	b4 = (a4 << 2) + b8;
	a2 = !(!(x >> (2 + b4)));
	b2 = (a2 << 1) + b4;
	a1 = (x >> (1 + b2));
	return a1 + b2;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    // deal with NaN
    if ((uf & 0x7FFFFFFF) > 0x7F800000) {
        return uf;
    }
    /*if (uf != 0x7F800000 && uf != 0xFF800000 && (uf & 0x7F800000) == 0x7F800000) {
        return uf;
    }*/

    return uf ^ 0x80000000;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    int exp = 0;
    int flo = x;
    int s = 0;
    int tmp = 0;
    int m = 0;
    int m1 = 0;
    int n = 0;
    int n1 = 0;
    if (x == 0) {
        return 0;
    }
    if (x == 0x80000000) {
        return 0xCF000000;
    }
    if (x < 0) {
        s = 0x80000000;
        x = -x;
    }
    tmp = x;
    while(tmp>>1) {
        exp++;
        tmp = tmp >> 1;
    }
    if (exp > 23) {
        m = 1 << (exp-23);
        m1 = m >> 1;
        n=x & (m1 - 1);
        n1=x&m1;
        flo = x >> (exp - 23);
        if (n1){
            if (n ||(flo & 1)) {
                flo++;
                if (flo == 0x1000000) {
                    flo = 0;
                    exp++;
                }
            }
        }
    }
    else {
        flo = x << (23 - exp);
    }
    return s + ((exp + 127) << 23) + (flo & 0x7FFFFF);
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    /*if ((uf & 0x7FFFFFFF) > 0x7F800000) {
        return uf;
    }
    return(uf + 0x800000);*/
    unsigned sign = (uf >> 31) & 0x1;
    unsigned e = (uf >> 23) & 0xFF;
    unsigned f = uf & 0x7FFFFF;

    if (e == 0xFF) { // inf
        return uf;
    } else if (e > 0) { // normal
        e = e + 1;
        return (sign << 31) + (e << 23) + f;
    } else { // denormal;
        return (uf << 1) | (sign << 31);
    }
}
