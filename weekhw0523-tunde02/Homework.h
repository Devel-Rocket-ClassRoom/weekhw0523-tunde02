#pragma once
#include <iostream>
using std::cin;

const int CIN_IGNORE_LENGTH = 10000;
const char CIN_IGNORE_DELIMITER = '\n';

void PrintDivider(wchar_t Divider, int Count);

template <typename T>
void InitializeArray(T* Array, int Length, T DefaultValue)
{
	for (int i = 0; i < Length; i++)
	{
		Array[i] = DefaultValue;
	}
}

template <typename T>
T SafeInput(T DefaultValue)
{
	T Input = DefaultValue;
	cin >> Input;
	cin.clear();
	cin.ignore(CIN_IGNORE_DELIMITER, CIN_IGNORE_DELIMITER);

	return Input;
}

// 과제 2
// 자리수 분리해서 합치기
void Homework02_Run();

// 과제3
// 슬롯 머신 게임 만들기
void Homework03_Run();
void PrintSlots(int* Slots, int SlotSize);
bool CanPlaySlot(int PlayerCash, int MinimumBet, int MaximumCash);
bool IsValidBet(int PlayerCash, int PlayerBet, int MinimumBet);
int CalcTotalBet(int PlayerBet, int Multiplier, int MaximumCash);
void PlaySlots(int Turn, int* Slots, int SlotSize, int MaximumSlotNumber, bool IsTestGame);
bool IsJackpot(int* Slots, int SlotSize);
bool IsPlayerWin(int* Slots, int SlotSize);
int CalcPlayerCash(int PlayerCash, int TotalBet, int MaximumCash);
bool IsExceededMaximumCash(int PlayerCash, int MaximumCash);
bool IsGameWin(int PlayerCash, int MinimumBet);

// 과제4
// 도둑 잡기 만들기
void Homework04_Run();
bool CanPlayChaseTheJoker(int PlayerCash, int MinimumBet);
bool PlayChaseTheJoker(int* DealerHand, bool* IsRevealed, int PlayerBet, int DealerHandCount, int JokerCardNumber, int WinMultiplier, int& OutPlayerCash);
void PrintDealerHand(int* Hand, bool* IsRevealed, int Length, int JokerCardNumber);
void DrawRandomCards(int* Hand, bool* IsDrawed, int Length, int MaximumCardNumber);
void ShuffleHand(int* Hand, int Length);
int ChooseCard(bool* IsRevealed, int DealerHandCount);
bool IsJokerCard(int* DealerHand, int PlayerChoice, int JokerCardNumber);
