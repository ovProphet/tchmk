// Lab2DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Lab2DLL.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// This is the constructor of a class that has been exported.
// see Lab2DLL.h for the class definition

LAB2DLL_API int baseIndex = 1;
LAB2DLL_API int powOfTen[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
LAB2DLL_API long long count = 0;
LAB2DLL_API long long scount= 0;
BigInt::BigInt()
{
	digits = NULL;
	amount = 0;
	negative = false;
}
void BigInt::output(FILE* f, bool bin)
{
	if(bin)
		outputBin(*this,f);
	else
		output1(*this,f);
}
BigInt BigInt::input(FILE *f, bool bin)
{
	bool b = true;
	BigInt res;
	res.digits = NULL;
	if(bin)
		res = inputBin(f,b);
	else
		res = input1(f,b);
	if (!b)
	{
		printf("Incorrect data!\n");
		return res;
	}
	res = shorten(res);
	if (this->digits != NULL)
		free(this->digits);
	digits = res.digits;
	amount = res.amount;
	negative = res.negative;
	return res;
}
BigInt BigInt::operator+(BigInt const & b)
{
	BigInt res;
	res = sum(*this,b);
	return res;
}
BigInt BigInt::operator-(BigInt const & b)
{
	BigInt res;
	res = sub(*this,b);
	return res;
}
BigInt BigInt::operator*(BigInt const & b)
{
	BigInt res;
	res = mul_big(*this,b);
	return res;
}
BigInt BigInt::operator/(BigInt const & b)
{
	BigInt res;
	res = div_big(*this,b);
	return res;
}
BigInt BigInt::operator%(BigInt const & b)
{
	BigInt res;
	res = mod_big(*this,b);
	return res;
}
BigInt& BigInt::operator=(BigInt const &a)
{
	digits = a.digits;
	amount = a.amount;
	negative=a.negative;
	return *this;
}

LAB2DLL_API BigInt shorten(BigInt a)
{
	int pos = a.amount - 1;
	while (pos >= 0 && a.digits[pos] == 0)
		--pos;
	if (pos == -1)
		a.amount = 1;
	else
		a.amount = pos + 1;
	BigInt res1;
	res1.amount = a.amount;
	res1.digits = (int *)malloc((res1.amount)*sizeof(int));
	for (int i = 0; i < res1.amount; ++i)
		res1.digits[i] = a.digits[i];

	res1.negative = a.negative;
	if (res1.amount == 1 && res1.digits[0] == 0)
		res1.negative = false;
	return res1;
}
LAB2DLL_API void outputOnScreen(BigInt res)
{
	if (res.amount == 0)
	{
		printf("0");
		return;
	}
	if(res.negative)
		printf("-");
	for (int i = res.amount - 1; i >= 0; --i)
	{
		//fprintf(f,"%d", res.digits[i]);
		printf("%d", res.digits[i]);
	}
	//fprintf(f,"\n");
	printf("\n");
}
LAB2DLL_API void reverse_num(BigInt a)
{
	int buff;
	for(int i=0;i < a.amount / 2; ++i)
	{
		buff = a.digits[i];
		a.digits[i] = a.digits[a.amount-i-1];
		a.digits[a.amount-i-1] = buff;
	}
}
LAB2DLL_API BigInt inputBin(FILE* f, bool& b)
{
	BigInt a;
	bool sign = false;
	fseek(f , 0 , SEEK_END);
	long lSize = ftell(f);
	rewind(f);

	char c = 0;
	int i = 0;
	fread(&c, sizeof(char), 1, f);
	if(c=='-')
	{
		sign = true;
		--lSize;
		fread(&c, sizeof(char), 1, f);
	}
	else
	{
		if(!(c>=0 && c<=9))
		{
			b = false;
			return a;
		}
	}

	a.digits = (int *)malloc((lSize)*sizeof(int));
	a.negative = sign;
	a.amount = lSize;

	a.digits[0] = (int)c;
	for(int i = 1; i < lSize; ++i)
	{
		fread(&c, sizeof(char), 1, f);
		if(!(c>=0 && c<=9))
		{
			b = false;
			return a;
		}
		a.digits[i] = (int)c;
	}
	
	reverse_num(a);
	while (a.digits[a.amount-1] == 0)
		--a.amount;

	if(a.amount == 0)
	{
		a.amount = 1;
		a.digits[0] = 0;
	}
	return a;
}

LAB2DLL_API BigInt input1(FILE* f1, bool& b)
{
	BigInt a1;
	int maxim = 500, count = 0;

	char* s1 = (char *) malloc(maxim * sizeof(char));
	char* s1buf;
	char ch = fgetc(f1);
	if(ch == EOF)
	{
		b = false;
		return a1;
	}
	if(ch == '-')
	{
		a1.negative = true;
		ch = fgetc(f1);
	}
	else
		a1.negative = false;

	int length = 0;
	while ( (ch != '\n') && (ch != EOF) ) {
		if(!(ch <= '9' && ch >= '0'))
		{
			b = false;
			return a1;
		}
		if(count == maxim) {
			maxim *= 2;
			s1buf = (char *)malloc(maxim * sizeof(char));
			for (int i = 0; i < maxim/2; ++i)
				s1buf[i] = s1[i];
			//strcpy(s1buf,s1);
			free(s1);
			//s1 = new char[maxim];
			s1 = s1buf;
		}
		s1[length] = ch;
		length++;
		count++;
		ch = fgetc(f1);
	}
	a1.amount = length;
	a1.digits = (int *)malloc((a1.amount)*sizeof(int));
	for (int i = 0; i < length; ++i)
		a1.digits[a1.amount-1-i] = s1[i] - '0';
	
	free(s1);
	return a1;
}

LAB2DLL_API void output1(BigInt res, FILE* f)
{
	if (res.amount == 0)
	{
		fprintf(f,"0");
		return;
	}
	if(res.negative)
		fprintf(f,"-");
	for(int i=res.amount - 1;i >= 0;--i)
		fprintf(f,"%d",res.digits[i]);
}

LAB2DLL_API void outputBin(BigInt res, FILE* f)
{
	char c = '-';
	if(res.negative)
		fwrite(&c, sizeof(char), 1, f);
	for (int i = res.amount - 1; i >= 0; --i)
		fwrite(&res.digits[i], sizeof(char), 1, f);
}
LAB2DLL_API bool equals(BigInt a, BigInt b)
{
	while (a.digits[a.amount - 1] == 0)
		a.amount-- ;
	while (b.digits[b.amount - 1] == 0)
		b.amount-- ;

	if(a.amount != b.amount)
		return false;
		
	for(int i = a.amount - 1; i>-1; --i)
		if (b.digits[i] != a.digits[i])
			return false;
		
	return true;
}

LAB2DLL_API bool greater(BigInt b, BigInt a)
{
	while (a.digits[a.amount-1] == 0)
		a.amount-- ;
	while (b.digits[b.amount-1] == 0)
		b.amount-- ;

	if(a.amount < b.amount)
		return true;
	if(a.amount > b.amount)
		return false;
		
	for(int i = a.amount - 1; i>-1; --i)
		if(b.digits[i] > a.digits[i])
			return true;
		else if (b.digits[i] < a.digits[i])
			return false;
		
	return false;
}

LAB2DLL_API bool less(BigInt b, BigInt a)
{
	while (a.digits[a.amount-1] == 0)
		a.amount-- ;
	while (b.digits[b.amount-1] == 0)
		b.amount-- ;

	if(a.amount > b.amount)
		return true;
	if(a.amount < b.amount)
		return false;
		
	for(int i = a.amount - 1; i>-1; --i)
		if(b.digits[i] < a.digits[i])
			return true;
		else if (b.digits[i] > a.digits[i])
			return false;
		
	return false;
}

LAB2DLL_API BigInt sub(BigInt a, BigInt b);

LAB2DLL_API BigInt sum(BigInt a, BigInt b)
{
	BigInt res,a1,b1;
	if(a.negative == b.negative)
	{
		res.amount = a.amount + 2;
		if(a.amount < b.amount)
		{
			res.amount = b.amount + 2;
		}
		res.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		a1.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		b1.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		for(int i=0;i < res.amount;++i)
			res.digits[i]=0;
		for(int i=0;i<res.amount;++i)
			b1.digits[i]=0;
		for(int i=0;i<res.amount;++i)
			a1.digits[i]=0;
		for(int i=0;i<b.amount;++i)
			b1.digits[i]=b.digits[i];
		for(int i=0;i<a.amount;++i)
			a1.digits[i]=a.digits[i];

		a1.amount = a.amount;
		b1.amount = b.amount;
		res.negative = a.negative;
		for(int i=0;i < res.amount;++i)
		{
			res.digits[i]+=a1.digits[i]+b1.digits[i];
			if(res.digits[i]>9)
			{
				res.digits[i]%=10;
				res.digits[i+1]+=1;
			}
		}
		free(a1.digits);
		free(b1.digits);
	}
	else if(a.negative)
	{
		a.negative = false;
		res = sub(b,a);
	}
	else
	{
		b.negative = false;
		res = sub(a,b);
	}

	while (res.digits[res.amount-1] == 0)
		res.amount-- ;
	return res;
}

LAB2DLL_API BigInt sub(BigInt a,BigInt b)
{
	BigInt res,a1,b1;
	if(a.negative == b.negative)
	{
		res.amount = a.amount+ 1;
		if(a.amount < b.amount)
		{
			res.amount = b.amount + 1;
		}

		res.digits = (int*) malloc((res.amount + 2)*sizeof(int));
	
		a1.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		b1.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		for(int i=0;i<res.amount;++i)
			res.digits[i]=0;
		for(int i=0;i<res.amount;++i)
			b1.digits[i]=0;
		for(int i=0;i<res.amount;++i)
			a1.digits[i]=0;
		for(int i=0;i<b.amount;++i)
			b1.digits[i]=b.digits[i];
		for(int i=0;i<a.amount;++i)
			a1.digits[i]=a.digits[i];

		res.negative = a.negative;
		if(greater(b,a))
		{
			BigInt buff = b1;
			b1 = a1;
			a1 = buff;
			res.negative = !res.negative;
		}
		for(int i=0;i<res.amount;++i)
		{
			res.digits[i]+=a1.digits[i]-b1.digits[i];
			if(res.digits[i]<0 && i<res.amount-1)
			{
				res.digits[i]+=10;
				res.digits[i+1]-=1;
			}
		}
		free(a1.digits);
		free(b1.digits);
	}
	else if(a.negative)
	{
		b.negative = true;
		res = sum(a,b);
	}
	else
	{
		a.negative = false;
		res = sum(a,b);
	}
	while (res.digits[res.amount-1] == 0)
		res.amount-- ;

	return res;

}
LAB2DLL_API BigInt mul_small(BigInt a,int b)
{
	BigInt res;
	res.negative = a.negative ^ (b < 0);
	if(b < 0)
		b *= -1;
	res.amount = a.amount * 2;
	res.digits = (int *)malloc((res.amount)*sizeof(int));
	int r = 0;
	for (int i = 0; i < res.amount; ++i)
	{
		if (a.amount > i)
			res.digits[i] = a.digits[i] * b + r;
		else
			res.digits[i] = r;
		r = res.digits[i] / powOfTen[baseIndex];
		res.digits[i] %= powOfTen[baseIndex];
	}
	count += res.amount;
	BigInt res1 = shorten(res);
	free(res.digits);
	return res1;
}
LAB2DLL_API BigInt mul_big(BigInt a, BigInt b)
{
	BigInt res;
	res.amount = a.amount + b.amount + 1;
	res.digits = (int*) malloc((res.amount + 2)*sizeof(int));
	if(a.negative && b.negative)
		res.negative = false;
	else
		res.negative = a.negative || b.negative;

	for(int i=0;i < res.amount;++i)
		res.digits[i]=0;
	for (int ix = 0; ix < a.amount; ix++)
		for (int jx = 0; jx < b.amount; jx++)
			res.digits[ix + jx] += a.digits[ix] * b.digits[jx];
 
	for (int ix = 0; ix < res.amount; ix++)
	{
		res.digits[ix + 1] +=  res.digits[ix] / 10;
		res.digits[ix] %= 10;
	}
	 
	while (res.digits[res.amount-1] == 0)
		res.amount--;
	return res;
}
LAB2DLL_API void div_small(BigInt a)
{
	int remainder = 0;
	for (int i = a.amount - 1; i >= 0; i--)
	{
		int cur = remainder * powOfTen[baseIndex] + a.digits[i];
		a.digits[i] = cur / 2;
		remainder = cur % 2;
	}
	while (a.digits[a.amount-1] == 0)
		--a.amount;
}
/*
int mod_small(BigInt a, int b)
{
	BigInt res;
	res.amount = a.amount;
	res.digits = (int *)malloc((res.amount)*sizeof(int));
	int remainder = 0;
	for (int i = res.amount - 1; i >= 0; i--)
	{
		int cur = remainder * powOfTen[baseIndex] + a.digits[i];
		res.digits[i] = cur / b;
		remainder = cur % b;
	}
	return remainder;
}
*/
LAB2DLL_API BigInt div_big(BigInt a, BigInt b)
{
	BigInt res,q,cur,y;
	int size_r;
	bool sign1;
	sign1 = a.negative;
	if(greater(b,a) && !a.negative && !b.negative)
	{
		res.amount=1;
		res.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		res.digits[0]=0;
		res.digits[1]=0;
		return res;
	}

	bool bsign = b.negative;
	bool asign = a.negative;
	if (b.negative == false)
	{
		sign1 = a.negative ^ b.negative;
	}
	else
	{
		b.negative = false;
		if(less(a,b) && a.negative == false)
		{
			sign1 = false;
		}
		else
		{
			sign1 = a.negative ^ true;
		}
	}

	reverse_num(a);

	q.amount = a.amount;
	q.digits = (int*) malloc((q.amount + 2)*sizeof(int));
	q.negative = false;
	cur.amount = 0;
	cur.digits = (int*) malloc((q.amount + 2)*sizeof(int));
	cur.negative = false;
	size_r = b.amount;
	for(int i=0;i<a.amount;++i)
	{
		q.digits[i]=0;
		cur.digits[i]=0;
	}
	int iq = 0;
	for(int i=0;i < a.amount;++i)
	{
		cur.digits[cur.amount]=a.digits[i];
		
		++cur.amount;
	
		reverse_num(cur);
		if(greater(b,cur))
		{
			iq++;
			reverse_num(cur);
			continue;
		}
		bool sign=0;
		
		while((greater(cur,b) || equals(cur,b)) && !sign)
		{
			++q.digits[iq];
			int aaa = cur.amount;
			
			y = sub(cur,b);
			y.negative = sign;
			free(cur.digits);
			cur = y;
		}
		++iq;
		reverse_num(cur);
	}
	q.amount=iq;
	reverse_num(cur);	
	reverse_num(q);
	while (q.digits[q.amount-1] == 0)
		q.amount-- ;
	while (cur.digits[cur.amount-1] == 0)
		cur.amount-- ;

	if((!bsign && asign || bsign && asign) && cur.amount != 0)
	{
		int i = 0;
		q.digits[q.amount] = 0;
		q.digits[q.amount+1] = 0;
		if(q.amount == 0)
		{
			++q.amount;
			q.digits[0] = 0;
		}
		q.digits[i]++;
		while(q.digits[i] >= 10)
		{
			q.digits[i+1]++;
			q.digits[i] /= 10;
			++i;
		}
		if(q.digits[q.amount] != 0)
			q.amount++;
		while (q.digits[q.amount-1] == 0)
			--q.amount;
	}

	free(cur.digits);
	res = q;
	res.negative = sign1;
	return res;
}
LAB2DLL_API BigInt mod_big(BigInt a, BigInt b)
{
	BigInt res,q,cur,y;
	int size_r;
	bool asign = a.negative;
	bool bsign = b.negative;
	if(greater(b,a) && !asign && !bsign)
	{
		res.negative = a.negative;
		res.amount = a.amount;
		res.digits = (int*) malloc((res.amount + 2)*sizeof(int));
		for(int i=0;i<res.amount;++i)
			res.digits[i]=a.digits[i];
		return res;
	}

	reverse_num(a);
	q.amount = a.amount;
	q.negative = false;
	q.digits =(int*) malloc((q.amount + 2)*sizeof(int));
	cur.amount = 0;
	cur.negative = false;
	cur.digits =(int*) malloc((q.amount + 2)*sizeof(int));
	size_r = b.amount;
	for(int i=0;i < a.amount;++i)
	{
		q.digits[i]=0;
		cur.digits[i]=0;
	}

	

	int iq=0;
	for(int i=0;i<a.amount;++i)
	{
		cur.digits[cur.amount]=a.digits[i];
		
		++cur.amount;
		
		reverse_num(cur);
		if(greater(b,cur))
		{
			iq++;
			reverse_num(cur);
			continue;
		}
		bool sign=0;
		
		while((greater(cur,b) || equals(cur,b)) && !sign)
		{
			++q.digits[iq];
			int aaa = cur.amount;
			
			y = sub(cur,b);
			y.negative = sign;
			free(cur.digits);
			cur = y;
		}
		++iq;
		reverse_num(cur);
	}
	q.amount = iq;
	reverse_num(cur);	
	reverse_num(q);
	while (q.digits[q.amount-1] == 0)
		q.amount-- ;
	while (cur.digits[cur.amount-1] == 0)
		cur.amount-- ;
	
	if((!bsign && asign || bsign && asign) && cur.amount != 0)
	{
		b.negative = false;
		cur.negative = true;
		y = sum(b,cur);
		free(cur.digits);
		cur = y;
	}
	
	free(q.digits);
	res=cur;
	res.negative = false;
	return res;
}

LAB2DLL_API bool isNull(BigInt a)
{
	for(int i=0;i < a.amount;++i)
		if(a.digits[i])
			return false;
	return true;
}
/*
BigInt power(BigInt a, BigInt b)
{
	BigInt x;
	x.amount = 1;
	x.digits = (int *)malloc((x.amount)*sizeof(int));
	x.digits[0] = 1;

	while(!isNull(b))
	{
		if (b.digits[0] % 2 == 1)
		{
			x = mul_big(x,a);
		}
		a = mul_big(a,a);

		b = div_small(b,2);
	}

	return x;
}
*/
LAB2DLL_API BigInt pow_mod(BigInt a, BigInt b, BigInt c)
{
	BigInt y = mod_big(a,c);
	BigInt res,ed;
	//outputOnScreen(y);
	free(a.digits);
	a = y;
	
	res.digits = (int*) malloc((1 + 2)*sizeof(int));
	ed.digits = (int*) malloc((1 + 2)*sizeof(int));
	res.digits[0]=1;
	res.digits[1]=0;
	res.negative = false;
	res.amount = 1;
	ed.digits[0]=1;
	ed.digits[1]=0;
	ed.amount = 1; //
	ed.negative = false;
	while (!isNull(b))
	{
		if (b.digits[0] % 2 == 1) 
		{
			y = mul_big(res,a);
			free(res.digits);
			
			res = y;
			
			y = mod_big(res,c);
			free(res.digits);
			res = y;
		}
		y = mul_big(a,a);
		free(a.digits);
		a = y;

		y = mod_big(a,c);
		free(a.digits);
		a = y;

		//outputOnScreen(a);
		//outputOnScreen(b);
		//outputOnScreen(c);
		div_small(b);
		//outputOnScreen(b);
	}

	return res;
}
FILE* ropen(char* file, bool bin)
{
	FILE * f1;
	if (bin)
		f1 = fopen(file,"rb");
	else
		f1 = fopen(file,"r");
	if (f1 == NULL)
	{
		printf("File not found.\n");
		return 0;
	}
	return f1;
}
FILE* wopen(char* file, bool bin)
{
	FILE * f1;
	if (bin)
		f1 = fopen(file,"wb");
	else
		f1 = fopen(file,"w");
	if (f1 == NULL)
	{
		printf("File not found.\n");
		return 0;
	}
	return f1;
}
bool binary(char* bin)
{
	char bina[] = "-b";
	if (strcmp(bin,bina) == 0 && strlen(bin) == strlen(bina))
		return true;
	return false;
}
extern "C" {
	__declspec(dllexport) BigInt* Big_new() {return new BigInt();}
	__declspec(dllexport) void Big_read(BigInt* a, char* fname, char* bin) {\
		bool b = binary(bin);
		FILE* f = ropen(fname,b);
		a->input(f,b);
	}
	__declspec(dllexport) void Big_write(BigInt* a, char* fname, char* bin) {\
		bool b = binary(bin);
		FILE* f = wopen(fname,b);
		a->output(f,b);
	}
	__declspec(dllexport) BigInt* Big_pow(BigInt* a,BigInt* b,BigInt*  mod)
	{
		BigInt* res=new BigInt();
		res[0] = pow_mod(a[0],b[0],mod[0]);
		return res;
	}
	__declspec(dllexport) BigInt* Big_add(BigInt* a,BigInt* b)
	{ 
		BigInt* res = new BigInt();
		res[0]=a[0] + b[0];
		return res;
	}
	__declspec(dllexport) BigInt* Big_sub(BigInt* a,BigInt* b)
	{
		BigInt* res=new BigInt();
		res[0]=a[0] - b[0];
		return res;
	}
	__declspec(dllexport) BigInt* Big_mul(BigInt* a,BigInt* b){
		BigInt* res=new BigInt();
		res[0]=a[0] * b[0];
		return res;
	}
	__declspec(dllexport) BigInt* Big_div(BigInt* a,BigInt* b){
		BigInt* res=new BigInt();
		res[0]=a[0] / b[0];
		return res;
	}
	__declspec(dllexport) BigInt* Big_mod(BigInt* a,BigInt* b)
	{
		BigInt* res=new BigInt();
		res[0]=a[0] % b[0];
		return res;
	}
}