#pragma once
#include <iostream>
using std::cin;

const int CIN_IGNORE_LENGTH = 10000;
const char CIN_IGNORE_DELIMITER = '\n';

void PrintDivider(wchar_t Divider, int Count);

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
