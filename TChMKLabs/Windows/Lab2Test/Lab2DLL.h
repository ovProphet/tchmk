// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LAB2DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LAB2DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include <stdlib.h>
#include <stdio.h>
#ifdef LAB2DLL_EXPORTS
#define LAB2DLL_API __declspec(dllexport)
#else
#define LAB2DLL_API __declspec(dllimport)
#endif

class LAB2DLL_API BigInt
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

LAB2DLL_API class BigInt;
extern LAB2DLL_API int baseIndex;
extern LAB2DLL_API int powOfTen[];
extern LAB2DLL_API long long count;
extern LAB2DLL_API long long scount;
LAB2DLL_API BigInt shorten(BigInt a);
LAB2DLL_API void outputOnScreen(BigInt res);
LAB2DLL_API void reverse_num(BigInt a);
LAB2DLL_API BigInt inputBin(FILE* f, bool& b);
LAB2DLL_API BigInt input1(FILE* f1, bool& b);
LAB2DLL_API void output1(BigInt res, FILE* f);
LAB2DLL_API void outputBin(BigInt res, FILE* f);
LAB2DLL_API bool equals(BigInt a, BigInt b);
LAB2DLL_API bool greater(BigInt b, BigInt a);
LAB2DLL_API bool less(BigInt b, BigInt a);
LAB2DLL_API BigInt sub(BigInt a, BigInt b);
LAB2DLL_API BigInt sum(BigInt a, BigInt b);
LAB2DLL_API BigInt mul_small(BigInt a,int b);
LAB2DLL_API BigInt mul_big(BigInt a, BigInt b);
LAB2DLL_API void div_small(BigInt a);
LAB2DLL_API BigInt div_big(BigInt a, BigInt b);
LAB2DLL_API BigInt mod_big(BigInt a, BigInt b);
LAB2DLL_API bool isNull(BigInt a);
LAB2DLL_API BigInt pow_mod(BigInt a, BigInt b, BigInt c);
