#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include "Lab2DLL.h"

int main(int argc, char* argv[])
{
	FILE * f1, *f2, *f3, *f;
	int operate, binArg = -1; // 1 - sum, 2 - sub, 3 - mul, 4 - div, 5 - mod, 6 - power
	char binary[] = "-b";
	bool bin = false;
	
	for (int i = argc - 1; i >= 5; --i)
	{
		binArg = i;
		if (strcmp(argv[binArg], binary) == 0 && strlen(argv[binArg]) == strlen(binary))
		{
			bin = true;
			break;
		}
	}

	if(!bin)
	{
		f1 = fopen(argv[1], "r");
		f2 = fopen(argv[3], "r");
		f = fopen(argv[4], "w");
	}
	else
	{
		f1 = fopen(argv[1], "rb");
		f2 = fopen(argv[3], "rb");
		f = fopen(argv[4], "wb");
	}

	if (f1 == NULL)
	{
		printf("Error occurred while opening first argument file.");
		return 0;
	}

	if (f2 == NULL)
	{
		printf("Error occurred while opening second argument file.");
		return 0;
	}

	if (f == NULL)
	{
		printf("Error occurred while opening output file.");
		return 0;
	}

	if (argv[2][0] == (char)'+')
		operate = 1;
	else if (argv[2][0] == (char)'-')
		operate = 2;
	else if (argv[2][0] == (char)'*')
		operate = 3;
	else if (argv[2][0] == (char)'/')
		operate = 4;
	else if (argv[2][0] == (char)'%')
		operate = 5;
	else
	{
		operate = 6;
		if(!bin)
			f3 = fopen(argv[argc - 1],"r");
		else
			f3 = fopen(argv[argc - 1],"rb");
		if (f3 == NULL)
		{
			printf("Error occurred while opening third argument file.");
			return 0;
		}
	}

	BigInt a1,a2,a3,re;
	a1.input(f1,bin);
	fclose(f1);

	if (a1.digits == NULL)
		return 0;

	outputOnScreen(a1);

	a2.input(f2,bin);
	fclose(f2);
	if (a2.digits == NULL)
		return 0;
	
	outputOnScreen(a2);

	if (operate == 6)
	{
		a3.input(f3,bin);
		fclose(f3);
		if (a3.digits == NULL)
			return 0;
		outputOnScreen(a3);
	}
	
	if (operate == 1)
		re = a1 + a2;
	else if (operate == 2)
		re = a1 - a2;
	else if (operate == 3)
		re = a1 * a2;
	else if (operate == 4)
	{
		if (a2.amount == 1 && a2.digits[0] == 0)
			return 0;
		re = a1 / a2;
	}
	else if (operate == 5)
	{
		if (a2.amount == 1 && a2.digits[0] == 0)
			return 0;
		re = a1 % a2;
	}
	else
	{
		if (a1.negative || a2.negative || a3.negative || (a1.amount == 1 && a1.digits[0] == 0)
			|| (a2.amount == 1 && a2.digits[0] == 0) || (a3.amount == 1 && a3.digits[0] == 0))
		{
			printf("Power modulo operation requires only positive numbers!");
			return 0;
		}
		re = pow_mod(a1,a2,a3);
	}
	
	re.output(f,bin);
	outputOnScreen(re);

	fclose(f);
	
	return 0;
}
