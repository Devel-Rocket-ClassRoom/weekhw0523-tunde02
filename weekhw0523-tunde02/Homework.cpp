#include "Homework.h"

void Homework02_Run()
{
	// 2. 자리수 분리해서 합치기(입력은 자리 수 제한 없음)

	int Number = 0;
	int InitialNumber = 0;

	printf("정수를 입력하세요 : ");
	cin >> Number;

	InitialNumber = Number;

	const int Ten = 10;
	int Sum = 0;
	while (Number > 0)
	{
		int Digit = Number % Ten;
		Sum += Digit;
		Number /= Ten;
	}

	printf("%d 의 자리수의 합 : %d\n", InitialNumber, Sum);
}
