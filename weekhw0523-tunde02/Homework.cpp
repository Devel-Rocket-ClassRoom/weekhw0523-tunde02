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

void Homework04_Run()
{
	// 4. 도둑 잡기 만들기
	//   - Homework04_Run(); 함수로 실행 가능해야 함.
	//   - 시작 금액 10000
	//   - 한판에 무조건 최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
	//   - 딜러는 A~K까지의 트럼프 카드 중 2장을 중복없이 선택하고 조커 카드가 추가된다.
	//   - 플레이어는 딜러의 카드 중 한장을 선택한다.
	//   - 만약 플레이어가 조커를 뽑았다면 플레이어의 승리.배팅 금액의 2배를 받는다.
	//   - 플레이어가 조커를 뽑지 못했다면 다음 게임을 시작하거나 배팅 금액의 2배를 추가로 지불하고 한번 더 선택할 수 있다.

	const int InitialCash		= 10000;
	const int MinimumBet		= 100;
	const int WinMultiplier		= 2;
	const int RetryMultiplier	= 2;
	const int DealerHandCount	= 3;
	const int MaximumCardNumber	= 13;
	const int JokerCardNumber	= 0;
	const int RetryChoice		= 2;

	int PlayerCash = InitialCash;
	int DealerHand[DealerHandCount] = { 0 };
	bool IsRevealed[DealerHandCount] = { false };
	bool IsDrawed[MaximumCardNumber] = { false };

	while (CanPlayChaseTheJoker(PlayerCash, MinimumBet))
	{
		int PlayerBet = 0;
		while (!IsValidBet(PlayerCash, PlayerBet, MinimumBet))
		{
			printf("[소지 금액 : %d ￦  |  최소 배팅 금액 %d ￦  |  최대 배팅 금액 %d ￦]\n", PlayerCash, MinimumBet, PlayerCash);
			printf("배팅 금액을 입력하세요 : ");
			PlayerBet = SafeInput(0);

			if (!IsValidBet(PlayerCash, PlayerBet, MinimumBet))
			{
				printf("[ERROR]  올바른 배팅 금액을 입력해주세요\n");
			}
		}

		PlayerCash -= PlayerBet;

		InitializeArray(DealerHand, DealerHandCount, 0);
		InitializeArray(IsRevealed, DealerHandCount, false);
		InitializeArray(IsDrawed, MaximumCardNumber, false);

		DrawRandomCards(DealerHand, IsDrawed, DealerHandCount, MaximumCardNumber);
		ShuffleHand(DealerHand, DealerHandCount);

		bool IsWin = PlayChaseTheJoker(DealerHand, IsRevealed, PlayerBet, DealerHandCount, JokerCardNumber, WinMultiplier, PlayerCash);

		if (!IsWin && CanPlayChaseTheJoker(PlayerCash, PlayerBet * RetryMultiplier))
		{
			printf("배팅 금액의 %d배(%d ￦)를 지불하면 카드를 한 번 더 선택할 수 있습니다.\n", RetryMultiplier, PlayerBet * RetryMultiplier);
			printf("1) 다음 게임으로   2) 한 번 더 선택\n");
			printf(" : ");
			int PlayerRechoice = SafeInput(0);

			while (PlayerRechoice < 1 || PlayerRechoice > 2)
			{
				printf("[ERROR]  1, 2번 중에 선택해주세요 : ");
				PlayerRechoice = SafeInput(0);
			}

			if (PlayerRechoice == RetryChoice)
			{
				int RetryBet = PlayerBet * RetryMultiplier;
				PlayerCash -= RetryBet;
				PlayerBet += RetryBet;

				PlayChaseTheJoker(DealerHand, IsRevealed, PlayerBet, DealerHandCount, JokerCardNumber, WinMultiplier, PlayerCash);
			}
		}

		PrintDivider('=', 100);
	}

	printf("게임이 종료되었습니다.\n");
}

bool CanPlayChaseTheJoker(int PlayerCash, int MinimumBet)
{
	return PlayerCash >= MinimumBet;
}

bool PlayChaseTheJoker(int* DealerHand, bool* IsRevealed, int PlayerBet, int DealerHandCount, int JokerCardNumber, int WinMultiplier, int& OutPlayerCash)
{
	bool IsWin = false;

	PrintDealerHand(DealerHand, IsRevealed, DealerHandCount, JokerCardNumber);
	printf("확인할 카드를 선택하세요 : ");
	int PlayerChoice = ChooseCard(IsRevealed, DealerHandCount);

	PrintDealerHand(DealerHand, IsRevealed, DealerHandCount, JokerCardNumber);

	if (IsJokerCard(DealerHand, PlayerChoice, JokerCardNumber))
	{
		OutPlayerCash += PlayerBet * WinMultiplier;
		IsWin = true;
		printf("조커를 찾으셨습니다!!!\n");
		printf("[소지 금액 : %d ￦]\n", OutPlayerCash);
	}
	else
	{
		printf("조커를 찾지 못했습니다...\n\n");
		printf("[소지 금액 : %d ￦]\n", OutPlayerCash);
	}

	return IsWin;
}

void PrintDealerHand(int* Hand, bool* IsRevealed, int Length, int JokerCardNumber)
{
	for (int i = 0; i < Length; i++)
	{
		printf("┏━━━━━━┓  ");
	}
	printf("\n");

	for (int i = 0; i < Length; i++)
	{
		printf("┃      ┃  ");
	}
	printf("\n");

	for (int i = 0; i < Length; i++)
	{
		if (!IsRevealed[i])
		{
			printf("┃   ?  ┃  ");
		}
		else if (Hand[i] == JokerCardNumber)
		{
			printf("┃ JOKER┃  ");
		}
		else if (Hand[i] == 11)
		{
			printf("┃   J  ┃  ");
		}
		else if (Hand[i] == 12)
		{
			printf("┃   Q  ┃  ");
		}
		else if (Hand[i] == 13)
		{
			printf("┃   K  ┃  ");
		}
		else
		{
			printf("┃  %2d  ┃  ", Hand[i]);
		}
	}
	printf("\n");

	for (int i = 0; i < Length; i++)
	{
		printf("┃      ┃  ");
	}
	printf("\n");

	for (int i = 0; i < Length; i++)
	{
		printf("┗━━━━━━┛  ");
	}
	printf("\n\n");
}

void DrawRandomCards(int* Hand, bool* IsDrawed, int Length, int MaximumCardNumber)
{
	for (int i = 0; i < Length - 1; i++)
	{
		int RandomCard = rand() % MaximumCardNumber + 1;
		while (IsDrawed[RandomCard - 1])
		{
			RandomCard = rand() % MaximumCardNumber + 1;
		}

		IsDrawed[RandomCard - 1] = true;
		Hand[i] = RandomCard;
	}
}

void ShuffleHand(int* Hand, int Length)
{
	// Fisher-Yates 셔플 알고리즘으로 핸드를 섞는다

	for (int i = Length - 1; i > -1; i--)
	{
		int RandomIndex = rand() % (i + 1);

		int Temp = Hand[RandomIndex];
		Hand[RandomIndex] = Hand[i];
		Hand[i] = Temp;
	}
}

int ChooseCard(bool* IsRevealed, int DealerHandCount)
{
	int PlayerChoice = SafeInput(0);
	while (PlayerChoice < 1 || PlayerChoice > DealerHandCount)
	{
		printf("[ERROR]  ");
		for (int i = 0; i < DealerHandCount; i++)
		{
			printf("%d ", i + 1);
		}
		printf("번 중에 선택해주세요 : ");

		PlayerChoice = SafeInput(0);
	}

	IsRevealed[PlayerChoice - 1] = true;

	return PlayerChoice;
}

bool IsJokerCard(int* DealerHand, int PlayerChoice, int JokerCardNumber)
{
	return DealerHand[PlayerChoice - 1] == JokerCardNumber;
}

void Homework05_Run()
{
	// 5. 미로 탈출 게임에 랜덤 인카운터를 추가하여 적과의 턴제 전투 만들기
	//   - Homework05_Run(); 함수로 실행 가능해야 함.
	//   - HP는 100으로 시작
	//   - 공격을 할 때 상대방에게 5~15의 데미지를 준다.
	//   - 10 % 의 확률로 크리티컬이 발생해 2배의 데미지를 준다.
	//   - 상대방의 HP가 0 이하가 되면 승리한다.	

	const int MazeRowSize				= 10;
	const int MazeColumnSize			= 10;
	const int EncounterRate				= 10;
	const int InitialHP					= 100;
	const int MinimumDamage				= 5;
	const int MaximumDamage				= 15;
	const int CriticalRate				= 10;
	const int CriticalDamageMultiplier	= 2;

	// 미로 배열
	TileType Maze[MazeRowSize][MazeColumnSize] = {
		{Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall},
		{Wall,Road,Road,Road,Road,Road,Road,Road,Road,Wall},
		{Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Road,Wall},
		{Wall,Road,Road,Road,Road,Road,Road,Wall,Road,Wall},
		{Wall,Road,Wall,Wall,Wall,Wall,Road,Wall,Road,Wall},
		{Wall,Road,Wall,Road,Wall,Wall,Road,Wall,Road,Wall},
		{Wall,Road,Wall,Road,Road,Road,Road,Wall,Road,Wall},
		{Wall,Road,Wall,Wall,Wall,Wall,Wall,Wall,Road,Wall},
		{Wall,Road,Road,Road,Road,Road,Road,Road,Road,Wall},
		{Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall}
	};

	const int StartX = 1;
	const int StartY = 1;
	const int EndX = 5;
	const int EndY = 3;

	Maze[StartX][StartY] = Start;
	Maze[EndX][EndY] = End;

	int PlayerHP = InitialHP;
	int PlayerX = StartX;
	int PlayerY = StartY;

	// 현재 플레이어가 밟고 있는 타일의 종류를 저장
	TileType PrevPlayerTileType = Start;

	// 플레이어 초기 위치 설정
	PrevPlayerTileType = Maze[PlayerX][PlayerY];
	Maze[PlayerX][PlayerY] = Player;

	printf("== = 텍스트 미로 탈출 게임 == =\n");

	while (CanPlayMazeGame(PlayerHP, PlayerX, PlayerY, EndX, EndY))
	{
		ShowMaze((int*)Maze, MazeRowSize, MazeColumnSize);

		printf("\n플레이어 체력(%d)", PlayerHP);
		PrintHpBar(PlayerHP);
		printf("\n");

		printf("이동할 수 있는 방향을 선택하세요(w: 위, s : 아래, a : 왼쪽, d : 오른쪽)\n");
		ShowMovableDirections((int*)Maze, MazeRowSize, MazeColumnSize, PlayerX, PlayerY);
		printf("\n : ");

		DirectionType PlayerInputDirection = InputDirection();
		while (!CanMoveTo((int*)Maze, MazeRowSize, MazeColumnSize, PlayerX, PlayerY, PlayerInputDirection))
		{
			printf("[ERROR]  올바른 방향을 선택하세요 : ");
			PlayerInputDirection = InputDirection();
		}

		// 플레이어가 이동하므로 이전에 있던 타일로 교체
		Maze[PlayerX][PlayerY] = PrevPlayerTileType;

		// 플레이어 좌표 이동
		int DirectionIndex = DirectionType2Int(PlayerInputDirection);
		PlayerX += Dx[DirectionIndex];
		PlayerY += Dy[DirectionIndex];

		// 플레이어가 밝고 있는 타일을 저장하고
		// 플레이어 좌표 위치의 타일을 플레이어로 변경
		PrevPlayerTileType = Maze[PlayerX][PlayerY];
		Maze[PlayerX][PlayerY] = Player;

		// 랜덤 인카운터
		bool bEncounter = IsEncountered(EncounterRate);
		if (bEncounter)
		{
			PlayerHP = ProcessEncounter(PlayerHP, InitialHP, MinimumDamage, MaximumDamage, CriticalRate, CriticalDamageMultiplier);

			if (PlayerHP <= 0)
			{
				// 플레이어가 사망하였으므로 해당 타일을 무덤으로 교체
				Maze[PlayerX][PlayerY] = Grave;
			}
		}
	}

	ShowMaze((int*)Maze, MazeRowSize, MazeColumnSize);

	if (PlayerHP > 0)
	{
		printf("\n[플레이어가 미로를 탈출했습니다!!]\n");
	}
	else
	{
		printf("\n[플레이어가 사망했습니다..]\n");
	}
}

bool CanPlayMazeGame(int PlayerHP, int PlayerX, int PlayerY, int EndX, int EndY)
{
	return (PlayerHP > 0) && !((PlayerX == EndX) && (PlayerY == EndY));
}

void ShowMaze(int* Maze, int RowSize, int ColumnSize)
{
	printf("\n");
	for (int i = 0; i < RowSize; i++)
	{
		for (int j = 0; j < ColumnSize; j++)
		{
			int Tile = *(Maze + (i * ColumnSize) + j);
			switch (Tile)
			{
				case Road:
					printf(". ");
					break;
				case Wall:
					printf("# ");
					break;
				case Start:
					printf("S ");
					break;
				case End:
					printf("E ");
					break;
				case Player:
					printf("P ");
					break;
				case Grave:
					printf("X ");
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}

void ShowMovableDirections(int* Maze, int RowSize, int ColumnSize, int PlayerX, int PlayerY)
{
	printf("이동 가능한 방향 : ");
	if (CanMoveTo(Maze, RowSize, ColumnSize, PlayerX, PlayerY, Up))
	{
		printf("w(↑) ");
	}
	if (CanMoveTo(Maze, RowSize, ColumnSize, PlayerX, PlayerY, Down))
	{
		printf("s(↓) ");
	}
	if (CanMoveTo(Maze, RowSize, ColumnSize, PlayerX, PlayerY, Left))
	{
		printf("a(←) ");
	}
	if (CanMoveTo(Maze, RowSize, ColumnSize, PlayerX, PlayerY, Right))
	{
		printf("d(→) ");
	}
}

DirectionType InputDirection()
{
	char PlayerInput = SafeInput('\0');
	DirectionType Direction = (DirectionType)(-1);

	switch (PlayerInput)
	{
		case 'w':
		case 'W':
			Direction = Up;
			break;
		case 's':
		case 'S':
			Direction = Down;
			break;
		case 'a':
		case 'A':
			Direction = Left;
			break;
		case 'd':
		case 'D':
			Direction = Right;
			break;
		default:
			break;
	}

	return Direction;
}

int DirectionType2Int(DirectionType Direction)
{
	switch (Direction)
	{
		case Up:
			return 0;
		case Down:
			return 1;
		case Left:
			return 2;
		case Right:
			return 3;
		default:
			return -1;
	}
}

bool IsValidDirectionType(DirectionType Target)
{
	switch (Target)
	{
		case Up:
		case Down:
		case Left:
		case Right:
			return true;
		default:
			return false;
	}
}

bool CanMoveTo(int* Maze, int RowSize, int ColumnSize, int PlayerX, int PlayerY, DirectionType Direction)
{
	if (!IsValidDirectionType(Direction))
	{
		return false;
	}

	int DirectionIndex = DirectionType2Int(Direction);
	int NextX = PlayerX + Dx[DirectionIndex];
	int NextY = PlayerY + Dy[DirectionIndex];

	return (-1 < NextX && NextX < RowSize) && (-1 < NextY && NextY < ColumnSize)
		&& *(Maze + (NextX * ColumnSize) + NextY) != Wall;
}

void PrintHpBar(int HP)
{
	const int MaximumSegments = 20;
	const int SegmentUnit = 100 / MaximumSegments;
	int HpSegments = HP / SegmentUnit;
	int BlankSegments = MaximumSegments - HpSegments;

	printf("[");
	if (HpSegments > 0)
	{
		for (int i = 0; i < HpSegments; i++)
		{
			printf("=");
		}

		for (int i = 0; i < BlankSegments; i++)
		{
			printf(" ");
		}
	}
	else
	{
		printf("-");
		for (int i = 1; i < BlankSegments; i++)
		{
			printf(" ");
		}
	}
	printf("]");
}

bool IsEncountered(int EncounterRate)
{
	// 랜덤 숫자가 0 ~ 9면 인카운터
	return (rand() % 100) < EncounterRate;
}

int ProcessEncounter(int PrevPlayerHP, int InitialHP, int MinimumDamage, int MaximumDamage, int CriticalRate, int CriticalDamageMultiplier)
{
	PrintDivider('-', 50);
	printf("[몬스터를 조우했습니다..!!]\n\n");

	int PlayerHP = PrevPlayerHP;
	int MonsterHP = InitialHP;

	while (PlayerHP > 0 && MonsterHP > 0)
	{
		printf("플레이어 체력(%d)", PlayerHP);
		PrintHpBar(PlayerHP);
		printf("  |  몬스터 체력(%d)", MonsterHP);
		PrintHpBar(MonsterHP);
		printf("\n");

		printf("공격하려면 아무 키나 입력하세요 : ");
		cin.get();

		bool IsCritical = false;
		int PlayerDamage = CalcDamage(MinimumDamage, MaximumDamage, CriticalRate, CriticalDamageMultiplier, IsCritical);

		if (!IsCritical)
		{
			printf("[플레이어의 공격] : %d\n", PlayerDamage);
		}
		else
		{
			printf("[플레이어의 공격 (크리티컬!)] : %d\n", PlayerDamage);
		}

		MonsterHP -= PlayerDamage;

		if (MonsterHP > 0)
		{
			int MonsterDamage = CalcDamage(MinimumDamage, MaximumDamage, CriticalRate, CriticalDamageMultiplier, IsCritical);

			if (!IsCritical)
			{
				printf("[몬스터의 공격] : %d\n", MonsterDamage);
			}
			else
			{
				printf("[몬스터의 공격 (크리티컬!)] : %d\n", MonsterDamage);
			}

			PlayerHP -= MonsterDamage;
		}
		else
		{
			printf("\n[몬스터를 처치했습니다!!]\n");
			printf("전투를 종료하려면 아무 키나 입력하세요 : ");
			cin.get();
		}

		printf("\n");
	}

	PrintDivider('-', 50);

	return PlayerHP;
}

int CalcDamage(int MinimumDamage, int MaximumDamage, int CriticalRate, int CriticalDamageMultiplier, bool& IsCritical)
{
	int Damage = ((rand() % (MaximumDamage - MinimumDamage)) + MinimumDamage);

	// 랜덤 숫자가 0 ~ 10이면 크리티컬
	IsCritical = rand() % 100 < CriticalRate;
	if (IsCritical)
	{
		Damage *= CriticalDamageMultiplier;
	}

	return Damage;
}
