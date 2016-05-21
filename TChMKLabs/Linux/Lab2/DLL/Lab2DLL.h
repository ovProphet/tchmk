// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LAB2DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LAB2DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include <stdlib.h>
#include <stdio.h>

class  BigInt
{
public:
	int amount;
	int* digits;
	bool negative;

	BigInt(void);
	void output(FILE* f, bool bin);
	BigInt input(FILE *f, bool bin);
	BigInt operator+(BigInt const & b);
	BigInt operator-(BigInt const & b);
	BigInt operator*(BigInt const & b);
	BigInt operator/(BigInt const & b);
	BigInt operator%(BigInt const & b);
	BigInt& operator=( BigInt const &a );
};

 class BigInt;
extern int baseIndex;
extern int powOfTen[];
extern long long count;
extern long long scount;
 BigInt shorten(BigInt a);
 void outputOnScreen(BigInt res);
 void reverse_num(BigInt a);
 BigInt inputBin(FILE* f, bool& b);
 BigInt input1(FILE* f1, bool& b);
 void output1(BigInt res, FILE* f);
 void outputBin(BigInt res, FILE* f);
 bool equals(BigInt a, BigInt b);
 bool greater(BigInt b, BigInt a);
 bool less(BigInt b, BigInt a);
 BigInt sub(BigInt a, BigInt b);
 BigInt sum(BigInt a, BigInt b);
 BigInt mul_small(BigInt a,int b);
 BigInt mul_big(BigInt a, BigInt b);
 void div_small(BigInt a);
 BigInt div_big(BigInt a, BigInt b);
 BigInt mod_big(BigInt a, BigInt b);
 bool isNull(BigInt a);
 BigInt pow_mod(BigInt a, BigInt b, BigInt c);
