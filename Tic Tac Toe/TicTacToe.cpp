
#include "stdafx.h"
#include "TicTacToe.h"


//---------------------------------
uint32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
	//const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	//static mt19937_64 generator(seed);
	//uniform_int_distribution<int32_t> dist(min, max);

	mt19937 gen(time(0));
	uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

//---------------------------------
/// Init memory for game
void __fastcall InitGame(TIC_TAC_TOE &game)
{
	game.m_ppField = new eTIC_TAC_TOE*[game.m_Size];

	for (size_t i = 0; i < game.m_Size; i++)
	{
		game.m_ppField[i] = new eTIC_TAC_TOE[game.m_Size];
	}

	// Here plus 1 because:
	// One sum of the elements along the major diagonal of X
	// And 
	// One sum of the elements along the major diagonal of Y
	game.m_dwSumWonX = new size_t[game.m_Size + 1];
	game.m_dwSumWonY = new size_t[game.m_Size + 1];
	for (size_t i = 0; i <= game.m_Size; i++)
	{
		game.m_dwSumWonX[i] = 0;
		game.m_dwSumWonY[i] = 0;
	}

	for (size_t i = 0; i < game.m_Size; i++)
		for (size_t j = 0; j < game.m_Size; j++)
			game.m_ppField[i][j] = eEmpty;

	if (getRandomNum(0, 1000) > 500)
	{
		game.m_tttGamerOne = eTic;
		game.m_tttGamerTwo = eTac;
		game.m_nStep = 1;
	}
	else
	{
		game.m_tttGamerOne = eTac;
		game.m_tttGamerTwo = eTic;
		game.m_nStep = 0;
	}
}

//---------------------------------
/// Delete memory for game
void __fastcall DeinitGame(TIC_TAC_TOE &game)
{
	for (size_t i = 0; i < game.m_Size; i++)
		delete[] game.m_ppField[i];

	delete[] game.m_ppField;

	delete[] game.m_dwSumWonX;
	delete[] game.m_dwSumWonY;
}

//---------------------------------
/// Draw Game into console
void __fastcall DrawGame(const TIC_TAC_TOE &game)
{
	cout << "    ";
	for (size_t i = 0; i < game.m_Size; i++)
		cout << i + 1 << "  ";
	cout << "\n";

	for (size_t i = 0; i < game.m_Size; i++)
	{
		cout << i + 1 << "  ";
		for (size_t j = 0; j < game.m_Size; j++)
			cout << (char)game.m_ppField[i][j] << " | ";

		cout << "\n";
	}

	cout << "\n";
	cout << ONE_PLAYER << ": " << (char)game.m_tttGamerOne << "\n";
	cout << TWO_PLAYER << ": " << (char)game.m_tttGamerTwo << "\n";
}


//---------------------------------
/// Define winner
Progress __fastcall getWon(const TIC_TAC_TOE game)
{
	Progress progRes = Progress::DRAW;

	// Check of drawm
	bool bCheck = false;
	for (size_t i = 0; i < game.m_Size; i++)
	{
		for (size_t j = 0; j < game.m_Size; j++)
		{
			if (game.m_ppField[i][j] == eEmpty)
			{
				progRes = Progress::IN_PROGRESS;
				bCheck = true;
				break;
			}
		}

		if (bCheck)
			break;
	}

	for (size_t i = 0; i <= game.m_Size; i++)
	{
		// Check won first playerby X and Y
		if ((game.m_dwSumWonX[i] == (game.m_Size * (char)game.m_tttGamerOne)) ||
			(game.m_dwSumWonY[i] == (game.m_Size * (char)game.m_tttGamerOne)))
		{
			progRes = Progress::WON_HUMAN;
			break;
		}

		// Check won second player by X and Y
		if ((game.m_dwSumWonX[i] == (game.m_Size * (char)game.m_tttGamerTwo)) ||
			(game.m_dwSumWonY[i] == (game.m_Size * (char)game.m_tttGamerTwo)))
		{
			progRes = Progress::WON_AI;
			break;
		}
	}

	return progRes;
}

//---------------------------------
/// Step by player
Coord __fastcall getCoord(TIC_TAC_TOE &tttGame)
{
	Coord c;

	do {
		cout << "Enter X: ";
		cin >> c.x;
		cout << "Enter Y: ";
		cin >> c.y;

		if (((c.x > 0) && (c.x <= tttGame.m_Size)) &&
			((c.y > 0) && (c.y <= tttGame.m_Size)) &&
			(tttGame.m_ppField[--c.y][--c.x] == eEmpty))
			break;

	} while (1);

	//--c.x;
	//--c.y;

	return c;
}

//---------------------------------
/// Step by AI
Coord __fastcall getCoordAi(TIC_TAC_TOE &game)
{
	Coord c;

	// Pre win situation
	eTIC_TAC_TOE analysPre = game.m_tttGamerTwo;
	for (size_t i = 0; i < game.m_Size; i++)
	{
		for (size_t j = 0; j < game.m_Size; j++)
		{
			c.x = j;
			c.y = i;

			if (game.m_ppField[i][j] != eEmpty)
				continue;

			game.m_ppField[i][j] = analysPre;
			game.stepUp(c, analysPre);

			if (getWon(game) == WON_AI)
			{
				game.m_ppField[i][j] = eEmpty;
				game.stepDown(c, analysPre);
				return c;
			}

			game.m_ppField[i][j] = eEmpty;
			game.stepDown(c, analysPre);
		}
	}

	// Pre fail situation
	analysPre = game.m_tttGamerOne;
	for (size_t i = 0; i < game.m_Size; i++)
	{
		for (size_t j = 0; j < game.m_Size; j++)
		{
			c.x = j;
			c.y = i;

			if (game.m_ppField[i][j] != eEmpty)
				continue;

			game.m_ppField[i][j] = analysPre;
			game.stepUp(c, analysPre);

			if (getWon(game) == WON_HUMAN)
			{
				game.m_ppField[i][j] = eEmpty;
				game.stepDown(c, analysPre);
				return c;
			}

			game.m_ppField[i][j] = eEmpty;
			game.stepDown(c, analysPre);
		}
	}

	// Center
	if (game.m_ppField[1][1] == eEmpty)
		return {1, 1};

	// Corner
	Coord arr[4];
	size_t num{ 0 };
	if (game.m_ppField[0][0]  == eEmpty)
	{
		arr[num] = { 0, 0 };
		num++;
	}
	if (game.m_ppField[2][2] == eEmpty)
	{
		arr[num] = { 2, 2 };
		num++;
	}
	if (game.m_ppField[2][0] == eEmpty)
	{
		arr[num] = { 2, 0 };
		num++;
	}
	if (game.m_ppField[0][2] == eEmpty)
	{
		arr[num] = { 0, 2 };
		num++;
	}
	if (num > 0)
	{
		const size_t dwIndex = getRandomNum(0, 1000) % num;
		return arr[dwIndex];
	}

	// Not corner
	num = 0;
	if (game.m_ppField[0][1] == eEmpty)
	{
		arr[num] = { 0, 1 };
		num++;
	}
	if (game.m_ppField[2][1] == eEmpty)
	{
		arr[num] = { 2, 1 };
		num++;
	}
	if (game.m_ppField[1][0] == eEmpty)
	{
		arr[num] = { 1, 0 };
		num++;
	}
	if (game.m_ppField[1][2] == eEmpty)
	{
		arr[num] = { 1, 2 };
		num++;
	}
	if (num > 0)
	{
		const size_t dwIndex = getRandomNum(0, 1000) % num;
		return arr[dwIndex];
	}
}

//---------------------------------
/// Congratation
void __fastcall Congrats(const TIC_TAC_TOE &game)
{
	if (game.m_Progress == WON_HUMAN)
		cout << ONE_PLAYER << " is winner" << "\n";
	if (game.m_Progress == WON_AI)
		cout << TWO_PLAYER << " is winner" << "\n";
	if (game.m_Progress == DRAW)
		cout << "Draw :/" << "\n";
}
