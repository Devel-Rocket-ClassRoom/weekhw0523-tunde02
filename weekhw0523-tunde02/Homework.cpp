#include "Homework.h"

void PrintDivider(wchar_t Divider, int Count)
{
	printf("\n");
	for (int i = 0; i < Count; i++)
	{
		printf("%lc", Divider);
	}
	printf("\n\n");
}

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

void Homework03_Run()
{
	// 3. 슬롯 머신 게임 만들기
	//   - Homework03_Run(); 함수로 실행 가능해야 함.
	//   - 시작 금액 10000
	//   - 한판에 무조건  최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
	//   - 같은 숫자 3개가 나오면 50배로 돌려 받는다.
	//   - 만약 777이면 10000배 받음

	const bool IsTestGame = true;

	const int InitialCash		= 10000;
	const int MaximumCash		= 999999999;
	const int WinMultiplier		= 50;
	const int JackpotMultiplier = 10000;
	const int SlotSize			= 3;
	const int MaximumSlotNumber = 9;
	const int MinimumBet		= 100;

	int Slots[SlotSize] = { 0 };
	int PlayerCash = InitialCash;
	int PlayerBet = MinimumBet;
	int Turn = 1;

	while (CanPlaySlot(PlayerCash, MinimumBet, MaximumCash))
	{
		printf("게임 %d\n", Turn);
		printf("[소지 금액 : %d ￦  |  최소 배팅 금액 %d ￦  |  최대 배팅 금액 %d ￦]\n", PlayerCash, MinimumBet, PlayerCash);
		printf("배팅 금액을 입력하세요 : ");
		PlayerBet = 0;
		cin >> PlayerBet;
		cin.clear();
		cin.ignore(CIN_IGNORE_LENGTH, CIN_IGNORE_DELIMITER);

		if (!IsValidBet(PlayerCash, PlayerBet, MinimumBet))
		{
			printf("[ERROR] 올바른 배팅 금액을 입력해주세요!!\n\n");
			continue;
		}

		PlayerCash -= PlayerBet;

		PlaySlots(Turn, Slots, SlotSize, MaximumSlotNumber, IsTestGame);
		PrintSlots(Slots, SlotSize);

		int TotalBet = 0;
		int PrevPlayerCash = PlayerCash;
		if (IsJackpot(Slots, SlotSize))
		{
			TotalBet = CalcTotalBet(PlayerBet, JackpotMultiplier, MaximumCash);
			PlayerCash = CalcPlayerCash(PlayerCash, TotalBet, MaximumCash);

			printf("잭팟입니다!!!\n");
			printf("[소지금액 : %d ￦  +  %d ￦  →  %d ￦]\n", PrevPlayerCash, TotalBet, PlayerCash);

		}
		else if (IsPlayerWin(Slots, SlotSize))
		{
			TotalBet = CalcTotalBet(PlayerBet, WinMultiplier, MaximumCash);
			PlayerCash = CalcPlayerCash(PlayerCash, TotalBet, MaximumCash);

			printf("당첨입니다!!\n");
			printf("[소지금액 : %d ￦  +  %d ￦  →  %d ￦]\n", PrevPlayerCash, TotalBet, PlayerCash);

		}
		else
		{
			printf("꽝입니다..\n");
			printf("[소지금액 : %d ￦]\n", PlayerCash);
		}

		Turn++;
		PrintDivider('=', 60);
	}

	if (!IsGameWin(PlayerCash, MinimumBet))
	{
		printf("소지금액이 부족하여 게임이 종료됩니다.\n");
	}
	else
	{
		printf("최대 금액을 달성하셨습니다!!!\n");
		printf("[소지금액 : %d ￦]\n", PlayerCash);
	}
}

void PrintSlots(int* Slots, int SlotSize)
{
	bool IsInitialPrint = Slots[0] == 0;

	printf("\n");
	for (int i = 0; i < SlotSize; i++)
	{
		if (!IsInitialPrint)
		{
			printf("[ %d ]  ", Slots[i]);
		}
		else
		{
			printf("[ * ]  ");
		}
	}
	printf("\n");
}

bool CanPlaySlot(int PlayerCash, int MinumumBet, int MaximumCash)
{
	return (PlayerCash >= MinumumBet) && (PlayerCash < MaximumCash);
}

bool IsValidBet(int PlayerCash, int PlayerBet, int MinimumBet)
{
	return (PlayerBet <= PlayerCash) && (PlayerBet >= MinimumBet);
}

int CalcTotalBet(int PlayerBet, int Multiplier, int MaximumCash)
{
	return PlayerBet <= MaximumCash / Multiplier ? PlayerBet * Multiplier : MaximumCash;
}

void PlaySlots(int Turn, int* Slots, int SlotSize, int MaximumSlotNumber, bool IsTestGame)
{
	// 테스트를 위해 매 4번 째 게임마다 같은 숫자 3개가,
	// 매 7번째 게임마다 잭팟이 나오도록 구현
	const int WinCycle = 4;
	const int JackpotCycle = 7;
	const int JackpotNumber = 7;

	if (IsTestGame && Turn % JackpotCycle == 0)
	{
		for (int i = 0; i < SlotSize; i++)
		{
			Slots[i] = JackpotNumber;
		}
	}
	else if (IsTestGame && Turn % WinCycle == 0)
	{
		int SlotNumber = (rand() % MaximumSlotNumber) + 1;
		for (int i = 0; i < SlotSize; i++)
		{
			Slots[i] = SlotNumber;
		}
	}
	else
	{
		for (int i = 0; i < SlotSize; i++)
		{
			Slots[i] = (rand() % MaximumSlotNumber) + 1;
		}
	}
}

bool IsJackpot(int* Slots, int SlotSize)
{
	for (int i = 0; i < SlotSize; i++)
	{
		if (Slots[i] != 7)
		{
			return false;
		}
	}

	return true;
}

bool IsPlayerWin(int* Slots, int SlotSize)
{
	int TargetSlotNumber = Slots[0];
	for (int i = 1; i < SlotSize; i++)
	{
		if (Slots[i] != TargetSlotNumber)
		{
			return false;
		}
	}

	return true;
}

int CalcPlayerCash(int PlayerCash, int TotalBet, int MaximumCash)
{
	int ExpectedPlayerCash = PlayerCash + TotalBet;
	return IsExceededMaximumCash(ExpectedPlayerCash, MaximumCash) ? MaximumCash : ExpectedPlayerCash;
}

bool IsExceededMaximumCash(int PlayerCash, int MaximumCash)
{
	return PlayerCash >= MaximumCash || PlayerCash < 0;
}

bool IsGameWin(int PlayerCash, int MinimumBet)
{
	return PlayerCash > MinimumBet;
}
